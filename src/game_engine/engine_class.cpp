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

namespace dungwich_sandeon
{
namespace game_engine
{

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
		(Engine::YES_NO_WINDOW_POS.x + 4 + Menu::WIDGET_SPACING_SIZE,
		Engine::YES_NO_WINDOW_POS.y + 4 + Menu::WIDGET_SPACING_SIZE);

Engine::Engine()
	: screen_window(this, PosVec2(), Window::WITH_BORDER_SCREEN_SIZE_2D),
	aux_window(this, PosVec2(), Window::WITH_BORDER_SCREEN_SIZE_2D),

	playfield_window(this, PLAYFIELD_WINDOW_POS, PLAYFIELD_WINDOW_END_POS),
	log_window(this, LOG_WINDOW_POS, LOG_WINDOW_END_POS),
	hud_window(this, HUD_WINDOW_POS, HUD_WINDOW_END_POS),
	popup_window(this, POPUP_WINDOW_POS, POPUP_WINDOW_END_POS),
	yes_no_window(this, YES_NO_WINDOW_POS, YES_NO_WINDOW_END_POS),

	_playfield_ent_id_v3d(NUM_FLOORS,
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
	printout("Ticking the game engine: ", _tick_counter, "\n");
	++_tick_counter;
}

void Engine::position_ctor_callback(comp::Position* obj)
{
	_err_when_ent_id_is_null(obj, "position_ctor_callback");

	auto& ent_id_set = _playfield_ent_id_v3d.at(obj->pos().z)
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

	auto& ent_id_set = _playfield_ent_id_v3d.at(obj->pos().z)
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

Engine* engine = nullptr;

} // namespace game_engine
} // namespace dungwich_sandeon
