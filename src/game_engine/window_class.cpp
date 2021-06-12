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

#include "window_class.hpp"

namespace dungwich_sandeon
{

namespace game_engine
{

Window::Window()
{
}
Window::Window(const PosVec2& s_pos, const Vec2<size_t>& s_size_2d)
	: _active(false), _pos(s_pos), 
	_ent_id_vec_2d(s_size_2d.y,
		ecs::EntIdVec(s_size_2d.x, ecs::ENT_NULL_ID))
{
}
Window::~Window()
{
}

} // namespace game_engine

} // namespace dungwich_sandeon
