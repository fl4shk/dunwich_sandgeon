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
enum class KeyKind: i32
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
public:		// constants
	// These are basement floors, going from B1F down to B25F
	static constexpr i32
		LOWEST_FLOOR = 25, HIGHEST_FLOOR = 1,
		//LOWEST_FLOOR = 5, HIGHEST_FLOOR = 1,
		NUM_FLOORS = std::abs(HIGHEST_FLOOR - LOWEST_FLOOR) + 1;

	static const std::string
		DEFAULT_SAVE_FILE_NAME,
		DEBUG_SAVE_FILE_NAME;

	static constexpr ecs::FileNum
		//NUM_FILES = 9;
		NUM_FILES = 3;
		//NUM_FILES = 1;
public:		// types
	//using EntIdSetVec2d
	//	= std::vector<std::vector<ecs::EntIdSet>>;

	//using Rng = pcg32;
	using Rng = pcg64;
	using LayoutRngArr = std::array<Rng, NUM_FLOORS>;
	using LayoutRngA2d = std::array<LayoutRngArr, NUM_FILES>;
public:		// types
	class NonEcsSerData final
	{
		friend class Engine;
	public:		// variables
		#define MEMB_AUTOSER_LIST_ENGINE_NON_ECS_SER_DATA(X) \
			X(did_init_save_file, std::nullopt) \
			\
			X(log_msg_log, std::nullopt) \
			X(hud_msg_log, std::nullopt) \
			\
			X(floor, std::nullopt) \
			X(pfield_ent_id_map, std::nullopt) \
			\
			X(_base_rng_seed, std::nullopt)

		bool did_init_save_file = false;

		MsgLog
			log_msg_log,
			hud_msg_log;

		i32 floor = HIGHEST_FLOOR;

		// dimensions: floor, y, x
		// "pfield" is short for "playfield".
		// I needed to have a shorter variable name, so I changed the name
		// of this variable and related functions
		std::unordered_map<PosVec3, ecs::EntIdSet> pfield_ent_id_map;

	private:		// variables
		u64 _base_rng_seed = 0;
		// The RNG to use for tasks other than initial floor layout
		// generation
		Rng _rng;
	//private:		// static functions
	//	static decltype(pfield_ent_id_v3d)
	//		_gen_blank_pfield_ent_id_v3d();
	public:		// functions
		NonEcsSerData();
		NonEcsSerData(const binser::Value& bv);
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(NonEcsSerData);
		~NonEcsSerData();

		operator binser::Value () const;

		inline size_t seed_layout_rng_arr(LayoutRngArr& layout_rng_arr)
			const
		{
			size_t i;
			for (i=0; i<layout_rng_arr.size(); ++i)
			{
				//layout_rng_arr.at(i).seed(_base_rng_seed + i);
				layout_rng_arr.at(i) = Rng(_base_rng_seed + i);
			}
			return i;
		}
		inline void seed_rngs_etc(LayoutRngArr& layout_rng_arr)
		{
			_base_rng_seed = get_hrc_now_rng_seed();

			const size_t i = seed_layout_rng_arr(layout_rng_arr);

			//_rng.seed(_base_rng_seed + i);
			_rng = Rng(_base_rng_seed + i);
		}

		//template<typename RetT=decltype(_rng())>
		//inline std::remove_cvref_t<RetT> rand()
		//	requires std::integral<std::remove_cvref_t<RetT>>
		template<typename T=decltype(std::declval<Rng>())>
		inline auto rand()
		{
			return rng_run<T>(_rng);
		}
		template<typename T>
		inline auto rand(const T& max_val, bool saturate=false)
		{
			return rng_run<T>(_rng, max_val, saturate);
		}
		template<typename T>
		inline auto rand_scaled(const T& scale)
		{
			return rng_run_scaled<T>(_rng, scale);
		}
		template<typename T>
		inline auto rand_scaled(const T& scale, const T& max_val,
			bool saturate=false)
		{
			return rng_run_scaled<T>(_rng, scale, max_val, saturate);
		}
	};
private:		// non-serialized variables
	int _argc = 0;
	char** _argv = nullptr;
	std::string _save_file_name;

	// The RNGs for each file's floors' initial layouts, including the
	// parts that are static (which are stored in the
	// `comp::StaticTileMap`).
	LayoutRngA2d _layout_rng_a2d;
public:		// serialized variables
	ecs::Engine ecs_engine;

	#define MEMB_SER_LIST_ENGINE(X) \
		X(ecs_engine, std::nullopt) \
		X(game_options, std::nullopt) \
		X(_non_ecs_ser_data_arr, std::nullopt) \
		\
		/* X(_screen_window, std::nullopt) */ \
		/* X(_aux_window, std::nullopt) */ \
		/* X(_pfield_window, std::nullopt) */ \
		/* X(_log_window, std::nullopt) */ \
		/* X(_hud_window, std::nullopt) */ \
		/* X(_yes_no_window, std::nullopt) */ \
		/* X(_text_yes_no_window, std::nullopt) */

	GameOptions game_options;
private:		// serialized variables
	std::array<NonEcsSerData, NUM_FILES> _non_ecs_ser_data_arr;
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
private:		// non-serialized variables
	GameMode _game_mode = GameMode::TitleScreen;
public:		// non-serialized variables
	Window
		// The `Window` that contains the entities to display on screen 
		screen_window,

		// Auxilliary `Window`, which takes up the whole game window, for
		// things like the title screen, game options, and credits.
		aux_window,

		// The game world's `Window`.
		pfield_window,

		// `Window` for messages from the game.
		log_window,

		// The heads up display `Window`.
		hud_window,

		// Popup `Window` for various tasks (inventory, shops, etc.)
		popup_window,

		// `Window` containing just "yes" and "no" buttons.
		yes_no_window,

		// Larger-than-`yes_no_window` `Window` containing "yes" and
		// "no" buttons, and also some text at the top.
		text_yes_no_window;

	Menu
		// `Menu` for various tasks that take up the whole game window
		aux_menu,

		// The popup window's menu
		popup_menu,

		// The small yes-no window's menu
		yes_no_menu,

		// The with-text yes-no window's menu
		text_yes_no_menu;
public:		// constants
	static constexpr int
		USE_CURR_FILE_NUM = ecs::Engine::USE_CURR_FILE_NUM;
		//USE_SRC_FILE_NUM = ecs::Engine::USE_SRC_FILE_NUM,
		//USE_COPY_DST_FILE_NUM = ecs::Engine::USE_COPY_DST_FILE_NUM;
private:		// non-serialized variables
	bool _did_init_window_clear = false;
	// File numbers selected via HorizPickers, though `curr_file_num` is
	// also the current file number used for indexing into
	// `_non_ecs_ser_data_arr`.
	ecs::FileNum
		* _curr_file_num = nullptr,
		* _src_file_num = nullptr,
		* _copy_dst_file_num = nullptr;
public:		// non-serialized variables

	// File number state
	//enum class FnState: int
	//{
	//	Curr,
	//	Src,
	//};
	//FnState fn_state = FnState::Curr;
private:		// variables
	//u64 _tick_counter = 0;
public:		// functions
	Engine(int s_argc, char** s_argv, bool do_create_or_load=true);
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
	void _inner_draw_menu_w_pre_clear(Window& window, Menu& menu);
public:		// functions
	//--------
	inline void draw_aux_menu_w_pre_clear()
	{
		_inner_draw_menu_w_pre_clear(aux_window, aux_menu);
	}
	inline void draw_popup_menu_w_pre_clear()
	{
		_inner_draw_menu_w_pre_clear(popup_window, popup_menu);
	}
	inline void draw_yes_no_menu_w_pre_clear()
	{
		_inner_draw_menu_w_pre_clear(yes_no_window, yes_no_menu);
	}
	inline void draw_text_yes_no_menu_w_pre_clear()
	{
		_inner_draw_menu_w_pre_clear(text_yes_no_window, text_yes_no_menu);
	}
	//--------
	inline LayoutRngArr& layout_rng_arr_fn(ecs::FileNum file_num)
	{
		return _layout_rng_a2d.at(_sel_file_num(file_num));
	}
	inline const LayoutRngArr& layout_rng_arr_fn(ecs::FileNum file_num)
		const
	{
		return _layout_rng_a2d.at(_sel_file_num(file_num));
	}
	inline LayoutRngArr& layout_rng_arr()
	{
		return layout_rng_arr_fn(USE_CURR_FILE_NUM);
	}
	inline const LayoutRngArr& layout_rng_arr() const
	{
		return layout_rng_arr_fn(USE_CURR_FILE_NUM);
	}

	inline auto layout_rand()
	{
		return layout_rng_arr().at(floor())();
	}

	inline std::ostream& dbg_osprint_layout_rng_a2d(std::ostream& os) const
	{
		osprintout(os, "Engine::dbg_osprint_layout_rng_a2d(): Start\n");

		for (ecs::FileNum file_num=0; file_num<NUM_FILES; ++file_num)
		{
			dbg_osprint_layout_rng_arr_fn(os, file_num);

			if (file_num + 1 < NUM_FILES)
			{
				osprintout(os, "\n");
			}
		}

		osprintout(os, "Engine::dbg_osprint_layout_rng_a2d(): End\n\n");
		return os;
	}
	inline std::ostream& dbg_osprint_layout_rng_arr_fn(std::ostream& os,
		ecs::FileNum file_num) const
	{
		const auto& lr_arr = layout_rng_arr_fn(file_num);

		for (size_t i=0; i<lr_arr.size(); ++i)
		{
			osprintout(os, i, ": ", lr_arr.at(i), "\n");
		}

		return os;
	}
	//inline void dbg_osprint_layout_rng_arr() const
	//{
	//	dbg_osprint_layout_rng_arr_fn(USE_CURR_FILE_NUM);
	//}
	//--------
public:		// `_non_ecs_ser_data_arr` accessor functions
	//--------
	inline NonEcsSerData& non_ecs_ser_data_fn(ecs::FileNum file_num)
	{
		return _non_ecs_ser_data_arr.at(_sel_file_num(file_num));
	}
	inline const NonEcsSerData& non_ecs_ser_data_fn(ecs::FileNum file_num)
		const
	{
		return _non_ecs_ser_data_arr.at(_sel_file_num(file_num));
	}
	inline NonEcsSerData& non_ecs_ser_data()
	{
		return non_ecs_ser_data_fn(USE_CURR_FILE_NUM);
	}
	inline const NonEcsSerData& non_ecs_ser_data() const
	{
		return non_ecs_ser_data_fn(USE_CURR_FILE_NUM);
	}
	//--------
	inline bool& did_init_save_file_fn(ecs::FileNum file_num)
	{
		return non_ecs_ser_data_fn(file_num).did_init_save_file;
	}
	inline const bool& did_init_save_file_fn(ecs::FileNum file_num) const
	{
		return non_ecs_ser_data_fn(file_num).did_init_save_file;
	}
	inline bool& did_init_save_file()
	{
		return did_init_save_file_fn(USE_CURR_FILE_NUM);
	}
	inline const bool& did_init_save_file() const
	{
		return did_init_save_file_fn(USE_CURR_FILE_NUM);
	}
	//--------
	inline MsgLog& log_msg_log_fn(ecs::FileNum file_num)
	{
		return non_ecs_ser_data_fn(file_num).log_msg_log;
	}
	inline const MsgLog& log_msg_log_fn(ecs::FileNum file_num) const
	{
		return non_ecs_ser_data_fn(file_num).log_msg_log;
	}
	inline MsgLog& log_msg_log()
	{
		return log_msg_log_fn(USE_CURR_FILE_NUM);
	}
	inline const MsgLog& log_msg_log() const
	{
		return log_msg_log_fn(USE_CURR_FILE_NUM);
	}
	//--------
	inline MsgLog& hud_msg_log_fn(ecs::FileNum file_num)
	{
		return non_ecs_ser_data_fn(file_num).hud_msg_log;
	}
	inline const MsgLog& hud_msg_log_fn(ecs::FileNum file_num) const
	{
		return non_ecs_ser_data_fn(file_num).hud_msg_log;
	}
	inline MsgLog& hud_msg_log()
	{
		return hud_msg_log_fn(USE_CURR_FILE_NUM);
	}
	inline const MsgLog& hud_msg_log() const
	{
		return hud_msg_log_fn(USE_CURR_FILE_NUM);
	}
	//--------
	inline int& floor_fn(ecs::FileNum file_num)
	{
		return non_ecs_ser_data_fn(file_num).floor;
	}
	inline const int& floor_fn(ecs::FileNum file_num) const
	{
		return non_ecs_ser_data_fn(file_num).floor;
	}
	inline int& floor()
	{
		return floor_fn(USE_CURR_FILE_NUM);
	}
	inline const int& floor() const
	{
		return floor_fn(USE_CURR_FILE_NUM);
	}
	//--------
	inline ecs::EntIdSet& pfield_ent_id_set_fn(ecs::FileNum file_num,
		const PosVec3& pos)
	{
		return non_ecs_ser_data_fn(file_num).pfield_ent_id_map[pos];
	}
	//inline const ecs::EntIdSet& pfield_ent_id_set_fn
	//	(ecs::FileNum file_num, const PosVec3& pos) const
	//{
	//	return non_ecs_ser_data(file_num).pfield_ent_id_map[pos];
	//}
	inline ecs::EntIdSet& pfield_ent_id_set(const PosVec3& pos)
	{
		return pfield_ent_id_set_fn(USE_CURR_FILE_NUM, pos);
	}
	//inline const ecs::EntIdSet& pfield_ent_id_set(const PosVec3& pos)
	//	const
	//{
	//	return pfield_ent_id_set_fn(USE_CURR_FILE_NUM, pos);
	//}
	//--------
	inline ecs::EntIdSet& pfield_ent_id_set_fn(ecs::FileNum file_num,
		const PosVec2& pos_2d)
	{
		return pfield_ent_id_set_fn(file_num,
			to_pos_vec3_fn(file_num, pos_2d));
	}
	//inline const ecs::EntIdSet& pfield_ent_id_set_fn(ecs::FileNum file_num,
	//	const PosVec2& pos_2d) const
	//{
	//	return pfield_ent_id_set_fn(file_num,
	//		to_pos_vec3_fn(file_num, pos_2d));
	//}
	inline ecs::EntIdSet& pfield_ent_id_set(const PosVec2& pos_2d)
	{
		return pfield_ent_id_set(to_pos_vec3(pos_2d));
	}
	//inline const ecs::EntIdSet& pfield_ent_id_set(const PosVec2& pos_2d)
	//	const
	//{
	//	return pfield_ent_id_set(to_pos_vec3(pos_2d));
	//}
	//inline EntIdSetVec2d& pfield_ent_id_v2d_fn(ecs::FileNum file_num)
	//{
	//	return pfield_ent_id_v3d_fn(file_num).at(floor_fn(file_num));
	//}
	//inline const EntIdSetVec2d& pfield_ent_id_v2d_fn(ecs::FileNum file_num)
	//	const
	//{
	//	return pfield_ent_id_v3d_fn(file_num).at(floor_fn(file_num));
	//}
	//inline EntIdSetVec2d& pfield_ent_id_v2d()
	//{
	//	return pfield_ent_id_v2d_fn(USE_CURR_FILE_NUM);
	//}
	//inline const EntIdSetVec2d& pfield_ent_id_v2d() const
	//{
	//	return pfield_ent_id_v2d_fn(USE_CURR_FILE_NUM);
	//}
	//--------
	//template<typename RetT=decltype(NonEcsSerData::_rng())>
	//inline RetT rand()
	template<typename T=decltype(std::declval<Rng>())>
	inline auto rand()
	{
		return non_ecs_ser_data().rand<T>();
	}
	template<typename T>
	inline auto rand(const T& max_val, bool saturate=false)
	{
		return non_ecs_ser_data().rand<T>(max_val, saturate);
	}
	template<typename T>
	inline auto rand_scaled(const T& scale)
	{
		return non_ecs_ser_data().rand_scaled<T>(scale);
	}
	template<typename T>
	inline auto rand_scaled(const T& scale, const T& max_val,
		bool saturate=false)
	{
		return non_ecs_ser_data().rand_scaled<T>(scale, max_val, saturate);
	}
	//--------
public:		// functions
	//--------
	inline PosVec3 to_pos_vec3_fn(ecs::FileNum file_num,
		const PosVec2& pos_2d) const
	{
		return PosVec3(pos_2d.x, pos_2d.y, floor_fn(file_num));
	}
	inline PosVec3 to_pos_vec3(const PosVec2& pos_2d) const
	{
		return to_pos_vec3_fn(USE_CURR_FILE_NUM, pos_2d);
	}
	//--------
public:		// functions
	//--------
	//inline int fn_state_index() const
	//{
	//	return
	//		fn_state == FnState::Curr
	//		? *curr_file_num()
	//		: *src_file_num();
	//}
	//--------
private:		// static functions
	inline ecs::FileNum _sel_file_num(ecs::FileNum some_file_num) const
	{
		return ecs_engine.sel_file_num(some_file_num);
	}
	//inline int _sel_file_num(ecs::FileNum some_file_num) const
	//{
	//	//return (some_file_num == USE_CURR_FILE_NUM)
	//	//	? *curr_file_num()
	//	//	: some_file_num;
	//	switch (some_file_num)
	//	{
	//	//--------
	//	case USE_CURR_FILE_NUM:
	//		return *curr_file_num();
	//		break;
	//	case USE_SRC_FILE_NUM:
	//		return *src_file_num();
	//		break;
	//	case USE_COPY_DST_FILE_NUM:
	//		return *copy_dst_file_num();
	//	default:
	//		return some_file_num;
	//		break;
	//	//--------
	//	}
	//}
public:		// functions
	void position_ctor_callback(comp::Position* obj);
	void position_dtor_callback(comp::Position* obj);
	void position_set_pos_callback(comp::Position* obj,
		const PosVec3& n_pos);

	inline Menu build_yes_no_menu(auto* self,
		const std::function<void(decltype(self))>& yes_func,
		const std::function<void(decltype(self))>& no_func)
	{
		return Menu
		(
			"yes",
			yes_no_window.size_2d(),
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
			Vec2<bool>({.x=false, .y=true})
		);
	}
	inline Menu build_text_yes_no_menu(auto* self,
		const std::string& s_text,
		const std::function<void(decltype(self))>& yes_func,
		const std::function<void(decltype(self))>& no_func,
		uint s_tab_amount=0)
	{
		return Menu
		(
			"yes",
			text_yes_no_window.size_2d(),
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
			Vec2<bool>({.x=false, .y=true}),
			s_tab_amount
		);
	}


	GameMode& set_game_mode(GameMode n_game_mode);
	inline decltype(_game_mode) game_mode() const
	{
		return _game_mode;
	}

	GEN_GETTER_BY_VAL(curr_file_num);
	GEN_GETTER_BY_VAL(src_file_num);
	GEN_GETTER_BY_VAL(copy_dst_file_num);
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
			throw std::invalid_argument(err_msg.c_str());
			//fprintf(stderr, err_msg.c_str());
			//exit(1);
		}
	}
};

extern Engine* engine;
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_engine_class_hpp
