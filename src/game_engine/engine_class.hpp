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
#include "comp/general_comp_classes.hpp"
#include "comp/block_comp_classes.hpp"

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
		= std::vector<std::vector<ecs::EntIdSet>>;
public:		// constants
	static const PosVec2 PLAYFIELD_WINDOW_POS, PLAYFIELD_WINDOW_END_POS;
	static const SizeVec2 PLAYFIELD_WINDOW_SIZE_2D;

	static const PosVec2
		BOTTOM_MSG_WINDOW_POS, BOTTOM_MSG_WINDOW_END_POS,
		RIGHT_MSG_WINDOW_POS, RIGHT_MSG_WINDOW_END_POS,
		POPUP_WINDOW_POS, POPUP_WINDOW_END_POS;

	// These are basement floors, going from B1F down to B50F
	static constexpr int LOWEST_FLOOR = 50, HIGHEST_FLOOR = 1,
		NUM_FLOORS = abs(HIGHEST_FLOOR - LOWEST_FLOOR) + 1;
public:		// variables
	ecs::Engine ecs_engine;
	Window screen_window, title_screen_window, credits_window,
		playfield_window, bottom_msg_window, right_msg_window,
		popup_window;
	//InputKind initial_input_kind = InputKind::None,
	//	final_input_kind = InputKind::None;
	InputKind input_kind;

	struct
	{
		PrevCurrPair<bool>
			left_l, up_l, right_l, down_l,
			left_r, up_r, right_r, down_r,
			mod_1_l, mod_2_l,
			mod_1_r, mod_2_r,
			start, select;
		std::string character;
	} key_status;

	int floor = HIGHEST_FLOOR;
private:		// variables
	// dimensions: floor, y, x
	std::vector<EntIdSetVec2d> _playfield_ent_id_v3d;

public:		// functions
	Engine();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Engine);
	~Engine();

	void position_ctor_callback(comp::Position* obj);
	void position_dtor_callback(comp::Position* obj);
	void position_set_pos_callback(comp::Position* obj,
		const PosVec3& n_pos);

	GEN_GETTER_BY_CON_REF(playfield_ent_id_v3d);
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
		return _playfield_ent_id_v3d.at(floor);
	}
	inline const EntIdSetVec2d& _curr_floor_playfield_ent_id_v2d() const
	{
		return _playfield_ent_id_v3d.at(floor);
	}
};

extern Engine engine;

} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_engine_class_hpp
