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
#include "../misc_types.hpp"
#include "../input_kind_enum.hpp"
#include "window_class.hpp"
#include "menu_etc_classes.hpp"
#include "game_options_class.hpp"
#include "comp/general_comp_classes.hpp"
#include "global_shape_constants_etc.hpp"
#include "lvgen_etc/dngn_floor_class.hpp"
#include "lvgen_etc/dngn_gen_class.hpp"
//#include "metaball_gen_class.hpp"
#include "namegen.hpp"
#include "pfield_layer_prio_enum.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
enum class KeyKind: i32 {
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
	X(DngnGen) \
	X(Main) \
	\
	/* X(PopupShop) */ \
	/* X(YesNoShop) */ \

// An `enum` to specify which `game_engine::Window` is the
// currently-selected one, as well as what game mode the game is in.
enum class GameMode {
	#define X(arg) \
		arg,
	LIST_OF_GAME_MODES(X)
	#undef X
};
//--------
template<typename ObjT>
concept EngineErrWhenEntNullIdObj = requires(ObjT obj) {
	{ obj.ent_id() } -> std::same_as<ecs::EntId>;
};

class Engine final {
	friend class NameGen::Random;
public:		// constants
	// These are basement floors, going from B1F down to B25F
	static constexpr i32
		//LOWEST_FLOOR
		//	= 25,
		//	//= 5,
		//HIGHEST_FLOOR
		//	= 1,
		//LOWEST_FLOOR = 5, HIGHEST_FLOOR = 1,

		LEVEL_1_FLOOR_MIN = 1,
			FIRST_FLOOR = LEVEL_1_FLOOR_MIN,
			HIGHEST_FLOOR = FIRST_FLOOR,
		LEVEL_1_FLOOR_MAX = 5,
			LEVEL_1_FLOOR_BOSS = LEVEL_1_FLOOR_MAX,

		LEVEL_2_FLOOR_MIN = 6,
		LEVEL_2_FLOOR_MAX = 10,
			LEVEL_2_FLOOR_BOSS = LEVEL_2_FLOOR_MAX,

		LEVEL_3_FLOOR_MIN = 11,
		LEVEL_3_FLOOR_MAX = 15,
			LEVEL_3_FLOOR_BOSS = LEVEL_3_FLOOR_MAX,

		LEVEL_4_FLOOR_MIN = 16,
		LEVEL_4_FLOOR_MAX = 20,
			LEVEL_4_FLOOR_BOSS = LEVEL_4_FLOOR_MAX,

		LEVEL_5_FLOOR_MIN = 21,
		LEVEL_5_FLOOR_MAX = 25,
			LEVEL_5_FLOOR_BOSS = LEVEL_5_FLOOR_MAX,
			LAST_FLOOR = LEVEL_5_FLOOR_BOSS,
			LOWEST_FLOOR = LAST_FLOOR,

		NUM_FLOORS = std::abs(HIGHEST_FLOOR - LOWEST_FLOOR) + 1,
		NUM_FLOORS_PER_LEVEL
			= std::abs(LEVEL_1_FLOOR_MAX - LEVEL_1_FLOOR_MIN) + 1;

	static const std::string
		DEFAULT_SAVE_FILE_NAME,
		DEBUG_SAVE_FILE_NAME;

	static constexpr ecs::FileNum
		//NUM_FILES = 9;
		NUM_FILES = 3;
		//NUM_FILES = 1;
public:		// types
	//using EntIdSetVec2d
	//	= std::vector<std::vector<ecs::EntIdUset>>;

	using Rng
		//= pcg32;
		= pcg64;
	using RngSeedT = std::remove_cvref_t<decltype(std::declval<Rng>()())>;

	template<typename ElemTarg>
	using ArrWNumFloorsElems = std::array<ElemTarg, NUM_FLOORS>;
	template<typename ElemTarg>
	using ArrWNumFilesElems = std::array<ElemTarg, NUM_FILES>;

	using LayoutRngArr = ArrWNumFloorsElems<Rng>;
	using LayoutRngA2d = ArrWNumFilesElems<LayoutRngArr>;
	using DngnFloorArr = ArrWNumFloorsElems<lvgen_etc::DngnFloor>;
public:		// types
	class NonEcsSerData final {
		friend class NameGen::Random;
		friend class Engine;
	public:		// variables
		#define MEMB_AUTOSER_LIST_ENGINE_NON_ECS_SER_DATA(X) \
			X(did_init_save_file, std::nullopt) \
			\
			X(log_msg_log, std::nullopt) \
			X(hud_msg_log, std::nullopt) \
			\
			X(player_pos3, std::nullopt) \
			X(pfield_ent_id_umap, std::nullopt) \
			\
			X(dngn_floor_arr, std::nullopt) \
			\
			X(_base_rng_seed, std::nullopt) \

		#define MEMB_RNG_LIST_ENGINE_NON_ECS_SER_DATA(X) \
			X(_rng, std::nullopt) \
			/* X(_namegen_rng, std::nullopt) */ \

		bool did_init_save_file = false;

		MsgLog
			log_msg_log,
			hud_msg_log;

		//PrevCurrPair<i32> floor = {FIRST_FLOOR, FIRST_FLOOR};
		i32 prev_floor = FIRST_FLOOR;
		//i32 floor = HIGHEST_FLOOR;
		PrevCurrPair<IntVec3> player_pos3
			= {{0, 0, FIRST_FLOOR}, {0, 0, FIRST_FLOOR}};
			//= {IntVec2(0, 0), IntVec2(0, 0)};

		// dimensions: floor, y, x
		// "pfield" is short for "playfield".
		// I needed to have a shorter variable name, so I changed the name
		// of this variable and related functions
		std::unordered_map<IntVec3, ecs::EntIdUset> pfield_ent_id_umap;
		std::array<lvgen_etc::DngnFloor, NUM_FLOORS>
			dngn_floor_arr;
	private:		// variables
		u64 _base_rng_seed = 0;
		// The RNG to use for tasks other than initial floor layout
		// generation
		Rng
			_rng;
		//pcg32
		//	_namegen_rng;
	//private:		// static functions
	//	static decltype(pfield_ent_id_v3d)
	//		_gen_blank_pfield_ent_id_v3d();
	public:		// functions
		NonEcsSerData();
		NonEcsSerData(const binser::Value& bv);
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(NonEcsSerData);
		~NonEcsSerData();

		operator binser::Value () const;

		inline i32 seed_ext_rngs(LayoutRngArr& layout_rng_arr) {
			i32 i;
			for (i=0; i<i32(layout_rng_arr.size()); ++i) {
				//layout_rng_arr.at(i).seed(_base_rng_seed + i);
				layout_rng_arr.at(i) = Rng(_base_rng_seed + i);
			}
			//_namegen_rng = pcg32(_base_rng_seed + i);
			//++i;
			return i;
		}
		//inline void seed_rngs_etc(LayoutRngArr& layout_rng_arr) {
		//	const i32 i = seed_layout_rng_arr(layout_rng_arr);

		//	//_rng.seed(_base_rng_seed + i);
		//	_rng = Rng(_base_rng_seed + i);
		//}
	private:		// functions
		inline void _init_base_rng_seed() {
			_base_rng_seed = get_hrc_now_rng_seed();
			//printout("NonEcsSerData::_init_base_rng_seed(): ",
			//	_base_rng_seed, "\n");
		}
		inline void _dbg_init_base_rng_seed(RngSeedT s_base_rng_seed) {
			_base_rng_seed = s_base_rng_seed;
		}
	public:		// functions
		inline void on_init_or_file_erase_seed_rngs_etc(
			LayoutRngArr& layout_rng_arr, RngSeedT s_base_rng_seed
		) {
			//_init_base_rng_seed();
			_dbg_init_base_rng_seed(s_base_rng_seed);

			const i32 i = seed_ext_rngs(layout_rng_arr);

			_rng = Rng(_base_rng_seed + i);
		}

		//template<typename RetT=decltype(_rng())>
		//inline std::remove_cvref_t<RetT> rand()
		//	requires std::integral<std::remove_cvref_t<RetT>>
		template<typename T=RngSeedT>
		inline auto rand() {
			return rng_run<T>(_rng);
		}
		//template<typename T=RngSeedT>
		//inline auto rand(const T& max, bool saturate=false) {
		//	return rng_run<T>(_rng, max, saturate);
		//}
		template<typename T=RngSeedT>
		inline auto rand_lt_bound(const T& bound) {
			return rng_run_lt_bound<T>(_rng, bound);
		}
		template<typename T=RngSeedT>
		inline auto rand(const T& lim_0, const T& lim_1) {
			return rng_run<T>(_rng, lim_0, lim_1);
		}
		//template<typename T=RngSeedT>
		//inline auto rand_scaled(const T& scale) {
		//	return rng_run_scaled<T>(_rng, scale);
		//}
		//template<typename T=RngSeedT>
		//inline auto rand_scaled(
		//	const T& scale, const T& max, bool saturate=false
		//) {
		//	return rng_run_scaled<T>(_rng, scale, max, saturate);
		//}
		//template<typename T=RngSeedT>
		//inline auto rand_scaled_lim(
		//	const T& scale, const T& lim_0, const T& lim_1
		//) {
		//	return rng_run_scaled_lim<T>(_rng, scale, lim_0, lim_1);
		//}

		GEN_GETTER_BY_VAL(base_rng_seed);
	};
private:		// non-serialized variables
	i32 _argc = 0;
	char** _argv = nullptr;
	std::string _save_file_name;

	// The RNGs for each file's floors' initial layouts, including the
	// parts that are static (which are stored in the
	// `comp::StaticBgTileMap`).
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
	//std::array<NonEcsSerData, NUM_FILES>
	ArrWNumFilesElems<NonEcsSerData>
		_non_ecs_ser_data_arr;
public:		// non-serialized variables
	EngineKeyStatus key_status;
	lvgen_etc::DngnGen dngn_gen;
	//lvgen_etc::DngnFloor dngn_floor;

	////InputKind initial_input_kind = InputKind::None,
	////	final_input_kind = InputKind::None;
	//InputKind input_kind;

	//struct {
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
	static constexpr i32
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
	//enum class FnState: i32 {
	//	Curr,
	//	Src,
	//};
	//FnState fn_state = FnState::Curr;
private:		// variables
	//u64 _tick_counter = 0;
public:		// functions
	Engine(i32 s_argc, char** s_argv, bool do_create_or_load=true);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Engine);
	~Engine();
	operator binser::Value () const;

	void deserialize(const binser::Value& bv);

	inline void err(
		const liborangepower::concepts::HasStdOstmOpLshift auto&... objs
	) const {
		printerr(objs...);
		exit(1);
	}
	inline void corrupted_save_file_err(
		const liborangepower::concepts::HasStdOstmOpLshift auto&... objs
	) const {
		err(objs..., "Error: corrupted save file ",
			"\"", _save_file_name, "\".",
			"\n");
	}
private:		// functions
	void _dbg_log_backend(const std::string& msg);
public:		// functions
	inline void dbg_log(
		const liborangepower::concepts::HasStdOstmOpLshift auto&... args
	) {
		_dbg_log_backend(sconcat(args...));
	}
	//inline void log(const std::stringstream& sstm) {
	//	log(sstm.str());
	//}

	//void dbg_check_ecs_engine(const IntVec2& wb_pos=IntVec2(0, 0));

	//inline void tick() {
	//	ecs_engine.tick();
	//}
	void tick();
	void draw_to_main_windows();
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
	inline void draw_aux_menu_w_pre_clear() {
		_inner_draw_menu_w_pre_clear(aux_window, aux_menu);
	}
	inline void draw_popup_menu_w_pre_clear() {
		_inner_draw_menu_w_pre_clear(popup_window, popup_menu);
	}
	inline void draw_yes_no_menu_w_pre_clear() {
		_inner_draw_menu_w_pre_clear(yes_no_window, yes_no_menu);
	}
	inline void draw_text_yes_no_menu_w_pre_clear() {
		_inner_draw_menu_w_pre_clear(text_yes_no_window, text_yes_no_menu);
	}
	//--------
	inline LayoutRngArr& layout_rng_arr_fn(ecs::FileNum file_num) {
		return _layout_rng_a2d.at(_sel_file_num(file_num));
	}
	inline const LayoutRngArr& layout_rng_arr_fn(
		ecs::FileNum file_num
	) const {
		return _layout_rng_a2d.at(_sel_file_num(file_num));
	}
	inline LayoutRngArr& layout_rng_arr() {
		return layout_rng_arr_fn(USE_CURR_FILE_NUM);
	}
	inline const LayoutRngArr& layout_rng_arr() const {
		return layout_rng_arr_fn(USE_CURR_FILE_NUM);
	}

	// Note: `layout_rng_fn()` and `layout_rng()` return the current
	// floor's layout RNG itself
	inline Rng& layout_rng_fn(ecs::FileNum file_num) {
		return layout_rng_arr_fn(file_num).at(floor_fn(file_num));
	}
	inline const Rng& layout_rng_fn(ecs::FileNum file_num) const {
		return layout_rng_arr_fn(file_num).at(floor_fn(file_num));
	}
	inline Rng& layout_rng() {
		return layout_rng_fn(USE_CURR_FILE_NUM);
	}
	inline const Rng& layout_rng() const {
		return layout_rng_fn(USE_CURR_FILE_NUM);
	}

	//inline auto layout_rand() {
	//	return layout_rng_arr().at(floor())();
	//}
	template<typename T=RngSeedT>
	inline auto layout_rand() {
		return rng_run<T>(layout_rng());
	}
	//template<typename T=RngSeedT>
	//inline auto layout_rand(const T& max, bool saturate=false) {
	//	return rng_run<T>(layout_rng(), max, saturate);
	//}
	template<typename T=RngSeedT>
	inline auto layout_rand_lt_bound(const T& bound) {
		return rng_run_lt_bound<T>(layout_rng(), bound);
	}
	template<typename T=RngSeedT>
	inline auto layout_rand(const T& lim_0, const T& lim_1) {
		return rng_run<T>(layout_rng(), lim_0, lim_1);
	}

	inline IntVec2 layout_rand_vec2(
		const IntVec2& min, const IntVec2& max
	) {
		return
			{.x=layout_rand<i32>(min.x, max.x),
			.y=layout_rand<i32>(min.y, max.y)};
	}
	inline IntVec2 layout_rand_vec2(
		const IntRect2& inside_r2
	) {
		return
			{.x=layout_rand<i32>(inside_r2.left_x(), inside_r2.right_x()),
			.y=layout_rand<i32>(inside_r2.top_y(), inside_r2.bottom_y())};
	};
	inline IntVec2 layout_rand_vec2_in_pfnb() {
		return layout_rand_vec2(PFIELD_PHYS_NO_BRDR_RECT2);
	}

	inline IntRect2 layout_rand_r2(
		const IntRect2& inside_r2, const IntVec2& min_size,
		const IntVec2& max_size
	) {
		IntRect2 ret;

		do {
			ret = {
				.pos
				{.x=layout_rand<i32>
					(inside_r2.left_x(),
					inside_r2.right_x() - min_size.x),
				.y=layout_rand<i32>
					(inside_r2.top_y(),
					inside_r2.bottom_y() - min_size.y)},
			.size_2d
				{.x=layout_rand<i32>(min_size.x, max_size.x),
				.y=layout_rand<i32>(min_size.y, max_size.y)}
			};
		} while (!r2_fits_in_other(ret, inside_r2));

		return ret;
	}
	inline IntRect2 layout_rand_r2_in_pfnb(
		const IntVec2& min_size, const IntVec2& max_size
	) {
		return layout_rand_r2
			(PFIELD_PHYS_NO_BRDR_RECT2, min_size, max_size);
	};
	//template<std::floating_point T>
	//inline auto flt_layout_rand(const T& lim_0, const T& lim_1,
	//	const T& scale) {
	//}
	//inline float calc_layout_noise_param_backend() {
	//	// This assumes `float` has a mantissa of at least 20-bit;
	//	// it almost certainly will.
	//	return float(layout_rand<i32>(0, (i32(1) << i32(20)) - i32(1)));
	//}
	//inline float calc_layout_noise_pos_scale() {
	//	return (1.0 / calc_layout_noise_param_backend()); 
	//}
	//inline float calc_layout_noise_pos_offset() {
	//	return calc_layout_noise_param_backend();
	//};
	//template<typename T=RngSeedT>
	//inline auto layout_noise(
	//	const T& lim_0, const T& lim_1, const IntVec2& pos,
	//	float pos_scale, float pos_offset
	//) {
	//	const float
	//		dist_lim = std::abs(float(lim_0) - float(lim_1) + 1.0),
	//		min_lim = math::min_va(float(lim_0), float(lim_1)),
	//		//raw_noise = float(SimplexNoise::noise
	//		//	(float(float(pos.x) + (add_amount / dist_lim)),
	//		//	float(float(pos.y) + (add_amount / dist_lim))));
	//		raw_noise = float(SimplexNoise::noise
	//			(float((float(pos.x) * pos_scale) + pos_offset),
	//			float((float(pos.y) * pos_scale) + pos_offset)));
	//	//if (float(i64(raw_noise)) == raw_noise)
	//	//if (float(i64(raw_noise)) != raw_noise) {
	//	//	log("Debug: game_engine::Engine::layout_noise(): ",
	//	//		raw_noise,
	//	//		"\n");
	//	//}
	//	const float
	//		// `SimplexNoise::noise()` returns a value in the range 
	//		// [-1, 1], so we shift the range to [0, 1]
	//		modded_noise
	//			= (((raw_noise + 1.0) / 2.0) * dist_lim)
	//			+ min_lim;
	//	//log("Debug: layout_noise(): ",
	//	//	"rw{", raw_noise, "}; ",
	//	//	"mn{", modded_noise, " ", T(std::round(modded_noise)), "}; ",
	//	//	"dl{", dist_lim, "}; ",
	//	//	"ml{", min_lim, "}",
	//	//	"\n");
	//	return T(std::round(modded_noise));
	//}
	//static inline i32 mball_out(
	//	i32 lim_0, i32 lim_1, const MetaballGen::GenDyna2d& dyna2d,
	//	const IntVec2& pos
	//) {
	//	const float
	//		dist_lim = std::abs(float(lim_0) - float(lim_1) + 1.0f),
	//		min_lim = math::min_va(float(lim_0), float(lim_1)),
	//		raw_mball_out = dyna2d.at(pos.y).at(pos.x),
	//		modded_mball_out
	//			= (raw_mball_out * dist_lim) + min_lim;
	//	return math::clamp(i32(std::round(modded_mball_out)),
	//		lim_0, lim_1);
	//}
	//template<typename T=RngSeedT>
	//inline auto layout_rand_scaled(const T& scale) {
	//	return rng_run_scaled<T>(layout_rng(), scale);
	//}
	//template<typename T=RngSeedT>
	//inline auto layout_rand_scaled(
	//	const T& scale, const T& max, bool saturate=false
	//) {
	//	return rng_run_scaled<T>(layout_rng(), scale, max, saturate);
	//}
	//template<typename T=RngSeedT>
	//inline auto layout_rand_scaled_lim(
	//	const T& scale, const T& lim_0, const T& lim_1
	//) {
	//	return rng_run_scaled_lim<T>(layout_rng(), scale, lim_0, lim_1);
	//}

	//template<CallableLikeRngBounded<double> RngT>
	//inline DblRect2 rand_rect2(
	//	RngT& rng, const DblVec2& pos_max, const DblVec2& pos_min,
	//	const DblVec2& size_2d_max, const DblVec2& size_2d_min
	//) {
	//	DblRect2 ret;
	//}
	//--------
	inline std::ostream& dbg_osprint_layout_rng_a2d(std::ostream& os)
		const {
		osprintout(os, "Engine::dbg_osprint_layout_rng_a2d(): Start\n");

		for (ecs::FileNum file_num=0; file_num<NUM_FILES; ++file_num) {
			dbg_osprint_layout_rng_arr_fn(os, file_num);

			if (file_num + 1 < NUM_FILES) {
				osprintout(os, "\n");
			}
		}

		osprintout(os, "Engine::dbg_osprint_layout_rng_a2d(): End\n\n");
		return os;
	}
	inline std::ostream& dbg_osprint_layout_rng_arr_fn(
		std::ostream& os, ecs::FileNum file_num
	) const {
		const auto& lr_arr = layout_rng_arr_fn(file_num);

		for (i32 i=0; i<i32(lr_arr.size()); ++i) {
			osprintout(os, i, ": ", lr_arr.at(i), "\n");
		}

		return os;
	}
	//inline void dbg_osprint_layout_rng_arr() const {
	//	dbg_osprint_layout_rng_arr_fn(USE_CURR_FILE_NUM);
	//}
	//--------
public:		// `_non_ecs_ser_data_arr` accessor functions
	//--------
	inline NonEcsSerData& non_ecs_ser_data_fn(ecs::FileNum file_num) {
		return _non_ecs_ser_data_arr.at(_sel_file_num(file_num));
	}
	inline const NonEcsSerData& non_ecs_ser_data_fn(ecs::FileNum file_num)
		const {
		return _non_ecs_ser_data_arr.at(_sel_file_num(file_num));
	}
	inline NonEcsSerData& non_ecs_ser_data() {
		return non_ecs_ser_data_fn(USE_CURR_FILE_NUM);
	}
	inline const NonEcsSerData& non_ecs_ser_data() const {
		return non_ecs_ser_data_fn(USE_CURR_FILE_NUM);
	}
	//--------
	inline bool& did_init_save_file_fn(ecs::FileNum file_num) {
		return non_ecs_ser_data_fn(file_num).did_init_save_file;
	}
	inline const bool& did_init_save_file_fn(ecs::FileNum file_num) const {
		return non_ecs_ser_data_fn(file_num).did_init_save_file;
	}
	inline bool& did_init_save_file() {
		return did_init_save_file_fn(USE_CURR_FILE_NUM);
	}
	inline const bool& did_init_save_file() const {
		return did_init_save_file_fn(USE_CURR_FILE_NUM);
	}
	//--------
	inline MsgLog& log_msg_log_fn(ecs::FileNum file_num) {
		return non_ecs_ser_data_fn(file_num).log_msg_log;
	}
	inline const MsgLog& log_msg_log_fn(ecs::FileNum file_num) const {
		return non_ecs_ser_data_fn(file_num).log_msg_log;
	}
	inline MsgLog& log_msg_log() {
		return log_msg_log_fn(USE_CURR_FILE_NUM);
	}
	inline const MsgLog& log_msg_log() const {
		return log_msg_log_fn(USE_CURR_FILE_NUM);
	}
	//--------
	inline MsgLog& hud_msg_log_fn(ecs::FileNum file_num) {
		return non_ecs_ser_data_fn(file_num).hud_msg_log;
	}
	inline const MsgLog& hud_msg_log_fn(ecs::FileNum file_num) const {
		return non_ecs_ser_data_fn(file_num).hud_msg_log;
	}
	inline MsgLog& hud_msg_log() {
		return hud_msg_log_fn(USE_CURR_FILE_NUM);
	}
	inline const MsgLog& hud_msg_log() const {
		return hud_msg_log_fn(USE_CURR_FILE_NUM);
	}
	//--------
	//inline i32& floor_fn(ecs::FileNum file_num) {
	//	return non_ecs_ser_data_fn(file_num).floor();
	//}
	//inline const i32& set_floor_fn(ecs::FileNum file_num, i32 n_floor) {
	//	auto& floor_pcp = non_ecs_ser_data_fn(file_num).floor_pcp;
	//	floor_pcp.back_up_and_update(n_floor);
	//	return floor_pcp();
	//}
	inline const IntVec3& player_pos3_fn(ecs::FileNum file_num) const {
		return non_ecs_ser_data_fn(file_num).player_pos3();
	}
	inline const IntVec3& prev_player_pos3_fn(
		ecs::FileNum file_num
	) const {
		return non_ecs_ser_data_fn(file_num).player_pos3.prev();
	}
	inline IntVec3& set_player_pos3_fn(
		ecs::FileNum file_num, const IntVec3& n_player_pos3
	) {
		//return non_ecs_ser_data_fn(file_num).player_pos2
		//	.back_up_and_update(n_player_pos2)();
		auto& the_player_pos3 = non_ecs_ser_data_fn(file_num).player_pos3;
		auto& the_prev_floor = non_ecs_ser_data_fn(file_num).prev_floor;
		const i32 old_floor = the_player_pos3().z;
		the_player_pos3.back_up_and_update(n_player_pos3);
		if (old_floor != the_player_pos3().z) {
			the_prev_floor = old_floor;
		}
		return the_player_pos3();
	}
	inline IntVec2 player_pos2_cf_fn(ecs::FileNum file_num) const {
		//return to_pos3_fn(file_num, player_pos2_fn(file_num));
		return to_pos2_cf(player_pos3_fn(file_num));
	}
	inline IntVec2 prev_player_pos2_cf_fn(ecs::FileNum file_num) const {
		return to_pos2_cf(prev_player_pos3_fn(file_num));
	}
	inline void set_player_pos2_cf_fn(
		ecs::FileNum file_num, const IntVec2& n_player_pos2
	) {
		set_player_pos3_fn(file_num,
			to_pos3_cf_fn(file_num, n_player_pos2));
	}
	//--------
	inline const IntVec3& player_pos3() const {
		return player_pos3_fn(USE_CURR_FILE_NUM);
	}
	inline const IntVec3& prev_player_pos3() const {
		return prev_player_pos3_fn(USE_CURR_FILE_NUM);
	}
	inline IntVec3& set_player_pos3(const IntVec3& n_player_pos3) {
		return set_player_pos3_fn(USE_CURR_FILE_NUM, n_player_pos3);
	}

	inline IntVec2 player_pos2_cf() const {
		return player_pos2_cf_fn(USE_CURR_FILE_NUM);
	}
	inline IntVec2 prev_player_pos2_cf() const {
		return prev_player_pos2_cf_fn(USE_CURR_FILE_NUM);
	}
	inline void set_player_pos2_cf(const IntVec2& n_player_pos2) {
		set_player_pos2_cf_fn(USE_CURR_FILE_NUM, n_player_pos2);
	}
	//--------
	inline const i32& floor_fn(ecs::FileNum file_num) const {
		//return non_ecs_ser_data_fn(file_num).floor();
		//return non_ecs_ser_data_fn(file_num).player_pos().z;
		return player_pos3_fn(file_num).z;
	}
	inline const i32& prev_floor_fn(ecs::FileNum file_num) const {
		return non_ecs_ser_data_fn(file_num).prev_floor;
		//return non_ecs_ser_data_fn(file_num).player_pos.prev().z;
		//return prev_player_pos_fn(file_num).z;
	}
	inline const i32& floor() const {
		return floor_fn(USE_CURR_FILE_NUM);
	}
	inline const i32& prev_floor() const {
		return prev_floor_fn(USE_CURR_FILE_NUM);
	}
	//--------
	inline i32 level_minus_1_fn(ecs::FileNum file_num) const {
		if (floor_fn(file_num) >= LEVEL_1_FLOOR_MIN
			&& floor_fn(file_num) <= LEVEL_1_FLOOR_MAX) {
			return 0;
		} else if (floor_fn(file_num) >= LEVEL_2_FLOOR_MIN
			&& floor_fn(file_num) <= LEVEL_2_FLOOR_MAX) {
			return 1;
		} else if (floor_fn(file_num) >= LEVEL_3_FLOOR_MIN
			&& floor_fn(file_num) <= LEVEL_3_FLOOR_MAX) {
			return 2;
		} else if (floor_fn(file_num) >= LEVEL_4_FLOOR_MIN
			&& floor_fn(file_num) <= LEVEL_4_FLOOR_MAX) {
			return 3;
		} else if (floor_fn(file_num) >= LEVEL_5_FLOOR_MIN
			&& floor_fn(file_num) <= LEVEL_5_FLOOR_MAX) {
			return 4;
		} else {
			throw std::runtime_error(sconcat
				("game_engine::Engine::level_minus_1_fn(): Eek! ",
				floor_fn(file_num)));
		}
	}
	inline i32 level_minus_1() const {
		return level_minus_1_fn(USE_CURR_FILE_NUM);
	}
	//--------
	inline bool pfield_ent_id_umap_contains_fn(
		ecs::FileNum file_num, const IntVec3& pos
	) const {
		return non_ecs_ser_data_fn(file_num).pfield_ent_id_umap
			.contains(pos);
	}
	inline bool pfield_ent_id_umap_contains(const IntVec3& pos) const {
		return pfield_ent_id_umap_contains_fn(USE_CURR_FILE_NUM, pos);
	}

	inline ecs::EntIdUset& pfield_ent_id_uset_fn(
		ecs::FileNum file_num, const IntVec3& pos
	) {
		return non_ecs_ser_data_fn(file_num).pfield_ent_id_umap[pos];
		//return non_ecs_ser_data_fn(file_num).pfield_ent_id_umap.at(pos);
	}
	//inline const ecs::EntIdUset& pfield_ent_id_uset_fn(
	//	ecs::FileNum file_num, const IntVec3& pos
	//) const {
	//	return non_ecs_ser_data(file_num).pfield_ent_id_umap[pos];
	//}
	inline ecs::EntIdUset& pfield_ent_id_uset(const IntVec3& pos) {
		return pfield_ent_id_uset_fn(USE_CURR_FILE_NUM, pos);
	}
	//inline const ecs::EntIdUset& pfield_ent_id_uset(const IntVec3& pos)
	//	const {
	//	return pfield_ent_id_uset_fn(USE_CURR_FILE_NUM, pos);
	//}
	//--------
	//inline ecs::EntIdUset& pfield_ent_id_uset_fn(
	//	ecs::FileNum file_num, const IntVec2& pos2
	//) {
	//	return pfield_ent_id_uset_fn(file_num,
	//		to_pos3_fn(file_num, pos2));
	//}

	//inline const ecs::EntIdUset& pfield_ent_id_uset_fn(
	//	ecs::FileNum file_num, const IntVec2& pos2
	//) const {
	//	return pfield_ent_id_uset_fn(file_num,
	//		to_pos3_fn(file_num, pos2));
	//}
	//inline ecs::EntIdUset& pfield_ent_id_uset(const IntVec2& pos2) {
	//	return pfield_ent_id_uset(to_pos3(pos2));
	//}
	//inline const ecs::EntIdUset& pfield_ent_id_uset(const IntVec2& pos2)
	//	const {
	//	return pfield_ent_id_uset(to_pos3(pos2));
	//}
	//inline EntIdSetVec2d& pfield_ent_id_v2d_fn(ecs::FileNum file_num) {
	//	return pfield_ent_id_v3d_fn(file_num).at(floor_fn(file_num));
	//}
	//inline const EntIdSetVec2d& pfield_ent_id_v2d_fn(
	//	ecs::FileNum file_num
	//) const {
	//	return pfield_ent_id_v3d_fn(file_num).at(floor_fn(file_num));
	//}
	//inline EntIdSetVec2d& pfield_ent_id_v2d() {
	//	return pfield_ent_id_v2d_fn(USE_CURR_FILE_NUM);
	//}
	//inline const EntIdSetVec2d& pfield_ent_id_v2d() const {
	//	return pfield_ent_id_v2d_fn(USE_CURR_FILE_NUM);
	//}
	//--------
	inline DngnFloorArr& dngn_floor_arr_fn(
		ecs::FileNum file_num
	) {
		return non_ecs_ser_data_fn(file_num).dngn_floor_arr;
	}
	inline const DngnFloorArr& dngn_floor_arr_fn(
		ecs::FileNum file_num
	) const {
		return non_ecs_ser_data_fn(file_num).dngn_floor_arr;
	}

	inline DngnFloorArr& dngn_floor_arr() {
		return dngn_floor_arr_fn(USE_CURR_FILE_NUM);
	}
	inline const DngnFloorArr& dngn_floor_arr_fn() const {
		return dngn_floor_arr_fn(USE_CURR_FILE_NUM);
	}

	//inline void clear_dngn_floor_arr_fn(
	//	ecs::FileNum file_num
	//) {
	//	auto& fl_arr = dngn_floor_arr_fn(file_num);
	//	for (auto& fl: fl_arr) {
	//		fl.clear();
	//	}
	//}
	//inline void clear_dngn_floor_arr() {
	//	auto& fl_arr = dngn_floor_arr();
	//	for (auto& fl: fl_arr) {
	//		fl.clear();
	//	}
	//}

	// Note: `dngn_floor_rng_fn()` and `layout_rng()` return the current
	// floor's `lvgen_etc::DngnFloor` itself
	inline lvgen_etc::DngnFloor& dngn_floor_fn(
		ecs::FileNum file_num
	) {
		return dngn_floor_arr_fn(file_num).at(floor_fn(file_num));
	}
	inline const lvgen_etc::DngnFloor& dngn_floor_fn(
		ecs::FileNum file_num
	) const {
		return dngn_floor_arr_fn(file_num).at(floor_fn(file_num));
	}
	inline lvgen_etc::DngnFloor& dngn_floor() {
		return dngn_floor_fn(USE_CURR_FILE_NUM);
	}
	inline const lvgen_etc::DngnFloor& dngn_floor() const {
		return dngn_floor_fn(USE_CURR_FILE_NUM);
	}
	//--------
	//template<typename RetT=decltype(NonEcsSerData::_rng())>
	//inline RetT rand()
	// These are for 
	template<typename T=RngSeedT>
	inline auto rand() {
		return non_ecs_ser_data().rand<T>();
	}
	//template<typename T=RngSeedT>
	//inline auto rand(const T& max, bool saturate=false) {
	//	return non_ecs_ser_data().rand<T>(max, saturate);
	//}
	template<typename T=RngSeedT>
	inline auto rand_lt_bound(const T& bound) {
		return non_ecs_ser_data().rand_lt_bound<T>(bound);
	}
	template<typename T=RngSeedT>
	inline auto rand(const T& lim_0, const T& lim_1) {
		return non_ecs_ser_data().rand<T>(lim_0, lim_1);
	}
	//template<typename T=RngSeedT>
	//inline auto rand_scaled(const T& scale) {
	//	return non_ecs_ser_data().rand_scaled<T>(scale);
	//}
	//template<typename T=RngSeedT>
	//inline auto rand_scaled(
	//	const T& scale, const T& max, bool saturate=false
	//) {
	//	return non_ecs_ser_data().rand_scaled<T>(scale, max, saturate);
	//}
	//template<typename T=RngSeedT>
	//inline auto rand_scaled_lim(
	//	const T& scale, const T& lim_0, const T& lim_1
	//) {
	//	return non_ecs_ser_data().rand_scaled_lim<T>(scale, lim_0, lim_1);
	//}
	//--------
public:		// functions
	//--------
	inline IntVec3 to_pos3_cf_fn(
		ecs::FileNum file_num, const IntVec2& pos2
	) const {
		return IntVec3(pos2.x, pos2.y, floor_fn(file_num));
	}
	inline IntVec3 to_pos3_cf(const IntVec2& pos2) const {
		return to_pos3_cf_fn(USE_CURR_FILE_NUM, pos2);
	}
	static inline IntVec2 to_pos2_cf(const IntVec3& pos3) {
		return {.x=pos3.x, .y=pos3.y};
	}
	//--------
public:		// functions
	//--------
	//inline i32 fn_state_index() const {
	//	return
	//		fn_state == FnState::Curr
	//		? *curr_file_num()
	//		: *src_file_num();
	//}
	//--------
private:		// static functions
	inline ecs::FileNum _sel_file_num(ecs::FileNum some_file_num) const {
		const auto& ret = ecs_engine.sel_file_num(some_file_num);
		//printout("game_engine::Engine::_sel_file_num(): ", ret, "\n");
		return ret;
	}
	//inline i32 _sel_file_num(ecs::FileNum some_file_num) const {
	//	//return (some_file_num == USE_CURR_FILE_NUM)
	//	//	? *curr_file_num()
	//	//	: some_file_num;
	//	switch (some_file_num) {
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
	void position_set_pos3_callback(
		comp::Position* obj, const IntVec3& n_pos3
	);

	inline Menu build_yes_no_menu(
		auto* self, const std::function<void(decltype(self))>& yes_func,
		const std::function<void(decltype(self))>& no_func
	) {
		return Menu(
			"yes",
			yes_no_window.size_2d(),
			Menu::build_node_map({
				Menu::build_action_button_knc_pair(
					"yes",
					"Yes",
					self,
					yes_func
				),
				Menu::build_action_button_knc_pair(
					"no",
					"No",
					self,
					no_func
				),
			}),
			Vec2<bool>({.x=false, .y=true})
		);
	}
	inline Menu build_text_yes_no_menu(
		auto* self, const std::string& s_text,
		const std::function<void(decltype(self))>& yes_func,
		const std::function<void(decltype(self))>& no_func,
		i32 s_tab_amount=0
	) {
		return Menu(
			"yes",
			text_yes_no_window.size_2d(),
			Menu::build_node_map({
				Menu::build_text_only_knc_pair(
					"<text[0]>",
					s_text
				),
				Menu::build_action_button_knc_pair(
					"yes",
					"Yes",
					self,
					yes_func
				),
				Menu::build_action_button_knc_pair(
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
	inline decltype(_game_mode) game_mode() const {
		return _game_mode;
	}

	GEN_GETTER_BY_VAL(curr_file_num);
	GEN_GETTER_BY_VAL(src_file_num);
	GEN_GETTER_BY_VAL(copy_dst_file_num);
private:		// functions
	//static void _yes_no_menu_act_yes(Engine* self);
	//static void _yes_no_menu_act_no(Engine* self);

	template<EngineErrWhenEntNullIdObj ObjT>
	inline void _err_when_ent_id_is_null(
		ObjT* obj, const std::string& func_name
	) const {
		if (obj->ent_id() == ecs::ENT_NULL_ID) {
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
