// This file is part of Dungwich Sandeon.
// 
// Dungwich Sandeon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// Dungwich Sandeon is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Dungwich Sandeon.  If not, see <https://www.gnu.org/licenses/>.

#ifndef src_game_engine_engine_class_hpp
#define src_game_engine_engine_class_hpp

// src/game_engine/engine_class.hpp

#include "../misc_includes.hpp"
#include "basic_window_classes.hpp"
#include "../input_kind_enum.hpp"
#include "general_comp_classes.hpp"
#include "block_comp_classes.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{

template<typename ObjType>
concept EngineErrWhenEntNullIdObj
	= requires(ObjType obj)
{
	{ obj.ent_id() } -> std::same_as<ecs::EntId>;
};

class Engine final
{
public:		// types
	using EntIdSetVec2d
		= std::vector<std::vector<std::set<ecs::EntId>>>;
public:		// constants
	static const PosVec2 PLAYFIELD_POS;
	static const SizeVec2 PLAYFIELD_SIZE_2D;

	// These are basement floors
	static constexpr int LOWEST_FLOOR = 50;
	static constexpr int HIGHEST_FLOOR = 1;
	static constexpr int NUM_FLOORS
		= abs(HIGHEST_FLOOR - LOWEST_FLOOR) + 1;
private:		// variables
	ecs::Engine _ecs_engine;
	Window _screen, _playfield;

	// dimensions: floor, y, x
	std::vector<EntIdSetVec2d> _playfield_ent_id_v3d;

	size_t _floor = HIGHEST_FLOOR;
public:		// functions
	Engine();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Engine);
	~Engine();

	void position_ctor_callback(comp::Position* obj);
	void position_dtor_callback(comp::Position* obj);
	void position_set_pos_callback(comp::Position* obj,
		const PosVec3& n_pos);

	GEN_GETTER_BY_CON_REF(ecs_engine);
	GEN_GETTER_BY_CON_REF(screen);
	GEN_GETTER_BY_CON_REF(playfield);
	GEN_GETTER_BY_CON_REF(playfield_ent_id_v3d);
	GEN_GETTER_AND_SETTER_BY_VAL(floor);
private:		// functions
	template<EngineErrWhenEntNullIdObj ObjType>
	inline void _err_when_ent_id_is_null(ObjType* obj,
		const std::string& func_name) const
	{
		if (obj->ent_id() == ecs::ENT_NULL_ID)
		{
			const std::string err_msg(sconcat("Engine", func_name, "():",
				"Internal error.\n"));
			fprintf(stderr, err_msg.c_str());
			exit(1);
		}
	}

	inline EntIdSetVec2d& _curr_floor_playfield_ent_id_v2d()
	{
		return _playfield_ent_id_v3d.at(floor());
	}
	inline const EntIdSetVec2d& _curr_floor_playfield_ent_id_v2d() const
	{
		return _playfield_ent_id_v3d.at(floor());
	}
};

extern Engine engine;

} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_engine_class_hpp
