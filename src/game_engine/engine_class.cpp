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
		(Window::SCREEN_SIZE_2D.x - 20,
		Window::SCREEN_SIZE_2D.y - 10);

const SizeVec2
	Engine::PLAYFIELD_WINDOW_SIZE_2D
		(Engine::PLAYFIELD_WINDOW_END_POS.x
			- Engine::PLAYFIELD_WINDOW_POS.x + 1,
		Engine::PLAYFIELD_WINDOW_END_POS.y
			- Engine::PLAYFIELD_WINDOW_POS.y + 1);

const PosVec2 
	Engine::BOTTOM_MSG_WINDOW_POS
		(0,
		Engine::PLAYFIELD_WINDOW_END_POS.y + 2),

	Engine::BOTTOM_MSG_WINDOW_END_POS
		(Engine::PLAYFIELD_WINDOW_END_POS.x,
		Window::SCREEN_SIZE_2D.y),

	Engine::RIGHT_MSG_WINDOW_POS
		(Engine::PLAYFIELD_WINDOW_END_POS.x + 2,
		Engine::PLAYFIELD_WINDOW_POS.y),

	Engine::RIGHT_MSG_WINDOW_END_POS
		(Window::SCREEN_SIZE_2D.x,
		Window::SCREEN_SIZE_2D.y),

	Engine::POPUP_WINDOW_POS(20, 20),

	Engine::POPUP_WINDOW_END_POS
		(Window::SCREEN_SIZE_2D.x - 20,
		Window::SCREEN_SIZE_2D.y - 20);

Engine::Engine()
	: screen_window(PosVec2(), Window::SCREEN_SIZE_2D),
	title_screen_window(PosVec2(), Window::SCREEN_SIZE_2D),
	playfield_window(PLAYFIELD_WINDOW_POS, PLAYFIELD_WINDOW_END_POS),
	bottom_msg_window(BOTTOM_MSG_WINDOW_POS, BOTTOM_MSG_WINDOW_END_POS),
	right_msg_window(RIGHT_MSG_WINDOW_POS, RIGHT_MSG_WINDOW_END_POS),
	popup_window(POPUP_WINDOW_POS, POPUP_WINDOW_END_POS),

	_playfield_ent_id_v3d(NUM_FLOORS,
		EntIdSetVec2d(PLAYFIELD_WINDOW_SIZE_2D.y,
			std::vector<std::set<ecs::EntId>>(PLAYFIELD_WINDOW_SIZE_2D.x)))
{
}
Engine::~Engine()
{
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

Engine engine;

} // namespace game_engine
} // namespace dungwich_sandeon
