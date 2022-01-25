// This file is part of Dungwich Sandeon.
// 
// Copyright 2022 FL4SHK
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

#include "engine_class.hpp"
#include "comp/block_comp_classes.hpp"
#include "comp/ui_etc_comp_classes.hpp"
#include "sys/gm_title_screen_class.hpp"
#include "sys/gm_options_class.hpp"
#include "sys/gm_file_select_class.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
//--------
KeyStatus::KeyStatus()
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
KeyStatus::~KeyStatus()
{
}
//--------

const std::string Engine::SAVE_FILE_NAME("save_file.json");

Engine::Engine()
	: screen_window(this, PosVec2(), WITH_BORDER_SCREEN_SIZE_2D),
	aux_window(this, PosVec2(), WITH_BORDER_SCREEN_SIZE_2D),

	playfield_window(this, PLAYFIELD_WINDOW_POS, PLAYFIELD_WINDOW_END_POS),
	log_window(this, LOG_WINDOW_POS, LOG_WINDOW_END_POS),
	hud_window(this, HUD_WINDOW_POS, HUD_WINDOW_END_POS),
	popup_window(this, POPUP_WINDOW_POS, POPUP_WINDOW_END_POS),
	yes_no_window(this, YES_NO_WINDOW_POS, YES_NO_WINDOW_END_POS),
	text_yes_no_window(this, TEXT_YES_NO_WINDOW_POS,
		TEXT_YES_NO_WINDOW_END_POS),

	playfield_ent_id_v3d(NUM_FLOORS,
		EntIdSetVec2d(PLAYFIELD_WINDOW_SIZE_2D.y,
			std::vector<std::set<ecs::EntId>>(PLAYFIELD_WINDOW_SIZE_2D.x)))
{
	screen_window.init_set_border();
	aux_window.init_set_border();

	playfield_window.init_set_border();
	log_window.init_set_border();
	hud_window.init_set_border();
	popup_window.init_set_border();
	yes_no_window.init_set_border();
	text_yes_no_window.init_set_border();

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
Engine::~Engine()
{
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

	//	yes_no_menu.tick(key_status);

	//	yes_no_window.clear();
	//	yes_no_window.draw(yes_no_menu);

	//	screen_window.clear();
	//	screen_window.draw(yes_no_window);
	//}
}

//void Engine::load_file()
//{
//}

void Engine::save_and_quit()
{
	//printout("game_engine::Engine::save_and_quit(): testificate\n");

	_save_file();
	exit(0);
}
void Engine::save_and_return_to_title()
{
	//printout("game_engine::Engine::save_and_return_to_title(): ",
	//	"testificate\n");

	_save_file();
	set_game_mode(GameMode::TitleScreen);
}

void Engine::load_file()
{
}
void Engine::copy_file()
{
}
void Engine::erase_file()
{
}
void Engine::_save_file()
{
}

void Engine::position_ctor_callback(comp::Position* obj)
{
	_err_when_ent_id_is_null(obj, "position_ctor_callback");

	auto& ent_id_set = playfield_ent_id_v3d.at(obj->pos().z)
		.at(obj->pos().y).at(obj->pos().x);
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

	auto& ent_id_set = playfield_ent_id_v3d.at(obj->pos().z)
		.at(obj->pos().y).at(obj->pos().x);
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
	_game_mode = n_game_mode;
	//printout("new _game_mode: ", (int)_game_mode, "\n");

	switch (game_mode())
	{
	//--------
	#define X(arg) \
		case GameMode::arg: \
			ecs_engine.sys_map().at(sys::Gm##arg::KIND_STR)->did_init \
				= false; \
			ecs_engine.sys_map().at(sys::Gm##arg::KIND_STR)->active \
				.back_up_and_update(false); \
			ecs_engine.sys_map().at(sys::Gm##arg::KIND_STR)->active \
				.back_up_and_update(true); \
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
} // namespace dungwich_sandeon
