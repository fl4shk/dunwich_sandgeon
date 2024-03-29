// This file is part of Dunwich Sandgeon.
// 
// Copyright 2023 FL4SHK
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

#include "engine_class.hpp"

#include "comp/list_of_comps_define.hpp"

#include "comp/general_comp_classes.hpp"
#include "comp/player_comp_class.hpp"
//#include "comp/block_comp_classes.hpp"
#include "lvgen_etc/dngn_floor_class.hpp"
#include "comp/status_comp_classes.hpp"
//#include "comp/ui_etc_comp_classes.hpp"

#include "sys/list_of_syses_defines.hpp"

#include "sys/gm_title_screen_class.hpp"
#include "sys/gm_options_class.hpp"
#include "sys/gm_file_select_class.hpp"
#include "sys/gm_dngn_gen_class.hpp"
#include "sys/gm_main_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
//--------
const std::string
	Engine::DEFAULT_SAVE_FILE_NAME("save_file.binser.ignore"),
	Engine::DEBUG_SAVE_FILE_NAME("debug_save_file.json.ignore");
//--------
//auto Engine::NonEcsSerData::_gen_blank_pfield_ent_id_v3d()
//	-> decltype(pfield_ent_id_v3d) {
//	return
//		decltype(pfield_ent_id_v3d) 
//			(NUM_FLOORS,
//			EntIdSetVec2d(W_BRDR_PFIELD_WINDOW_SIZE_2D.y,
//				std::vector<std::unordered_set<ecs::EntId>>
//					(W_BRDR_PFIELD_WINDOW_SIZE_2D.x,
//					std::unordered_set<ecs::EntId>())));
//}

Engine::NonEcsSerData::NonEcsSerData()
	//: pfield_ent_id_v3d(_gen_blank_pfield_ent_id_v3d())
{
	//const auto& time_count = get_hrc_now().time_since_epoch().count();
	//rng.seed(time_count, time_count + 1, time_count + 2);

	//#ifdef DEBUG
	//printerr("Engine::NonEcsSerData::NonEcsSerData(): Note: ",
	//	"**NOT** calling `_init_base_rng_seed()`\n");
	//#endif		// DEBUG
	printerr("Engine::NonEcsSerData::NonEcsSerData(): Note: ",
		"**NOT** ",
		"calling `_dbg_init_base_rng_seed()`\n");
	_init_base_rng_seed();
	//_dbg_init_base_rng_seed(0);
	//_dbg_init_base_rng_seed(1);
}
Engine::NonEcsSerData::NonEcsSerData(const binser::Value& bv) {
	//MEMB_AUTOSER_LIST_ENGINE_NON_ECS_SER_DATA(BINSER_MEMB_DESERIALIZE);

	//{
	//	//std::vector<std::string> vec;
	//	//binser::get_bv_memb(vec, bv, "layout_rng_arr", std::nullopt);

	//	//if (vec.size() != Engine::NUM_FLOORS) {
	//		const std::string err_msg(sconcat(
	//			"game_engine::Engine::NonEcsSerData::NonEcsSerData",
	//			"(const binser::Value&): Wrong `vec.size()` value of ",
	//			vec.size(), "."
	//		));
	//	//	throw std::invalid_argument(err_msg.c_str());
	//	//}

	//	//for (i32 i=0; i<Engine::NUM_FLOORS; ++i) {
	//	//	Rng layout_rng;
	//	//	inv_sconcat(vec.at(i), layout_rng);
	//	//	layout_rng_arr.at(i) = std::move(layout_rng);
	//	//}
	//}

	{
		MEMB_AUTOSER_LIST_ENGINE_NON_ECS_SER_DATA(BINSER_MEMB_DESERIALIZE);
		#define X(name, func_umap) \
			do {  \
				std::string str;  \
				binser::get_bv_memb(str, bv, #name, func_umap);  \
				inv_sconcat(str, name);  \
			} while (0);
		MEMB_RNG_LIST_ENGINE_NON_ECS_SER_DATA(X);
		#undef X

		//if (std::string str; true) {
		//	binser::get_bv_memb(str, bv, "_rng", std::nullopt);
		//	inv_sconcat(str, _rng);
		//}
		//if (std::string str; true) {
		//	binser::get_bv_memb(str, bv, "_namegen_rng", std::nullopt);
		//	inv_sconcat(str, _namegen_rng);
		//}
	}
}

Engine::NonEcsSerData::~NonEcsSerData() {}

Engine::NonEcsSerData::operator binser::Value () const {
	binser::Value ret;

	MEMB_AUTOSER_LIST_ENGINE_NON_ECS_SER_DATA(BINSER_MEMB_SERIALIZE);
	//binser::set_bv_memb(ret, "rng", sconcat(rng));
	//{
	//	std::vector<std::string> vec;
	//	for (const auto& layout_rng: layout_rng_arr) {
	//		vec.push_back(sconcat(layout_rng));
	//	}
	//	binser::set_bv_memb(ret, "layout_rng_arr", vec);
	//}
	//binser::set_bv_memb(ret, "_rng", sconcat(_rng));
	//binser::set_bv_memb(ret, "_namegen_rng", sconcat(_namegen_rng));
	#define X(name, func_umap) \
		binser::set_bv_memb(ret, #name , sconcat( name ));
	MEMB_RNG_LIST_ENGINE_NON_ECS_SER_DATA(X);
	#undef X

	return ret;
}

//--------
Engine::Engine(i32 s_argc, char** s_argv, bool do_create_or_load)
	: _argc(s_argc), _argv(s_argv),
	ecs_engine(NUM_FILES),

	//_non_ecs_ser_data_arr(NUM_FILES, NonEcsSerData()),
	key_status(i32(KeyKind::Lim)),

	screen_window(IntVec2(), W_BRDR_SCREEN_SIZE_2D, false),
	aux_window(IntVec2(), W_BRDR_SCREEN_SIZE_2D, false),

	pfield_window(PFIELD_WINDOW_POS, PFIELD_WINDOW_END_POS, true),
	log_window(LOG_WINDOW_POS, LOG_WINDOW_END_POS, true),
	hud_window(HUD_WINDOW_POS, HUD_WINDOW_END_POS, true),
	popup_window(POPUP_WINDOW_POS, POPUP_WINDOW_END_POS, true),
	yes_no_window(YES_NO_WINDOW_POS, YES_NO_WINDOW_END_POS, true),
	text_yes_no_window(TEXT_YES_NO_WINDOW_POS, TEXT_YES_NO_WINDOW_END_POS,
		true),

	aux_menu(Menu()),
	popup_menu(Menu()),
	yes_no_menu(Menu()),
	text_yes_no_menu(Menu()) {
	if (_argc <= 0) {
		err("game_engine::Engine::Engine(): Eek!\n");
	} else if (_argc == 1) {
		//printout("testificate\n");
		_save_file_name = DEFAULT_SAVE_FILE_NAME;
	} else if (_argc == 2) {
		_save_file_name = const_cast<const char*>(_argv[1]);
	} else {
		err
			("Usage 1: ", _argv[0], "\n",
			"Usage 2: ", _argv[0], " <save_file_name>\n");
	}
	_curr_file_num = &ecs_engine.curr_file_num;
	_src_file_num = &ecs_engine.src_file_num;
	_copy_dst_file_num = &ecs_engine.copy_dst_file_num;

	//screen_window = Window(this, IntVec2(),
	//		W_BRDR_SCREEN_SIZE_2D, i);
	//for (i32 i=0; i<NUM_FILES; ++i) {
	//	//--------
	//	//_non_ecs_ser_data_arr.push_back(NonEcsSerData());
	//	//--------
	//	//auto add_window = [](auto& vec_etc, Window&& to_push) -> void {
	//	//	//dbg_log("add_window() testificate: ",
	//	//	//	to_push.engine() == nullptr, "\n");
	//	//	vec_etc.push_back(std::move(to_push));
	//	//	//vec_etc.back().init_set_border();
	//	//};
	//	//--------
	//	_screen_window_darr.push_back(Window(
	//		IntVec2(), W_BRDR_SCREEN_SIZE_2D, i
	//	));
	//	_aux_window_darr.push_back(Window(
	//		IntVec2(), W_BRDR_SCREEN_SIZE_2D, i
	//	));
	//	//--------
	//	_pfield_window_darr.push_back(Window(
	//		PFIELD_WINDOW_POS, PFIELD_WINDOW_END_POS, i
	//	));
	//	_log_window_darr.push_back(Window(
	//		LOG_WINDOW_POS, LOG_WINDOW_END_POS, i
	//	));
	//	_hud_window_darr.push_back(Window(
	//		HUD_WINDOW_POS, HUD_WINDOW_END_POS, i
	//	));
	//	_popup_window_darr.push_back(Window(
	//		POPUP_WINDOW_POS, POPUP_WINDOW_END_POS, i
	//	));
	//	_yes_no_window_darr.push_back(Window(
	//		YES_NO_WINDOW_POS, YES_NO_WINDOW_END_POS, i
	//	));
	//	_text_yes_no_window_darr.push_back(Window(
	//		TEXT_YES_NO_WINDOW_POS, TEXT_YES_NO_WINDOW_END_POS, i
	//	));
	//	//--------
	//}

	ecs_engine.init_comp_deserialize<
		//EVAL(DEFER(MAP_INDIRECT)()(ID, COMMA, LIST_OF_COMPS))
		LIST_OF_COMPS
	>();

	//ecs_engine.init_sys_deserialize<
	//	//EVAL(DEFER(MAP_INDIRECT)()(ID, COMMA, LIST_OF_SYSES))
	//	LIST_OF_SYSES
	//>();

	//yes_no_menu
	//	= build_yes_no_menu(this,
	//		std::function<void(Engine*)>(&Engine::_yes_no_menu_act_yes),
	//		std::function<void(Engine*)>(&Engine::_yes_no_menu_act_no));

	#define X(arg) \
		if (ecs_engine.insert_sys(ecs::SysSptr(new sys::Gm ## arg()))) { \
			err("game_engine::Engine::Engine(): ", \
				#arg " internal error\n"); \
		}
	LIST_OF_GAME_MODES(X)
	#undef X

	set_game_mode(GameMode::TitleScreen);

	//dbg_log("Engine::Engine()\n");
	//dbg_check_ecs_engine();
	if (do_create_or_load) {
		_create_or_load_save_file_etc();
	}
	//_load_from_json();
}
//Engine::Engine(const binser::Value& bv) {
//	MEMB_LIST_ENGINE(BINSER_MEMB_DESERIALIZE);
//}
Engine::~Engine() {}

//void Engine::deserialize(const binser::Value& bv, ecs::FileNum file_num) {
//	Engine ret;
//
//	ret.ecs_engine.deserialize(bv["ecs_engine"]);
//
//	BINSER_MEMB_DESERIALIZE
//
//	return ret;
//}
Engine::operator binser::Value () const {
	binser::Value ret;

	//BINSER_MEMB_SERIALIZE(ecs_engine);
	MEMB_SER_LIST_ENGINE(BINSER_MEMB_SERIALIZE);
	//BINSER_MEMB_SERIALIZE(ecs_engine, std::nullopt);
	//BINSER_MEMB_SERIALIZE(game_options, std::nullopt);
	//BINSER_MEMB_SERIALIZE(_non_ecs_ser_data_arr, std::nullopt);

	return ret;
}
void Engine::deserialize(const binser::Value& bv) {
	//BINSER_MEMB_DESERIALIZE(ecs_engine);
	//ecs_engine.deserialize(bv["ecs_engine"]);
	//dbg_log("Engine::deserialize() before: ",
	//	aux_window(0).engine() == nullptr, "\n");
	MEMB_SER_LIST_ENGINE(BINSER_MEMB_DESERIALIZE);
	//dbg_log("Engine::deserialize() after: ",
	//	aux_window(0).engine() == nullptr, "\n");

	for (ecs::FileNum file_num=0; file_num<NUM_FILES; ++file_num) {
		//auto& lr_arr = layout_rng_arr_fn(file_num);
		auto& temp = non_ecs_ser_data_fn(file_num);
		temp.seed_layout_rng_arr(layout_rng_arr_fn(file_num));
		//temp.seed_rngs_etc(layout_rng_arr_fn(file_num));
	}

	#ifdef DEBUG
	dbg_log("Engine::deserialize()\n");
	//dbg_osprint_layout_rng_a2d(std::cout);
	#endif		// DEBUG
}

//void Engine::dbg_check_ecs_engine(const IntVec2& wb_pos) {
//	const ecs::EntId id
//		= screen_window.with_border_ent_id_at(wb_pos);
//
//	if (id != ecs::ENT_NULL_ID) {
//		dbg_log("Engine::dbg_check_ecs_engine(): ",
//			id, " ", ecs_engine.engine_comp_map().contains(id),
//			"\n");
//
//		if (ecs_engine.engine_comp_map().contains(id)) {
//			dbg_log(ecs_engine.comp_map(id).contains(
//					game_engine::comp::Drawable::KIND_STR
//				),
//				"\n"
//			);
//		}
//	}
//}

void Engine::_dbg_log_backend(const std::string& msg) {
	// This is temporary
	//#ifdef DEBUG
	printout(msg);
	//#endif		// DEBUG
}
void Engine::tick() {
	if (!_did_init_window_clear) {
		_did_init_window_clear = true;

		//for (i32 i=0; i<NUM_FILES; ++i) {
		//	_screen_window_darr.at(i).clear();
		//	_aux_window_darr.at(i).clear();
		//	_pfield_window_darr.at(i).clear();
		//	_log_window_darr.at(i).clear();
		//	_hud_window_darr.at(i).clear();
		//	_popup_window_darr.at(i).clear();
		//	_yes_no_window_darr.at(i).clear();
		//	_text_yes_no_window_darr.at(i).clear();
		//}

		screen_window.clear();
		aux_window.clear();
		pfield_window.clear();
		log_window.clear();
		hud_window.clear();
		popup_window.clear();
		yes_no_window.clear();
		text_yes_no_window.clear();
	}
	// testing

	//printerr("Engine::tick(): Note: **NOT** ticking `ecs_engine`.\n");
	//ecs_engine.destroy_scheduled();
	switch (game_mode()) {
	//--------
	#define X(arg) \
		case GameMode::arg: \
			ecs_engine.tick(std::nullopt, sys::Gm##arg::KIND_STR, true); \
			break;
	LIST_OF_GAME_MODES(X)
	#undef X
	default:
		fprintf(stderr,
			"game_engine::Engine::tick(): Internal error!\n");
		exit(1);
		break;
	}
	//--------
	//ecs_engine.tick(std::nullopt, std::nullopt);

	//screen_window.draw(pfield_window);
	//screen_window.draw(log_window);
	//screen_window.draw(hud_window);


	// testing
	//if (
	//	key_status.key_just_went_down(KeyKind::Start)
	//	&& key_status.key_up_now(KeyKind::Select)
	//) {
	//} else if (
	//	key_status.key_just_went_down(KeyKind::Select)
	//	&& key_status.key_up_now(KeyKind::Start)
	//) {
	//}

	{
		// `binser` debugging stuff

		//if (
		//	key_status.key_down_now(KeyKind::ShoulderL)
		//	&& key_status.key_up_now(KeyKind::ShoulderR)
		//) {
		//	_save_to_binser();
		//} else if (
		//	key_status.key_down_now(KeyKind::ShoulderR)
		//	&& key_status.key_up_now(KeyKind::ShoulderL)
		//) {
		//	_create_or_load_save_file_etc();
		//	if (
		//		auto file=std::fstream(DEFAULT_SAVE_FILE_NAME, 
		//			std::ios_base::in);
		//		file.is_open()
		//	) {
		//	//	binser::Value root;
		//	//	std::string errs;

		//	//	parse_json(file, &root, &errs);

		//	//	deserialize(root);
		//	//}
		//}
	}

	{
		//dbg_log("Ticking the game engine: ", _tick_counter, "\n");
		//++_tick_counter;

		//if (game_mode == GameMode::AuxTitleScreen) {
		//	dbg_log("game_engine::Engine::tick(): ",
		//		"Temporary title screen code\n");

		//	yes_no_menu().tick(key_status);

		//	yes_no_window().clear();
		//	yes_no_window().draw(yes_no_menu());

		//	screen_window().clear();
		//	screen_window().draw(yes_no_window());
		//}
	}

}
void Engine::draw_to_main_windows() {
	pfield_window.clear();
	//dngn_gen.dngn_floor().draw();
	dngn_floor().draw();
	screen_window.clear();

	screen_window.draw(engine->hud_window);
	screen_window.draw(engine->log_window);
	screen_window.draw(engine->pfield_window);
}
//--------
void Engine::_create_or_load_save_file_etc() {
	dbg_log("game_engine::Engine::_create_or_load_save_file_etc(): ",
		"testificate\n");

	if (
		auto file=std::fstream(_save_file_name,
			std::ios_base::in | std::ios_base::binary);
		file.is_open()
	) {
		binser::Value root;
		//std::string errs;

		// If the on-computer binser file has not been created yet
		if (file.peek() == decltype(file)::traits_type::eof()) {
			//Engine()._save_to_binser();
		}
		// Else if there's not a valid JSON file
		//else if (!parse_json(file, &root, &errs)) {
		//	err("game_engine::Engine::_create_or_load_save_file_etc(): ",
		//		"JSON parsing error: ", errs);
		//}
		else {
			try {
				#ifdef DEBUG
				printerr("Engine::_create_or_load_save_file_etc(): ",
					"parse_binser(), deserialize()\n");
				#endif		// DEBUG

				binser::parse_binser(file, root);
				//#ifdef DEBUG
				//if (Json::Value jv_root=binser::bv_to_jv(root); true) {
				//	json::write_json
				//		("parsed_binser.json.ignore", &jv_root);
				//}
				//#endif		// DEBUG
				deserialize(root);
			} catch (const std::exception& e) {
				#ifdef DEBUG
				printerr("Error: ", e.what(), "\n");
				#endif		// DEBUG
				corrupted_save_file_err();
			}
			//dbg_log("Testificate: Calling `deserialize()`\n");
		}
	} else {
		//err("game_engine::Engine::_create_or_load_save_file_etc(): ",
		//	"Error opening file called \"", _save_file_name, "\" for ",
		//	"reading.\n");

		//for (ecs::FileNum file_num=0; file_num<NUM_FILES; ++file_num) {
		//	auto& temp = non_ecs_ser_data_fn(file_num);

		//	temp.on_init_or_file_erase_seed_rngs_etc(
		//		layout_rng_arr_fn(file_num), temp.base_rng_seed()
		//	);
		//}
		#ifdef DEBUG
		printerr("Engine::_create_or_load_save_file_etc(): ",
			"creating initial data;");
		#endif		// DEBUG

		for (ecs::FileNum file_num=0; file_num<NUM_FILES; ++file_num) {
			for (size_t floor_num=0; floor_num<NUM_FLOORS; ++floor_num) {
				dngn_floor_arr_fn(file_num).at(floor_num)._pos3_z
					= static_cast<i32>(floor_num);
			}
		}

		_save_to_binser(true);
	}
	//if (
	//	auto ent_id_darr=ecs_engine.ent_id_vec_from_keys_any_fn
	//		({comp::Player::KIND_STR}, 0);
	//	ent_id_darr.size() > 0
	//) {
	//	if (ent_id_darr.size() != 1) {
	//		corrupted_save_file_err();
	//	}
	//	dbg_log("This `game_engine::comp::Player` `EntId` was found: ",
	//		ent_id_darr.front(), "\n");

	//	comp::Player* player = ecs_engine.casted_comp_at_fn<comp::Player>
	//		(ent_id_darr.front(), 0);

	//	dbg_log("game_engine::Engine::_create_or_load_save_file_etc(): ",
	//		"Found `game_engine::comp::Player`: ",
	//		player->level, ".",
	//		"\n");
	//}
	//dbg_log("Testificate: ", ecs_engine.curr_file_num, "\n");
}

//void Engine::_load_from_binser() {
//	binser::Value root;
//
//	deserialize
//}
void Engine::_save_to_binser(bool do_create_or_load) {
	#ifdef DEBUG
	dbg_log("game_engine::Engine::_save_to_binser(): testificate\n");
	#endif		// DEBUG

	//binser::Value root 
	//	= do_create_or_load ? Engine(_argc, _argv, false) : *this;
	binser::Value root;
	if (do_create_or_load) {
		root = Engine(_argc, _argv, false);
	} else {
		root = *this;
	}

	binser::write_binser(_save_file_name, root);

	#ifdef DEBUG
	if (Json::Value jv_root=binser::bv_to_jv(root); true) {
		json::write_json(DEBUG_SAVE_FILE_NAME, &jv_root);
	}
	#endif		// DEBUG
}

void Engine::save_and_quit() {
	#ifdef DEBUG
	dbg_log("game_engine::Engine::save_and_quit(): testificate\n");
	#endif		// DEBUG

	_save_to_binser();
	exit(0);
}
void Engine::save_and_return_to_title() {
	#ifdef DEBUG
	dbg_log("game_engine::Engine::save_and_return_to_title(): ",
		"testificate\n");
	#endif		// DEBUG

	auto& temp = non_ecs_ser_data();
	temp.on_init_or_file_erase_seed_rngs_etc
		(layout_rng_arr(), temp.base_rng_seed());

	_save_to_binser();
	set_game_mode(GameMode::TitleScreen);
}

void Engine::copy_file() {
	#ifdef DEBUG
	dbg_log("game_engine::Engine::copy_file(): testificate\n");
	#endif		// DEBUG
	ecs_engine.copy_file();
	non_ecs_ser_data_fn(*copy_dst_file_num())
		= non_ecs_ser_data_fn(*src_file_num());
	layout_rng_arr_fn(*copy_dst_file_num())
		= layout_rng_arr_fn(*src_file_num());

	#ifdef DEBUG
	dbg_log("Engine::copy_file()\n");
	//dbg_osprint_layout_rng_a2d(std::cout);
	#endif		// DEBUG
}
void Engine::erase_file() {
	#ifdef DEBUG
	dbg_log("game_engine::Engine::erase_file(): testificate\n");
	#endif		// DEBUG
	ecs_engine.erase_file();

	auto& temp = non_ecs_ser_data_fn(*src_file_num());
	temp = NonEcsSerData();
	//layout_rng_arr_fn(*src_file_num()) = LayoutRngArr();
	//temp.seed_layout_rng_arr(layout_rng_arr_fn(*src_file_num()));
	temp.on_init_or_file_erase_seed_rngs_etc
		(layout_rng_arr_fn(*src_file_num()), temp.base_rng_seed());

	//for (ecs::FileNum file_num=0; file_num<NUM_FILES; ++file_num) {
	//	dbg_osprint_layout_rng_arr_fn(std::cout, file_num);
	//	dbg_log("\n");
	//}

	#ifdef DEBUG
	dbg_log("Engine::erase_file()\n");
	//dbg_osprint_layout_rng_a2d(std::cout);
	#endif		// DEBUG
}
void Engine::_inner_draw_menu_w_pre_clear(Window& window, Menu& menu) {
	window.clear();
	window.draw(menu);
	//_screen_window_darr.at(_sel_file_num(file_num)).draw(window);
	screen_window.draw(window);
}

void Engine::position_ctor_callback(comp::Position* obj) {
	_err_when_ent_id_is_null(obj, "position_ctor_callback");

	//auto& ent_id_set = pfield_ent_id_v3d()
	//	.at(obj->pos3().z).at(obj->pos3().y).at(obj->pos3().x);
	auto& ent_id_uset = pfield_ent_id_uset(obj->pos3());

	if (ent_id_uset.contains(obj->ent_id())) {
		fprintf(stderr, sconcat("Engine::position_ctor_callback(): ",
			"Internal error.\n").c_str());
		exit(1);
	}

	ent_id_uset.insert(obj->ent_id());
	dngn_floor_arr().at(obj->floor())._position_ctor_callback(obj);

	// Insert this `obj->ent_id()` into the
	// `game_engine::lvgen_etc::DngnFloor`
	//switch (obj->priority) {

	//if (obj->ent_kind() == comp::Position::EntKind::Item) {
	//	auto& the_dngn_floor = dngn_floor_arr().at(obj->pos3().z);
	//	auto& gnd_item_uset = the_dngn_floor.gnd_item_umap.at(obj->pos2());
	//	if (gnd_item_uset.contains(obj->pos2())) {
	//	}
	//}
}
void Engine::position_dtor_callback(comp::Position* obj) {
	_err_when_ent_id_is_null(obj, "position_dtor_callback");

	//auto& ent_id_set = pfield_ent_id_v3d()
	//	.at(obj->pos3().z).at(obj->pos3().y).at(obj->pos3().x);
	auto& ent_id_uset = pfield_ent_id_uset(obj->pos3());

	if (!ent_id_uset.contains(obj->ent_id())) {
		fprintf(stderr, sconcat("Engine::position_dtor_callback(): ",
			"Internal error.\n").c_str());
		exit(1);
	}

	ent_id_uset.erase(obj->ent_id());
	dngn_floor_arr().at(obj->floor())._position_dtor_callback(obj);
}

void Engine::position_set_pos3_callback(
	comp::Position* obj, const IntVec3& n_pos3
) {
	// I'm pretty sure we don't need to have something like
	// `dngn_floor_arr().at(obj->floor()).position_set_pos3_callback()`

	_err_when_ent_id_is_null(obj, "position_set_pos3_callback");

	position_dtor_callback(obj);
	const i32 old_floor = obj->floor();
	//obj->_pos3 = n_pos3;
	obj->_pos3.back_up_and_update(n_pos3)();
	if (old_floor != obj->floor()) {
		obj->_prev_floor = old_floor;
	}
	//obj->_pos2.back_up_and_update({.x=n_pos3.x, .y=n_pos.y});
	//obj->_floor.back_up_and_update(n_pos3.z)
	position_ctor_callback(obj);
}

GameMode& Engine::set_game_mode(GameMode n_game_mode) {
	//dbg_log("old _game_mode: ", i32(_game_mode), "\n");
	_game_mode = n_game_mode;
	//dbg_log("new _game_mode: ", i32(_game_mode), "\n");

	switch (game_mode()) {
	//--------
	#define X(arg) \
		case GameMode::arg: \
			ecs_engine.sys_umap().at(sys::Gm##arg::KIND_STR) \
				->prep_init(); \
			break;
	LIST_OF_GAME_MODES(X)
	#undef X
	default:
		fprintf(stderr,
			"game_engine::Engine::set_game_mode(): Internal error!\n");
		exit(1);
		break;
	//--------
	}

	return _game_mode;
}

//void Engine::_yes_no_menu_act_yes(Engine* self) {
//	dbg_log("yes_no_menu: \"Yes\" button activated!\n");
//}
//void Engine::_yes_no_menu_act_no(Engine* self) {
//	dbg_log("yes_no_menu: \"No\" button activated!\n");
//}

//void Engine::_save() {
//}

Engine* engine = nullptr;
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon
