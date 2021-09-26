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

#include "engine_class.hpp"
#include "comp/block_comp_classes.hpp"
#include "comp/ui_etc_comp_classes.hpp"
#include "sys/gm_aux_title_screen_class.hpp"

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

const PosVec2 
	Engine::PLAYFIELD_WINDOW_POS(0, 0),

	Engine::PLAYFIELD_WINDOW_END_POS
		(Window::WITH_BORDER_SCREEN_SIZE_2D.x - 1 - 20,
		Window::WITH_BORDER_SCREEN_SIZE_2D.y - 1 - 10);

const SizeVec2
	Engine::PLAYFIELD_WINDOW_SIZE_2D
		(Engine::PLAYFIELD_WINDOW_END_POS.x
			- Engine::PLAYFIELD_WINDOW_POS.x + 1,
		Engine::PLAYFIELD_WINDOW_END_POS.y
			- Engine::PLAYFIELD_WINDOW_POS.y + 1);

const PosVec2 
	Engine::LOG_WINDOW_POS
		(0,
		Engine::PLAYFIELD_WINDOW_END_POS.y),

	Engine::LOG_WINDOW_END_POS
		(Engine::PLAYFIELD_WINDOW_END_POS.x,
		Window::WITH_BORDER_SCREEN_SIZE_2D.y - 1),

	Engine::HUD_WINDOW_POS
		(Engine::PLAYFIELD_WINDOW_END_POS.x,
		Engine::PLAYFIELD_WINDOW_POS.y),

	Engine::HUD_WINDOW_END_POS
		(Window::WITH_BORDER_SCREEN_SIZE_2D.x - 1,
		Window::WITH_BORDER_SCREEN_SIZE_2D.y - 1),

	Engine::POPUP_WINDOW_POS
		(13,
		10),

	Engine::POPUP_WINDOW_END_POS
		(Engine::HUD_WINDOW_POS.x - 1,
		Window::WITH_BORDER_SCREEN_SIZE_2D.y - 15),

	Engine::YES_NO_WINDOW_POS
		(2,
		Window::WITH_BORDER_SCREEN_SIZE_2D.y / 2),

	Engine::YES_NO_WINDOW_END_POS
		(Engine::YES_NO_WINDOW_POS.x + 3 +
		MsgLog::WIDGET_SELECTED_SPACING_SIZE + Menu::WIDGET_SPACING_SIZE
		+ 1,
		Engine::YES_NO_WINDOW_POS.y + 2 + 1 + 2); // "+ 4" is temporary

Engine::Engine()
	: screen_window(this, PosVec2(), Window::WITH_BORDER_SCREEN_SIZE_2D),
	aux_window(this, PosVec2(), Window::WITH_BORDER_SCREEN_SIZE_2D),

	playfield_window(this, PLAYFIELD_WINDOW_POS, PLAYFIELD_WINDOW_END_POS),
	log_window(this, LOG_WINDOW_POS, LOG_WINDOW_END_POS),
	hud_window(this, HUD_WINDOW_POS, HUD_WINDOW_END_POS),
	popup_window(this, POPUP_WINDOW_POS, POPUP_WINDOW_END_POS),
	yes_no_window(this, YES_NO_WINDOW_POS, YES_NO_WINDOW_END_POS),

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

	yes_no_menu
		= Menu
		(
			"yes",
			yes_no_window.size_2d(),
			Menu::NodeMap
			({
				{
					Menu::START_NODE_KEY,
					Menu::Node
					(
						Menu::START_NODE_KEY,		// text
						Menu::Node::Kind::Start,	// kind
						0x0,						// flags
						"", "yes",					// where
						std::monostate(),			// data
						0x0,						// variable
						nullptr						// on_update_func
					)
				},
				{
					"yes",
					Menu::Node
					(
						"Yes",							// text
						Menu::Node::Kind::ActionButton, // kind
						0x0,							// flags
						Menu::START_NODE_KEY, "no",		// where
						std::function<void()>			// data
							(Menu::ActionButtonFunctor<Engine>
								(this, 
								&Engine::_yes_no_menu_act_yes)),
						0x0,							// variable
						nullptr							// on_update_func
					)
				},
				{
					"no",
					Menu::Node
					(
						"No",							// text
						Menu::Node::Kind::ActionButton, // kind
						0x0,							// flags
						"yes", Menu::END_NODE_KEY,		// where
						std::function<void()>			// data
							(Menu::ActionButtonFunctor<Engine>
								(this, 
								&Engine::_yes_no_menu_act_no)),
						0x0,							// variable
						nullptr							// on_update_func
					)
				},
				{
					Menu::END_NODE_KEY,
					Menu::Node
					(
						Menu::END_NODE_KEY,		// text
						Menu::Node::Kind::End,	// kind
						0x0,					// flags
						"no", "",				// where
						std::monostate(),		// data
						0x0,					// variable
						nullptr					// on_update_func
					)
				},
			}),
			Vec2(true, true)
		);

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
	//printout("Ticking the game engine: ", _tick_counter, "\n");
	//++_tick_counter;

	//if (key_status.has_changed())
	//{
	//	printout("game_engine::Engine::tick(): key_status.has_changed()",
	//		" true.\n");
	//}

	//if (key_status.key_went_down_just_now(KeyStatus::UpL)
	//	&& (!key_status.at(KeyStatus::DownL)()))
	//{
	//	////printout("Engine::tick(): key_went_down_now(): up\n");
	//	//if (yes_no_menu.sel_key() == "no")
	//	//{
	//	//	yes_no_menu.set_sel_key("yes");
	//	//}
	//}
	//else if (key_status.key_went_down_just_now(KeyStatus::DownL)
	//	&& (!key_status.at(KeyStatus::UpL)()))
	//{
	//	////printout("Engine::tick(): key_went_down_now(): down\n");
	//	//if (yes_no_menu.sel_key() == "yes")
	//	//{
	//	//	yes_no_menu.set_sel_key("no");
	//	//}
	//}

	//switch (game_mode)
	//{
	////--------
	//case GameMode::AuxTitleScreen:
	//	break;
	//case GameMode::AuxGameOptions:
	//	break;
	//case GameMode::AuxCredits:
	//	break;

	//case GameMode::MainInGame:
	//	break;

	////case GameMode::PopupShop:
	////	break;

	////case GameMode::YesNoShop:
	////	break;

	//default:
	//	break;
	////--------
	//}
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

void Engine::_yes_no_menu_act_yes(Engine* self)
{
	printout("yes_no_menu: \"Yes\" button activated!\n");
}
void Engine::_yes_no_menu_act_no(Engine* self)
{
	printout("yes_no_menu: \"No\" button activated!\n");
}

Engine* engine = nullptr;
//--------
} // namespace game_engine
} // namespace dungwich_sandeon
