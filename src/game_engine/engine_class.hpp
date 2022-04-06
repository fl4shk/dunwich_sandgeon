// This file is part of Dunwich Sandgeon.
// 
// Copyright 2022 FL4SHK
//
// Dunwich Sandgeon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// Dunwich Sandgeon is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Dunwich Sandgeon.  If not, see <https://www.gnu.org/licenses/>.

#ifndef src_game_engine_engine_class_hpp
#define src_game_engine_engine_class_hpp

// src/game_engine/engine_class.hpp

#include "../misc_includes.hpp"
#include "../input_kind_enum.hpp"
#include "window_class.hpp"
#include "menu_etc_classes.hpp"
#include "game_options_class.hpp"
#include "comp/general_comp_classes.hpp"
#include "window_size_2d_constants.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
//--------
enum class KeyKind: int
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

	Lim,
};
//--------
#define LIST_OF_GAME_MODES(X) \
	/* X(AuxStartup) */ \
	X(TitleScreen) \
	X(Options) \
	\
	/* X(Credits) */ \
	\
	X(FileSelect) \
	X(DungeonGen) \
	/* X(Main) */ \
	\
	/* X(PopupShop) */ \
	/* X(YesNoShop) */ \

// An `enum` to specify which `game_engine::Window` is the
// currently-selected one, as well as what game mode the game is in.
enum class GameMode
{
	#define X(arg) \
		arg,
	LIST_OF_GAME_MODES(X)
	#undef X
};
//--------
template<typename ObjT>
concept EngineErrWhenEntNullIdObj = requires(ObjT obj)
{
	{ obj.ent_id() } -> std::same_as<ecs::EntId>;
};

class Engine final
{
public:		// types
	//using EntIdSetVec2d
	//	= std::vector<std::vector<ecs::EntIdSet>>;

public:		// constants
	// These are basement floors, going from B1F down to B25F
	static constexpr i32
		LOWEST_FLOOR = 25, HIGHEST_FLOOR = 1,
		//LOWEST_FLOOR = 5, HIGHEST_FLOOR = 1,
		NUM_FLOORS = std::abs(HIGHEST_FLOOR - LOWEST_FLOOR) + 1;

	static const std::string
		SAVE_FILE_NAME,
		DEBUG_SAVE_FILE_NAME;

	static constexpr int
		//NUM_FILES = 9;
		NUM_FILES = 3;
		//NUM_FILES = 1;
public:		// types
	class NonEcsSerData final
	{
	public:		// variables
		#define MEMB_LIST_ENGINE_NON_ECS_SER_DATA(X) \
			X(log_msg_log, std::nullopt) \
			X(hud_msg_log, std::nullopt) \
			X(floor, std::nullopt) \
			X(pfield_ent_id_map, std::nullopt)

		MsgLog
			log_msg_log,
			hud_msg_log;

		int floor = HIGHEST_FLOOR;

		// dimensions: floor, y, x
		// "pfield" is short for "playfield".
		// I needed to have a shorter variable name, so I changed the name
		// of this variable and related functions
		std::unordered_map<PosVec3, ecs::EntIdSet> pfield_ent_id_map;
	//private:		// static functions
	//	static decltype(pfield_ent_id_v3d)
	//		_gen_blank_pfield_ent_id_v3d();
	public:		// functions
		NonEcsSerData();
		NonEcsSerData(const binser::Value& bv);
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(NonEcsSerData);
		~NonEcsSerData();

		operator binser::Value () const;
	};

public:		// serialized variables
	ecs::Engine ecs_engine;

	#define MEMB_SER_LIST_ENGINE(X) \
		X(ecs_engine, std::nullopt) \
		X(game_options, std::nullopt) \
		X(_non_ecs_ser_data_vec, std::nullopt) \
		\
		/* X(_screen_window_vec, std::nullopt) */ \
		/* X(_aux_window_vec, std::nullopt) */ \
		/* X(_pfield_window_vec, std::nullopt) */ \
		/* X(_log_window_vec, std::nullopt) */ \
		/* X(_hud_window_vec, std::nullopt) */ \
		/* X(_yes_no_window_vec, std::nullopt) */ \
		/* X(_text_yes_no_window_vec, std::nullopt) */

	GameOptions game_options;
private:		// serialized variables
	std::vector<NonEcsSerData> _non_ecs_ser_data_vec;
public:		// non-serialized variables
	EngineKeyStatus key_status;

	////InputKind initial_input_kind = InputKind::None,
	////	final_input_kind = InputKind::None;
	//InputKind input_kind;

	//struct
	//{
	//	bool req_start = false;
	//	std::string text;
	//} text_input;
private:		// variables
	GameMode _game_mode = GameMode::TitleScreen;
private:		// non-serialized variables
	std::vector<Window>
		// The `Window` that contains the entities to display on screen 
		_screen_window_vec,

		// Auxilliary `Window`s, which takes up the whole game window, for
		// things like the title screen, game options, and credits.
		_aux_window_vec,

		// The game world's `Window`s.
		_pfield_window_vec,

		// `Window`s for messages from the game.
		_log_window_vec,

		// The heads up display `Window`.
		_hud_window_vec,

		// Popup `Window`s for various tasks (inventory, shops, etc.)
		_popup_window_vec,

		// `Window`s containing just "yes" and "no" buttons.
		_yes_no_window_vec,

		// Larger-than-`_yes_no_window_vec` `Window`s containing "yes" and
		// "no" buttons, and also some text at the top.
		_text_yes_no_window_vec;

	std::vector<Menu>
		// `Menu`s for various tasks that take up the whole game window
		_aux_menu_vec,

		// The popup windows' menus
		_popup_menu_vec,

		// The small yes-no windows' menus
		_yes_no_menu_vec,

		// The with-text yes-no windows' menus
		_text_yes_no_menu_vec;
public:		// constants
	static constexpr int
		USE_CURR_FILE_NUM = -1,
		USE_SRC_FILE_NUM = -2,
		USE_COPY_DST_FILE_NUM = -3;
private:		// non-serialized variables
	bool _did_init_window_clear = false;
	// File numbers selected via HorizPickers, though `curr_file_num` is
	// also the current file number used for indexing into
	// `_non_ecs_ser_data_vec`.
	int* _curr_file_num = nullptr;
public:		// non-serialized variables
	int
		src_file_num = 0,
		copy_dst_file_num = 0;

	// File number state
	enum class FnState: int
	{
		Curr,
		Src,
	};
	FnState fn_state = FnState::Curr;
private:		// variables
	//u64 _tick_counter = 0;
public:		// functions
	Engine(bool do_create_or_load=true);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Engine);
	~Engine();
	operator binser::Value () const;

	void deserialize(const binser::Value& bv);

	inline void err(const auto&... objs) const
	{
		printerr(objs...);
		exit(1);
	}

	//void dbg_check_ecs_engine(const PosVec2& wb_pos=PosVec2(0, 0));

	//inline void tick()
	//{
	//	ecs_engine.tick();
	//}
	void tick();
private:		// functions
	void _create_or_load_save_file_etc();
	//void _load_from_binser();
	void _save_to_binser(bool do_create_or_load=false);
public:		// functions
	void save_and_quit();
	void save_and_return_to_title();

	void copy_file();
	void erase_file();
private:		// functions
	void _inner_draw_menu_w_pre_clear(Window& window, Menu& menu,
		int file_num);
public:		// functions
	inline void draw_aux_menu_w_pre_clear(int file_num)
	{
		_inner_draw_menu_w_pre_clear(aux_window(file_num),
			aux_menu(file_num), file_num);
	}
	inline void draw_aux_menu_w_pre_clear_cfn()
	{
		draw_aux_menu_w_pre_clear(USE_CURR_FILE_NUM);
	}

	inline void draw_popup_menu_w_pre_clear(int file_num)
	{
		_inner_draw_menu_w_pre_clear(popup_window(file_num),
			popup_menu(file_num), file_num);
	}
	inline void draw_popup_menu_w_pre_clear_cfn()
	{
		draw_popup_menu_w_pre_clear(USE_CURR_FILE_NUM);
	}

	inline void draw_yes_no_menu_w_pre_clear(int file_num)
	{
		_inner_draw_menu_w_pre_clear(yes_no_window(file_num),
			yes_no_menu(file_num), file_num);
	}
	inline void draw_yes_no_menu_w_pre_clear_cfn()
	{
		draw_yes_no_menu_w_pre_clear(USE_CURR_FILE_NUM);
	}

	inline void draw_text_yes_no_menu_w_pre_clear(int file_num)
	{
		_inner_draw_menu_w_pre_clear(text_yes_no_window(file_num),
			text_yes_no_menu(file_num), file_num);
	}
	inline void draw_text_yes_no_menu_w_pre_clear_cfn()
	{
		draw_text_yes_no_menu_w_pre_clear(USE_CURR_FILE_NUM);
	}
public:		// `_non_ecs_ser_data_vec` accessor functions
	//--------
	inline NonEcsSerData& non_ecs_ser_data(int file_num)
	{
		return _non_ecs_ser_data_vec.at(_sel_file_num(file_num));
	}
	inline const NonEcsSerData& non_ecs_ser_data(int file_num) const
	{
		return _non_ecs_ser_data_vec.at(_sel_file_num(file_num));
	}
	inline NonEcsSerData& non_ecs_ser_data_cfn()
	{
		return non_ecs_ser_data(USE_CURR_FILE_NUM);
	}
	inline const NonEcsSerData& non_ecs_ser_data_cfn() const
	{
		return non_ecs_ser_data(USE_CURR_FILE_NUM);
	}
	//--------
	inline MsgLog& log_msg_log(int file_num)
	{
		return non_ecs_ser_data(file_num).log_msg_log;
	}
	inline const MsgLog& log_msg_log(int file_num) const
	{
		return non_ecs_ser_data(file_num).log_msg_log;
	}
	inline MsgLog& log_msg_log_cfn()
	{
		return log_msg_log(USE_CURR_FILE_NUM);
	}
	inline const MsgLog& log_msg_log_cfn() const
	{
		return log_msg_log(USE_CURR_FILE_NUM);
	}
	//--------
	inline MsgLog& hud_msg_log(int file_num)
	{
		return non_ecs_ser_data(file_num).hud_msg_log;
	}
	inline const MsgLog& hud_msg_log(int file_num) const
	{
		return non_ecs_ser_data(file_num).hud_msg_log;
	}
	inline MsgLog& hud_msg_log_cfn()
	{
		return hud_msg_log(USE_CURR_FILE_NUM);
	}
	inline const MsgLog& hud_msg_log_cfn() const
	{
		return hud_msg_log(USE_CURR_FILE_NUM);
	}
	//--------
	inline int& floor(int file_num)
	{
		return non_ecs_ser_data(file_num).floor;
	}
	inline const int& floor(int file_num) const
	{
		return non_ecs_ser_data(file_num).floor;
	}
	inline int& floor_cfn()
	{
		return floor(USE_CURR_FILE_NUM);
	}
	inline const int& floor_cfn() const
	{
		return floor(USE_CURR_FILE_NUM);
	}
	//--------
	inline ecs::EntIdSet& pfield_ent_id_set(int file_num,
		const PosVec3& pos)
	{
		return non_ecs_ser_data(file_num).pfield_ent_id_map[pos];
	}
	//inline const ecs::EntIdSet& pfield_ent_id_set(int file_num,
	//	const PosVec3& pos) const
	//{
	//	return non_ecs_ser_data(file_num).pfield_ent_id_map[pos];
	//}
	inline ecs::EntIdSet& pfield_ent_id_set_cfn(const PosVec3& pos)
	{
		return pfield_ent_id_set(USE_CURR_FILE_NUM, pos);
	}
	//inline const ecs::EntIdSet& pfield_ent_id_set_cfn(const PosVec3& pos)
	//	const
	//{
	//	return pfield_ent_id_set(USE_CURR_FILE_NUM, pos);
	//}
	//--------
	inline ecs::EntIdSet& pfield_ent_id_set(int file_num,
		const PosVec2& pos_2d)
	{
		return pfield_ent_id_set(file_num, to_pos_vec3(file_num, pos_2d));
	}
	//inline const ecs::EntIdSet& pfield_ent_id_set(int file_num,
	//	const PosVec2& pos_2d) const
	//{
	//	return pfield_ent_id_set(file_num, to_pos_vec3(file_num, pos_2d));
	//}
	inline ecs::EntIdSet& pfield_ent_id_set_cfn(const PosVec2& pos_2d)
	{
		return pfield_ent_id_set_cfn(to_pos_vec3_cfn(pos_2d));
	}
	//inline const ecs::EntIdSet& pfield_ent_id_set_cfn
	//	(const PosVec2& pos_2d) const
	//{
	//	return pfield_ent_id_set_cfn(to_pos_vec3_cfn(pos_2d));
	//}
	//inline EntIdSetVec2d& pfield_ent_id_v2d(int file_num)
	//{
	//	return pfield_ent_id_v3d(file_num).at(floor(file_num));
	//}
	//inline const EntIdSetVec2d& pfield_ent_id_v2d(int file_num) const
	//{
	//	return pfield_ent_id_v3d(file_num).at(floor(file_num));
	//}
	//inline EntIdSetVec2d& pfield_ent_id_v2d_cfn()
	//{
	//	return pfield_ent_id_v2d(USE_CURR_FILE_NUM);
	//}
	//inline const EntIdSetVec2d& pfield_ent_id_v2d_cfn() const
	//{
	//	return pfield_ent_id_v2d(USE_CURR_FILE_NUM);
	//}
	//--------
public:		// functions
	//--------
	inline PosVec3 to_pos_vec3(int file_num, const PosVec2& pos_2d) const
	{
		return PosVec3(pos_2d.x, pos_2d.y, floor(file_num));
	}
	inline PosVec3 to_pos_vec3_cfn(const PosVec2& pos_2d) const
	{
		return to_pos_vec3(USE_CURR_FILE_NUM, pos_2d);
	}
	//--------
public:		// functions
	//--------
	inline int fn_state_index() const
	{
		return
			fn_state == FnState::Curr
			? *curr_file_num()
			: src_file_num;
	}
	//--------
public:		// `Window` and `Menu` accessor functions
	//--------
	//inline Window& screen_window(int file_num)
	//{
	//	return _screen_window_vec.at(_sel_file_num(file_num));
	//}
	//inline const Window& screen_window(int file_num) const
	//{
	//	return _screen_window_vec.at(_sel_file_num(file_num));
	//}
	//inline Window& screen_window_cfn()
	//{
	//	return screen_window(USE_CURR_FILE_NUM);
	//}
	//inline const Window& screen_window_cfn() const
	//{
	//	return screen_window(USE_CURR_FILE_NUM);
	//}
	inline Window& screen_window()
	{
		return _screen_window_vec.at(fn_state_index());
	}
	inline const Window& screen_window() const
	{
		return _screen_window_vec.at(fn_state_index());
	}
	//--------
	inline Window& aux_window(int file_num)
	{
		return _aux_window_vec.at(_sel_file_num(file_num));
	}
	inline const Window& aux_window(int file_num) const
	{
		return _aux_window_vec.at(_sel_file_num(file_num));
	}
	inline Window& aux_window_cfn()
	{
		return aux_window(USE_CURR_FILE_NUM);
	}
	inline const Window& aux_window_cfn() const
	{
		return aux_window(USE_CURR_FILE_NUM);
	}
	//--------
	inline Window& pfield_window(int file_num)
	{
		return _pfield_window_vec.at(_sel_file_num(file_num));
	}
	inline const Window& pfield_window(int file_num) const
	{
		return _pfield_window_vec.at(_sel_file_num(file_num));
	}
	inline Window& pfield_window_cfn()
	{
		return pfield_window(USE_CURR_FILE_NUM);
	}
	inline const Window& pfield_window_cfn() const
	{
		return pfield_window(USE_CURR_FILE_NUM);
	}
	//--------
	inline Window& log_window(int file_num)
	{
		return _log_window_vec.at(_sel_file_num(file_num));
	}
	inline const Window& log_window(int file_num) const
	{
		return _log_window_vec.at(_sel_file_num(file_num));
	}
	inline Window& log_window_cfn()
	{
		return log_window(USE_CURR_FILE_NUM);
	}
	inline const Window& log_window_cfn() const
	{
		return log_window(USE_CURR_FILE_NUM);
	}
	//--------
	inline Window& hud_window(int file_num)
	{
		return _hud_window_vec.at(_sel_file_num(file_num));
	}
	inline const Window& hud_window(int file_num) const
	{
		return _hud_window_vec.at(_sel_file_num(file_num));
	}
	inline Window& hud_window_cfn()
	{
		return hud_window(USE_CURR_FILE_NUM);
	}
	inline const Window& hud_window_cfn() const
	{
		return hud_window(USE_CURR_FILE_NUM);
	}
	//--------
	inline Window& popup_window(int file_num)
	{
		return _popup_window_vec.at(_sel_file_num(file_num));
	}
	inline const Window& popup_window(int file_num) const
	{
		return _popup_window_vec.at(_sel_file_num(file_num));
	}
	inline Window& popup_window_cfn()
	{
		return popup_window(USE_CURR_FILE_NUM);
	}
	inline const Window& popup_window_cfn() const
	{
		return popup_window(USE_CURR_FILE_NUM);
	}
	//--------
	inline Window& yes_no_window(int file_num)
	{
		return _yes_no_window_vec.at(_sel_file_num(file_num));
	}
	inline const Window& yes_no_window(int file_num) const
	{
		return _yes_no_window_vec.at(_sel_file_num(file_num));
	}
	inline Window& yes_no_window_cfn()
	{
		return yes_no_window(USE_CURR_FILE_NUM);
	}
	inline const Window& yes_no_window_cfn() const
	{
		return yes_no_window(USE_CURR_FILE_NUM);
	}
	//--------
	inline Window& text_yes_no_window(int file_num)
	{
		return _text_yes_no_window_vec.at(_sel_file_num(file_num));
	}
	inline const Window& text_yes_no_window(int file_num) const
	{
		return _text_yes_no_window_vec.at(_sel_file_num(file_num));
	}
	inline Window& text_yes_no_window_cfn()
	{
		return text_yes_no_window(USE_CURR_FILE_NUM);
	}
	inline const Window& text_yes_no_window_cfn() const
	{
		return text_yes_no_window(USE_CURR_FILE_NUM);
	}
	//--------
	inline Menu& aux_menu(int file_num)
	{
		return _aux_menu_vec.at(_sel_file_num(file_num));
	}
	inline const Menu& aux_menu(int file_num) const
	{
		return _aux_menu_vec.at(_sel_file_num(file_num));
	}
	inline Menu& aux_menu_cfn()
	{
		return aux_menu(USE_CURR_FILE_NUM);
	}
	inline const Menu& aux_menu_cfn() const
	{
		return aux_menu(USE_CURR_FILE_NUM);
	}
	//--------
	inline Menu& popup_menu(int file_num)
	{
		return _popup_menu_vec.at(_sel_file_num(file_num));
	}
	inline const Menu& popup_menu(int file_num) const
	{
		return _popup_menu_vec.at(_sel_file_num(file_num));
	}
	inline Menu& popup_menu_cfn()
	{
		return popup_menu(USE_CURR_FILE_NUM);
	}
	inline const Menu& popup_menu_cfn() const
	{
		return popup_menu(USE_CURR_FILE_NUM);
	}
	//--------
	inline Menu& yes_no_menu(int file_num)
	{
		return _yes_no_menu_vec.at(_sel_file_num(file_num));
	}
	inline const Menu& yes_no_menu(int file_num) const
	{
		return _yes_no_menu_vec.at(_sel_file_num(file_num));
	}
	inline Menu& yes_no_menu_cfn()
	{
		return yes_no_menu(USE_CURR_FILE_NUM);
	}
	inline const Menu& yes_no_menu_cfn() const
	{
		return yes_no_menu(USE_CURR_FILE_NUM);
	}
	//--------
	inline Menu& text_yes_no_menu(int file_num)
	{
		return _text_yes_no_menu_vec.at(_sel_file_num(file_num));
	}
	inline const Menu& text_yes_no_menu(int file_num) const
	{
		return _text_yes_no_menu_vec.at(_sel_file_num(file_num));
	}
	inline Menu& text_yes_no_menu_cfn()
	{
		return text_yes_no_menu(USE_CURR_FILE_NUM);
	}
	inline const Menu& text_yes_no_menu_cfn() const
	{
		return text_yes_no_menu(USE_CURR_FILE_NUM);
	}
	//--------
private:		// static functions
	inline int _sel_file_num(int some_file_num) const
	{
		//return (some_file_num == USE_CURR_FILE_NUM)
		//	? *curr_file_num()
		//	: some_file_num;
		switch (some_file_num)
		{
		//--------
		case USE_CURR_FILE_NUM:
			return *curr_file_num();
			break;
		case USE_SRC_FILE_NUM:
			return src_file_num;
			break;
		case USE_COPY_DST_FILE_NUM:
			return copy_dst_file_num;
		default:
			return some_file_num;
			break;
		//--------
		}
	}
public:		// functions
	void position_ctor_callback(comp::Position* obj);
	void position_dtor_callback(comp::Position* obj);
	void position_set_pos_callback(comp::Position* obj,
		const PosVec3& n_pos);

	template<typename SelfT>
	inline Menu build_yes_no_menu(SelfT* self, int file_num,
		const std::function<void(SelfT*)>& yes_func,
		const std::function<void(SelfT*)>& no_func)
	{
		return Menu
		(
			"yes",
			yes_no_window(file_num).size_2d(),
			Menu::build_node_map
			({
				Menu::build_action_button_knc_pair
				(
					"yes",
					"Yes",
					self,
					yes_func
				),
				Menu::build_action_button_knc_pair
				(
					"no",
					"No",
					self,
					no_func
				),
			}),
			Vec2(false, true)
		);
	}
	template<typename SelfT>
	inline Menu build_text_yes_no_menu(SelfT* self, int file_num,
		const std::string& s_text,
		const std::function<void(SelfT*)>& yes_func,
		const std::function<void(SelfT*)>& no_func,
		uint s_tab_amount=0)
	{
		return Menu
		(
			"yes",
			text_yes_no_window(file_num).size_2d(),
			Menu::build_node_map
			({
				Menu::build_text_only_knc_pair
				(
					"<text[0]>",
					s_text
				),
				Menu::build_action_button_knc_pair
				(
					"yes",
					"Yes",
					self,
					yes_func
				),
				Menu::build_action_button_knc_pair
				(
					"no",
					"No",
					self,
					no_func
				),
			}),
			Vec2(false, true),
			s_tab_amount
		);
	}


	GameMode& set_game_mode(GameMode n_game_mode);
	inline decltype(_game_mode) game_mode() const
	{
		return _game_mode;
	}

	GEN_GETTER_BY_VAL(curr_file_num);
private:		// functions
	//static void _yes_no_menu_act_yes(Engine* self);
	//static void _yes_no_menu_act_no(Engine* self);
	template<EngineErrWhenEntNullIdObj ObjT>
	inline void _err_when_ent_id_is_null(ObjT* obj,
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
};

extern Engine* engine;
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_engine_class_hpp
