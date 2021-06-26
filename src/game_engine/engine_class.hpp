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

class Engine final
{
public:		// types
	using EntIdSetVec2d
		= std::vector<std::vector<std::set<ecs::EntId>>>;
public:		// constants
	static const PosVec2 PLAYFIELD_POS;
	static const SizeVec2 PLAYFIELD_SIZE_2D;

	static constexpr size_t HIGHEST_FLOOR = 0;
	static constexpr size_t LOWEST_FLOOR = 49;
private:		// variables
	ecs::Engine _ecs_engine;
	Window _screen, _playfield;
	std::vector<EntIdSetVec2d> _playfield_ent_id_set_vec_3d;
	size_t _floor = HIGHEST_FLOOR;
public:		// functions
	Engine();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Engine);
	~Engine();

	void position_ctor_callback(comp::Position* self);
	void position_dtor_callback(comp::Position* self);

	GEN_GETTER_BY_CON_REF(ecs_engine);
	GEN_GETTER_BY_CON_REF(screen);
	GEN_GETTER_BY_CON_REF(playfield);
	GEN_GETTER_BY_CON_REF(playfield_ent_id_set_vec_3d);
	GEN_GETTER_BY_VAL(floor);
private:		// functions
	inline EntIdSetVec2d& _curr_playfield_ent_id_set_vec_2d()
	{
		return _playfield_ent_id_set_vec_3d.at(floor());
	}
	inline const EntIdSetVec2d& _curr_playfield_ent_id_set_vec_2d() const
	{
		return _playfield_ent_id_set_vec_3d.at(floor());
	}
};

} // namespace game_engine

} // namespace dungwich_sandeon

#endif		// src_game_engine_engine_class_hpp
