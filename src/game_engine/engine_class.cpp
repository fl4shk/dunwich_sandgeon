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

#include "engine_class.hpp"

#include "comp/list_of_comp_defines.hpp"

#include "comp/general_comp_classes.hpp"
#include "comp/player_comp_class.hpp"
//#include "comp/block_comp_classes.hpp"
#include "comp/floor_layout_comp_classes.hpp"
#include "comp/status_comp_classes.hpp"
//#include "comp/ui_etc_comp_classes.hpp"

#include "sys/list_of_sys_defines.hpp"

#include "sys/gm_title_screen_class.hpp"
#include "sys/gm_options_class.hpp"
#include "sys/gm_file_select_class.hpp"
#include "sys/gm_dungeon_gen_class.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
//--------
const std::string
	Engine::DEFAULT_SAVE_FILE_NAME("save_file.binser.ignore"),
	Engine::DEBUG_SAVE_FILE_NAME("debug_save_file.json.ignore");
//--------
//auto Engine::NonEcsSerData::_gen_blank_pfield_ent_id_v3d()
//	-> decltype(pfield_ent_id_v3d)
//{
//	return
//		decltype(pfield_ent_id_v3d)
//		(
//			NUM_FLOORS,
//			EntIdSetVec2d(PFIELD_WINDOW_SIZE_2D.y,
//				std::vector<std::unordered_set<ecs::EntId>>
//					(PFIELD_WINDOW_SIZE_2D.x,
//					std::unordered_set<ecs::EntId>()))
//		);
//}

Engine::NonEcsSerData::NonEcsSerData()
	//: pfield_ent_id_v3d(_gen_blank_pfield_ent_id_v3d())
{
	//const auto& time_count = get_hrc_now().time_since_epoch().count();
	//rng.seed(time_count, time_count + 1, time_count + 2);
}
Engine::NonEcsSerData::NonEcsSerData(const binser::Value& bv)
{
	MEMB_AUTOSER_LIST_ENGINE_NON_ECS_SER_DATA(BINSER_MEMB_DESERIALIZE);

	//{
	//	//std::vector<std::string> vec;
	//	//binser::get_bv_memb(vec, bv, "layout_rng_arr", std::nullopt);

	//	//if (vec.size() != Engine::NUM_FLOORS)
	//	//{
	//	//	const std::string err_msg(sconcat
	//	//		("game_engine::Engine::NonEcsSerData::NonEcsSerData",
	//	//		"(const binser::Value&): Wrong `vec.size()` value of ",
	//	//		vec.size(), "."));
	//	//	throw std::invalid_argument(err_msg.c_str());
	//	//}

	//	//for (i32 i=0; i<Engine::NUM_FLOORS; ++i)
	//	//{
	//	//	Rng layout_rng;
	//	//	inv_sconcat(vec.at(i), layout_rng);
	//	//	layout_rng_arr.at(i) = std::move(layout_rng);
	//	//}
	//}

	{
		std::string str;
		binser::get_bv_memb(str, bv, "_rng", std::nullopt);
		inv_sconcat(str, _rng);
	}
}

Engine::NonEcsSerData::~NonEcsSerData()
{
}

Engine::NonEcsSerData::operator binser::Value () const
{
	binser::Value ret;

	MEMB_AUTOSER_LIST_ENGINE_NON_ECS_SER_DATA(BINSER_MEMB_SERIALIZE);
	//binser::set_bv_memb(ret, "rng", sconcat(rng));
	//{
	//	std::vector<std::string> vec;
	//	for (const auto& layout_rng: layout_rng_arr)
	//	{
	//		vec.push_back(sconcat(layout_rng));
	//	}
	//	binser::set_bv_memb(ret, "layout_rng_arr", vec);
	//}
	binser::set_bv_memb(ret, "_rng", sconcat(_rng));

	return ret;
}

//--------
Engine::Engine(int s_argc, char** s_argv, bool do_create_or_load)
	: _argc(s_argc), _argv(s_argv),
	ecs_engine(NUM_FILES),

	//_non_ecs_ser_data_arr(NUM_FILES, NonEcsSerData()),
	key_status(size_t(KeyKind::Lim)),

	screen_window(PosVec2(), WITH_BORDER_SCREEN_SIZE_2D),
	aux_window(PosVec2(), WITH_BORDER_SCREEN_SIZE_2D),

	pfield_window(PFIELD_WINDOW_POS, PFIELD_WINDOW_END_POS),
	log_window(LOG_WINDOW_POS, LOG_WINDOW_END_POS),
	hud_window(HUD_WINDOW_POS, HUD_WINDOW_END_POS),
	popup_window(POPUP_WINDOW_POS, POPUP_WINDOW_END_POS),
	yes_no_window(YES_NO_WINDOW_POS, YES_NO_WINDOW_END_POS),
	text_yes_no_window(TEXT_YES_NO_WINDOW_POS, TEXT_YES_NO_WINDOW_END_POS),

	aux_menu(Menu()),
	popup_menu(Menu()),
	yes_no_menu(Menu()),
	text_yes_no_menu(Menu())
{
	if (_argc <= 0)
	{
		err("Engine::Engine(): Eek!\n");
	}
	else if (_argc == 1)
	{
		_save_file_name = DEFAULT_SAVE_FILE_NAME;
	}
	else if (_argc == 2)
	{
		_save_file_name = const_cast<const char*>(_argv[1]);
	}
	else
	{
		err
		(
			"Usage 1: ", _argv[0], "\n",
			"Usage 2: ", _argv[0], " <save_file_name>\n"
		);
	}
	_curr_file_num = &ecs_engine.curr_file_num;
	_src_file_num = &ecs_engine.src_file_num;
	_copy_dst_file_num = &ecs_engine.copy_dst_file_num;

	//screen_window = Window(this, PosVec2(),
	//		WITH_BORDER_SCREEN_SIZE_2D, i);
	//for (i32 i=0; i<NUM_FILES; ++i)
	//{
	//	//--------
	//	//_non_ecs_ser_data_arr.push_back(NonEcsSerData());
	//	//--------
	//	//auto add_window = [](auto& vec_etc, Window&& to_push) -> void
	//	//{
	//	//	//printout("add_window() testificate: ",
	//	//	//	to_push.engine() == nullptr, "\n");
	//	//	vec_etc.push_back(std::move(to_push));
	//	//	//vec_etc.back().init_set_border();
	//	//};
	//	//--------
	//	_screen_window_vec.push_back
	//		(Window(PosVec2(), WITH_BORDER_SCREEN_SIZE_2D, i));
	//	_aux_window_vec.push_back
	//		(Window(PosVec2(), WITH_BORDER_SCREEN_SIZE_2D, i));
	//	//--------
	//	_pfield_window_vec.push_back
	//		(Window(PFIELD_WINDOW_POS, PFIELD_WINDOW_END_POS, i));
	//	_log_window_vec.push_back
	//		(Window(LOG_WINDOW_POS, LOG_WINDOW_END_POS, i));
	//	_hud_window_vec.push_back
	//		(Window(HUD_WINDOW_POS, HUD_WINDOW_END_POS, i));
	//	_popup_window_vec.push_back
	//		(Window(POPUP_WINDOW_POS, POPUP_WINDOW_END_POS, i));
	//	_yes_no_window_vec.push_back
	//		(Window(YES_NO_WINDOW_POS, YES_NO_WINDOW_END_POS, i));
	//	_text_yes_no_window_vec.push_back
	//		(Window(TEXT_YES_NO_WINDOW_POS, TEXT_YES_NO_WINDOW_END_POS,
	//			i));
	//	//--------
	//}

	ecs_engine.init_comp_deserialize
	<
		//EVAL(DEFER(MAP_INDIRECT)()(ID, COMMA, LIST_OF_COMP))
		LIST_OF_COMP
	>();

	//ecs_engine.init_sys_deserialize
	//<
	//	//EVAL(DEFER(MAP_INDIRECT)()(ID, COMMA, LIST_OF_SYS))
	//	LIST_OF_SYS
	//>();

	//yes_no_menu
	//	= build_yes_no_menu(this,
	//		std::function<void(Engine*)>(&Engine::_yes_no_menu_act_yes),
	//		std::function<void(Engine*)>(&Engine::_yes_no_menu_act_no));

	#define X(arg) \
		if (ecs_engine.insert_sys(ecs::SysSptr(new sys::Gm ## arg()))) \
		{ \
			err("game_engine::Engine::Engine(): ", \
				#arg " internal error\n"); \
		}
	LIST_OF_GAME_MODES(X)
	#undef X

	set_game_mode(GameMode::TitleScreen);

	//printout("Engine::Engine()\n");
	//dbg_check_ecs_engine();
	if (do_create_or_load)
	{
		_create_or_load_save_file_etc();
	}
	//_load_from_json();
}
//Engine::Engine(const binser::Value& bv)
//{
//	MEMB_LIST_ENGINE(BINSER_MEMB_DESERIALIZE);
//}
Engine::~Engine()
{
}

//void Engine::deserialize(const binser::Value& bv, ecs::FileNum file_num)
//{
//	Engine ret;
//
//	ret.ecs_engine.deserialize(bv["ecs_engine"]);
//
//	BINSER_MEMB_DESERIALIZE
//
//	return ret;
//}
Engine::operator binser::Value () const
{
	binser::Value ret;

	//BINSER_MEMB_SERIALIZE(ecs_engine);
	MEMB_SER_LIST_ENGINE(BINSER_MEMB_SERIALIZE);

	return ret;
}
void Engine::deserialize(const binser::Value& bv)
{
	//BINSER_MEMB_DESERIALIZE(ecs_engine);
	//ecs_engine.deserialize(bv["ecs_engine"]);
	//printout("Engine::deserialize() before: ",
	//	aux_window(0).engine() == nullptr, "\n");
	MEMB_SER_LIST_ENGINE(BINSER_MEMB_DESERIALIZE);
	//printout("Engine::deserialize() after: ",
	//	aux_window(0).engine() == nullptr, "\n");

	for (ecs::FileNum file_num=0; file_num<NUM_FILES; ++file_num)
	{
		//auto& lr_arr = layout_rng_arr_fn(file_num);
		non_ecs_ser_data_fn(file_num).seed_layout_rng_arr
			(layout_rng_arr_fn(file_num));
	}

	//#ifdef DEBUG
	//printout("Engine::deserialize()\n");
	//dbg_osprint_layout_rng_a2d(std::cout);
	//#endif		// DEBUG
}

//void Engine::dbg_check_ecs_engine(const PosVec2& wb_pos)
//{
//	const ecs::EntId id
//		= screen_window.with_border_ent_id_at(wb_pos);
//
//	if (id != ecs::ENT_NULL_ID)
//	{
//		printout("Engine::dbg_check_ecs_engine(): ",
//			id, " ", ecs_engine.engine_comp_map().contains(id),
//			"\n");
//
//		if (ecs_engine.engine_comp_map().contains(id))
//		{
//			printout(ecs_engine.comp_map(id).contains
//				(game_engine::comp::Drawable::KIND_STR),
//				"\n");
//		}
//	}
//}

void Engine::tick()
{
	if (!_did_init_window_clear)
	{
		_did_init_window_clear = true;

		//for (i32 i=0; i<NUM_FILES; ++i)
		//{
		//	_screen_window_vec.at(i).clear();
		//	_aux_window_vec.at(i).clear();
		//	_pfield_window_vec.at(i).clear();
		//	_log_window_vec.at(i).clear();
		//	_hud_window_vec.at(i).clear();
		//	_popup_window_vec.at(i).clear();
		//	_yes_no_window_vec.at(i).clear();
		//	_text_yes_no_window_vec.at(i).clear();
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

	ecs_engine.tick();

	// testing
	//if (key_status.key_just_went_down(KeyKind::Start)
	//	&& key_status.key_up_now(KeyKind::Select))
	//{
	//}
	//else if (key_status.key_just_went_down(KeyKind::Select)
	//	&& key_status.key_up_now(KeyKind::Start))
	//{
	//}

	if (key_status.key_down_now(KeyKind::ShoulderL)
		&& key_status.key_up_now(KeyKind::ShoulderR))
	{
		_save_to_binser();
	}
	else if (key_status.key_down_now(KeyKind::ShoulderR)
		&& key_status.key_up_now(KeyKind::ShoulderL))
	{
		_create_or_load_save_file_etc();
		//if (auto file=std::fstream(DEFAULT_SAVE_FILE_NAME, 
		//	std::ios_base::in);
		//	file.is_open())
		//{
		//	binser::Value root;
		//	std::string errs;

		//	parse_json(file, &root, &errs);

		//	deserialize(root);
		//}
	}
	//printout("Ticking the game engine: ", _tick_counter, "\n");
	//++_tick_counter;

	//if (game_mode == GameMode::AuxTitleScreen)
	//{
	//	printout("game_engine::Engine::tick(): ",
	//		"Temporary title screen code\n");

	//	yes_no_menu().tick(key_status);

	//	yes_no_window().clear();
	//	yes_no_window().draw(yes_no_menu());

	//	screen_window().clear();
	//	screen_window().draw(yes_no_window());
	//}
}
//--------
void Engine::_create_or_load_save_file_etc()
{
	printout("game_engine::Engine::_create_or_load_save_file_etc(): ",
		"testificate\n");

	if (auto file=std::fstream(_save_file_name,
		std::ios_base::in | std::ios_base::binary);
		file.is_open())
	{
		binser::Value root;
		//std::string errs;

		// If the on-computer JSON file has not been created yet
		if (file.peek() == decltype(file)::traits_type::eof())
		{
			//Engine()._save_to_binser();
		}
		// Else if there's not a valid JSON file
		//else if (!parse_json(file, &root, &errs))
		//{
		//	err("game_engine::Engine::_create_or_load_save_file_etc(): ",
		//		"JSON parsing error: ", errs);
		//}
		else
		{
			try
			{
				binser::parse_binser(file, root);
				deserialize(root);
			}
			catch (const std::exception& e)
			{
				#ifdef DEBUG
				printerr("Error: ", e.what(), "\n");
				#endif		// DEBUG
				err("Error: corrupted save file ",
					"\"", _save_file_name, "\".",
					"\n");
			}
			//printout("Testificate: Calling `deserialize()`\n");
		}
	}
	else
	{
		//err("game_engine::Engine::_create_or_load_save_file_etc(): ",
		//	"Error opening file called \"", _save_file_name, "\" for ",
		//	"reading.\n");
		_save_to_binser(true);
	}
	//printout("Testificate: ", ecs_engine.curr_file_num, "\n");
}

//void Engine::_load_from_binser()
//{
//	binser::Value root;
//
//	deserialize
//}
void Engine::_save_to_binser(bool do_create_or_load)
{
	#ifdef DEBUG
	printout("game_engine::Engine::_save_to_binser(): testificate\n");
	#endif		// DEBUG

	//binser::Value root 
	//	= do_create_or_load ? Engine(_argc, _argv, false) : *this;
	binser::Value root;
	if (do_create_or_load)
	{
		root = Engine(_argc, _argv, false);
	}
	else
	{
		root = *this;
	}

	binser::write_binser(_save_file_name, root);

	#ifdef DEBUG
	if (Json::Value jv_root=binser::bv_to_jv(root); true)
	{
		json::write_json(DEBUG_SAVE_FILE_NAME, &jv_root);
	}
	#endif		// DEBUG
}

void Engine::save_and_quit()
{
	#ifdef DEBUG
	printout("game_engine::Engine::save_and_quit(): testificate\n");
	#endif		// DEBUG

	_save_to_binser();
	exit(0);
}
void Engine::save_and_return_to_title()
{
	#ifdef DEBUG
	printout("game_engine::Engine::save_and_return_to_title(): ",
		"testificate\n");
	#endif		// DEBUG

	_save_to_binser();
	set_game_mode(GameMode::TitleScreen);
}

void Engine::copy_file()
{
	#ifdef DEBUG
	printout("game_engine::Engine::copy_file(): testificate\n");
	#endif		// DEBUG
	ecs_engine.copy_file();
	non_ecs_ser_data_fn(*copy_dst_file_num())
		= non_ecs_ser_data_fn(*src_file_num());
	layout_rng_arr_fn(*copy_dst_file_num())
		= layout_rng_arr_fn(*src_file_num());

	//#ifdef DEBUG
	//printout("Engine::copy_file()\n");
	//dbg_osprint_layout_rng_a2d(std::cout);
	//#endif		// DEBUG
}
void Engine::erase_file()
{
	#ifdef DEBUG
	printout("game_engine::Engine::erase_file(): testificate\n");
	#endif		// DEBUG
	ecs_engine.erase_file();

	auto& temp = non_ecs_ser_data_fn(*src_file_num());
	temp = NonEcsSerData();
	//layout_rng_arr_fn(*src_file_num()) = LayoutRngArr();
	temp.seed_layout_rng_arr(layout_rng_arr_fn(*src_file_num()));

	//for (ecs::FileNum file_num=0; file_num<NUM_FILES; ++file_num)
	//{
	//	dbg_osprint_layout_rng_arr_fn(file_num);
	//}

	//#ifdef DEBUG
	//printout("Engine::erase_file()\n");
	//dbg_osprint_layout_rng_a2d(std::cout);
	//#endif		// DEBUG
}
void Engine::_inner_draw_menu_w_pre_clear(Window& window, Menu& menu)
{
	window.clear();
	window.draw(menu);
	//_screen_window_vec.at(_sel_file_num(file_num)).draw(window);
	screen_window.draw(window);
}

void Engine::position_ctor_callback(comp::Position* obj)
{
	_err_when_ent_id_is_null(obj, "position_ctor_callback");

	//auto& ent_id_set = pfield_ent_id_v3d()
	//	.at(obj->pos().z).at(obj->pos().y).at(obj->pos().x);
	auto& ent_id_set = pfield_ent_id_set(obj->pos());

	if (ent_id_set.contains(obj->ent_id()))
	{
		fprintf(stderr, sconcat("Engine::position_ctor_callback(): ",
			"Internal error.\n").c_str());
		exit(1);
	}

	ent_id_set.insert(obj->ent_id());
}
void Engine::position_dtor_callback(comp::Position* obj)
{
	_err_when_ent_id_is_null(obj, "position_dtor_callback");

	//auto& ent_id_set = pfield_ent_id_v3d()
	//	.at(obj->pos().z).at(obj->pos().y).at(obj->pos().x);
	auto& ent_id_set = pfield_ent_id_set(obj->pos());

	if (!ent_id_set.contains(obj->ent_id()))
	{
		fprintf(stderr, sconcat("Engine::position_dtor_callback(): ",
			"Internal error.\n").c_str());
		exit(1);
	}

	ent_id_set.erase(obj->ent_id());
}

void Engine::position_set_pos_callback(comp::Position* obj,
	const PosVec3& n_pos)
{
	_err_when_ent_id_is_null(obj, "position_set_pos_callback");

	position_dtor_callback(obj);
	obj->_pos = n_pos;
	position_ctor_callback(obj);
}

GameMode& Engine::set_game_mode(GameMode n_game_mode)
{
	//printout("old _game_mode: ", int(_game_mode), "\n");
	_game_mode = n_game_mode;
	//printout("new _game_mode: ", int(_game_mode), "\n");

	switch (game_mode())
	{
	//--------
	#define X(arg) \
		case GameMode::arg: \
			ecs_engine.sys_map().at(sys::Gm##arg::KIND_STR) \
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

//void Engine::_yes_no_menu_act_yes(Engine* self)
//{
//	printout("yes_no_menu: \"Yes\" button activated!\n");
//}
//void Engine::_yes_no_menu_act_no(Engine* self)
//{
//	printout("yes_no_menu: \"No\" button activated!\n");
//}

//void Engine::_save()
//{
//}

Engine* engine = nullptr;
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon
