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

const PosVec2 Engine::PLAYFIELD_POS(0, 0);
const SizeVec2 Engine::PLAYFIELD_SIZE_2D(60, 50);

Engine::Engine()
	: _screen(PosVec2(), Window::SCREEN_SIZE_2D),
	_playfield(PLAYFIELD_POS, PLAYFIELD_SIZE_2D)
{
}
Engine::~Engine()
{
}

void Engine::position_ctor_callback(comp::Position* self)
{
}
void Engine::position_dtor_callback(comp::Position* self)
{
}

} // namespace game_engine

} // namespace dungwich_sandeon
