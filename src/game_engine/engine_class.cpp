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
#include "comp/block_comp_classes.hpp"
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
const std::string Engine::SAVE_FILE_NAME("save_file.json");
//--------
auto Engine::NonEcsSerData::_gen_blank_pfield_ent_id_v3d()
	-> decltype(pfield_ent_id_v3d)
{
	return
		decltype(pfield_ent_id_v3d)
		(
			NUM_FLOORS,
			EntIdSetVec2d(PFIELD_WINDOW_SIZE_2D.y,
				std::vector<std::set<ecs::EntId>>
					(PFIELD_WINDOW_SIZE_2D.x))
		);
}

Engine::NonEcsSerData::NonEcsSerData()
	: pfield_ent_id_v3d(_gen_blank_pfield_ent_id_v3d())
{
}
Engine::NonEcsSerData::NonEcsSerData(const Json::Value& jv)
{
	MEMB_LIST_ENGINE_NON_ECS_SER_DATA(JSON_MEMB_DESERIALIZE);
}

Engine::NonEcsSerData::~NonEcsSerData()
{
}

Engine::NonEcsSerData::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_ENGINE_NON_ECS_SER_DATA(JSON_MEMB_SERIALIZE);

	return ret;
}
//--------
Engine::Engine()
	: ecs_engine(NUM_FILES),

	_non_ecs_ser_data_vec(NUM_FILES, NonEcsSerData()),
	key_status(static_cast<size_t>(KeyKind::Lim)),

	//screen_window(this, PosVec2(), WITH_BORDER_SCREEN_SIZE_2D,
	//	USE_CURR_FILE_NUM),
	//_screen_window_vec(NUM_FILES,
	//	Window(this, PosVec2(), WITH_BORDER_SCREEN_SIZE_2D)),
	//_aux_window_vec(NUM_FILES,
	//	Window(this, PosVec2(), WITH_BORDER_SCREEN_SIZE_2D)),

	//_pfield_window_vec(NUM_FILES,
	//	Window(this, PFIELD_WINDOW_POS, PFIELD_WINDOW_END_POS)),
	//_log_window_vec(NUM_FILES,
	//	Window(this, LOG_WINDOW_POS, LOG_WINDOW_END_POS)),
	//_hud_window_vec(NUM_FILES,
	//	Window(this, HUD_WINDOW_POS, HUD_WINDOW_END_POS)),
	//_popup_window_vec(NUM_FILES,
	//	Window(this, POPUP_WINDOW_POS, POPUP_WINDOW_END_POS)),
	//_yes_no_window_vec(NUM_FILES,
	//	Window(this, YES_NO_WINDOW_POS, YES_NO_WINDOW_END_POS)),
	//_text_yes_no_window_vec(NUM_FILES,
	//	Window(this, TEXT_YES_NO_WINDOW_POS, TEXT_YES_NO_WINDOW_END_POS)),

	_aux_menu_vec(NUM_FILES, Menu()),
	_popup_menu_vec(NUM_FILES, Menu()),
	_yes_no_menu_vec(NUM_FILES, Menu()),
	_text_yes_no_menu_vec(NUM_FILES, Menu())
{
	_curr_file_num = &ecs_engine.curr_file_num;

	//screen_window = Window(this, PosVec2(),
	//		WITH_BORDER_SCREEN_SIZE_2D, i);
	for (int i=0; i<NUM_FILES; ++i)
	{
		//--------
		//_non_ecs_ser_data_vec.push_back(NonEcsSerData());
		//--------
		auto add_window = [](auto& vec_etc, Window&& to_push) -> void
		{
			vec_etc.push_back(std::move(to_push));
			vec_etc.back().init_set_border();
		};
		//--------
		add_window(_screen_window_vec,
			Window(this, PosVec2(),
				WITH_BORDER_SCREEN_SIZE_2D, i));
		add_window(_aux_window_vec,
			Window(this, PosVec2(),
				WITH_BORDER_SCREEN_SIZE_2D, i));
		//--------
		add_window(_pfield_window_vec,
			Window(this,
				PFIELD_WINDOW_POS, PFIELD_WINDOW_END_POS, i));
		add_window(_log_window_vec,
			Window(this,
				LOG_WINDOW_POS, LOG_WINDOW_END_POS, i));
		add_window(_hud_window_vec,
			Window(this,
				HUD_WINDOW_POS, HUD_WINDOW_END_POS, i));
		add_window(_popup_window_vec,
			Window(this,
				POPUP_WINDOW_POS, POPUP_WINDOW_END_POS, i));
		add_window(_yes_no_window_vec,
			Window(this,
				YES_NO_WINDOW_POS, YES_NO_WINDOW_END_POS, i));
		add_window(_text_yes_no_window_vec,
			Window(this,
				TEXT_YES_NO_WINDOW_POS, TEXT_YES_NO_WINDOW_END_POS, i));
		//--------
	}

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
		if (ecs_engine.insert_sys(ecs::SysUptr(new sys::Gm ## arg()))) \
		{ \
			fprintf(stderr, "game_engine::Engine::Engine(): " \
				#arg " internal error\n"); \
			exit(1); \
		}
	LIST_OF_GAME_MODES(X)
	#undef X

	set_game_mode(GameMode::TitleScreen);

	//printout("Engine::Engine()\n");
	//dbg_check_ecs_engine();
}
//Engine::Engine(const Json::Value& jv)
//{
//	MEMB_LIST_ENGINE(JSON_MEMB_DESERIALIZE);
//}
Engine::~Engine()
{
}

//void Engine::deserialize(const Json::Value& jv, int file_num)
//{
//	Engine ret;
//
//	ret.ecs_engine.deserialize(jv["ecs_engine"]);
//
//	JSON_MEMB_DESERIALIZE
//
//	return ret;
//}
Engine::operator Json::Value () const
{
	Json::Value ret;

	//JSON_MEMB_SERIALIZE(ecs_engine);
	MEMB_LIST_ENGINE(JSON_MEMB_SERIALIZE);

	return ret;
}
void Engine::deserialize(const Json::Value& jv)
{
	//JSON_MEMB_DESERIALIZE(ecs_engine);
	//ecs_engine.deserialize(jv["ecs_engine"]);
	MEMB_LIST_ENGINE(JSON_MEMB_DESERIALIZE);
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
	ecs_engine.tick();
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
void Engine::_create_save_file_if_needed()
{
	printout("game_engine::Engine::_create_save_file_if_needed(): ",
		"testificate\n");

	if (auto file=std::fstream(SAVE_FILE_NAME, std::ios_base::in);
		file.is_open())
	{
		Json::Value root;
		std::string errs;

		// If the on-computer JSON file has not been created yet
		if (file.peek() == decltype(file)::traits_type::eof())
		{
			Engine()._save_to_json();
		}
		// Else if there's not a valid JSON file
		else if (!parse_json(file, &root, &errs))
		{
			printerr("game_engine::Engine::_create_save_file_if_needed(): ",
				"JSON parsing error: ", errs);
			exit(1);
		}
		else
		{
			return;
		}
	}
	else
	{
		printerr("game_engine::Engine::_create_save_file_if_needed(): ",
			"Error opening file called \"", SAVE_FILE_NAME, "\" for ",
			"reading.\n");
		exit(1);
	}
}

void Engine::_load_from_json()
{
}
void Engine::_save_to_json()
{
	printout("game_engine::Engine::_save_file(): testificate\n");
}

void Engine::save_and_quit()
{
	printout("game_engine::Engine::save_and_quit(): testificate\n");

	_save_to_json();
	exit(0);
}
void Engine::save_and_return_to_title()
{
	printout("game_engine::Engine::save_and_return_to_title(): ",
		"testificate\n");

	_save_to_json();
	set_game_mode(GameMode::TitleScreen);
}

void Engine::copy_file()
{
	printout("game_engine::Engine::copy_file(): testificate\n");
}
void Engine::erase_file()
{
	printout("game_engine::Engine::erase_file(): testificate\n");
}
void Engine::_inner_draw_menu_w_pre_clear(Window& window, Menu& menu,
	int file_num)
{
	window.clear();
	window.draw(menu);
	//_screen_window_vec.at(_sel_file_num(file_num)).draw(window);
	screen_window().draw(window);
}

void Engine::position_ctor_callback(comp::Position* obj)
{
	_err_when_ent_id_is_null(obj, "position_ctor_callback");

	auto& ent_id_set = pfield_ent_id_v3d_cfn()
		.at(obj->pos().z).at(obj->pos().y).at(obj->pos().x);
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

	auto& ent_id_set = pfield_ent_id_v3d_cfn()
		.at(obj->pos().z).at(obj->pos().y).at(obj->pos().x);
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
	//printout("old _game_mode: ", (int)_game_mode, "\n");
	_game_mode = n_game_mode;
	//printout("new _game_mode: ", (int)_game_mode, "\n");

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
