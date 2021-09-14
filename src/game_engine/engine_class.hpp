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
#include "../input_kind_enum.hpp"
#include "basic_window_classes.hpp"
#include "menu_etc_classes.hpp"
#include "comp/general_comp_classes.hpp"
#include "comp/block_comp_classes.hpp"
#include "comp/ui_etc_comp_classes.hpp"

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
		LOG_WINDOW_POS, LOG_WINDOW_END_POS,
		HUD_WINDOW_POS, HUD_WINDOW_END_POS,
		POPUP_WINDOW_POS, POPUP_WINDOW_END_POS,
		YES_NO_WINDOW_POS, YES_NO_WINDOW_END_POS;

	// These are basement floors, going from B1F down to B50F
	static constexpr int
		LOWEST_FLOOR = 50, HIGHEST_FLOOR = 1,
		NUM_FLOORS = abs(HIGHEST_FLOOR - LOWEST_FLOOR) + 1;

public:		// variables
	ecs::Engine ecs_engine;
	Window 
		// The `Window` that contains the entities to display on screen 
		screen_window,

		// Auxilliary `Window`, which takes up the whole game window, for
		// things like the title screen, game options, and credits.
		aux_window,

		// The game world's `Window`.
		playfield_window,

		// `Window` for messages from the game.
		log_window,

		// The heads up display `Window`.
		hud_window,

		// A popup window for various tasks (inventory, shops, etc.)
		popup_window,

		// A window containing "yes" and "no" buttons.
		yes_no_window;

	Menu 
		// `Menu` for various tasks that take up the whole game window
		aux_menu,

		// The popup window's menu
		popup_menu,

		// The yes-no window's menu
		yes_no_menu;

	MsgLog
		log_msg_log,
		hud_msg_log;

	//InputKind initial_input_kind = InputKind::None,
	//	final_input_kind = InputKind::None;
	InputKind input_kind;

	class KeyStatus final
	{
	public:		// types
		enum KeyKind
		{
			LeftL,
			UpL,
			RightL,
			DownL,

			LeftR,
			UpR,
			RightR,
			DownR,

			ShoulderL,
			ShoulderR,

			Start,
			Select,

			LimKeyKind,
		};
	public:		// variables
		std::map<KeyKind, PrevCurrPair<bool>> state_map;
	public:		// functions
		inline KeyStatus()
		{
			auto init_state = [&](KeyKind key_kind) -> void
			{
				state_map[key_kind] = PrevCurrPair<bool>();
				state_map.at(key_kind)() = false;
				state_map.at(key_kind).back_up();
			};

			init_state(LeftL);
			init_state(UpL);
			init_state(RightL);
			init_state(DownL);

			init_state(LeftR);
			init_state(UpR);
			init_state(RightR);
			init_state(DownR);

			init_state(ShoulderL);
			init_state(ShoulderR);

			init_state(Start);
			init_state(Select);
		}
		inline PrevCurrPair<bool>& at(KeyKind key_kind)
		{
			return state_map.at(key_kind);
		}
		inline const PrevCurrPair<bool>& at(KeyKind key_kind) const
		{
			return state_map.at(key_kind);
		}

		inline bool any_key_went_up_just_now() const
		{
			for (const auto& item: state_map)
			{
				if (item.second.prev() && (!item.second()))
				{
					return true;
				}
			}
			return false;
		}
		inline bool any_key_went_down_just_now() const
		{
			for (const auto& item: state_map)
			{
				if ((!item.second.prev()) && item.second())
				{
					return true;
				}
			}
			return false;
		}
		inline bool has_changed() const
		{
			for (const auto& item: state_map)
			{
				if (item.second.has_changed())
				{
					return true;
				}
			}
			return false;
		}
	} key_status;

	//struct
	//{
	//	bool req_start = false;
	//	std::string text;
	//} text_input;

	int floor = HIGHEST_FLOOR;
private:		// variables
	// dimensions: floor, y, x
	std::vector<EntIdSetVec2d> _playfield_ent_id_v3d;

	//u64 _tick_counter = 0;

public:		// functions
	Engine();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Engine);
	~Engine();

	//void dbg_check_ecs_engine(const PosVec2& wb_pos=PosVec2(0, 0));

	void tick();

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
			const std::string err_msg(sconcat("Engine::", func_name,
				"(): Internal error.\n"));
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

extern Engine* engine;

} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_engine_class_hpp
