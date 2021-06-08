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

namespace engine
{

Window::Window(EntMap&& s_ent_map, SystemMap&& s_sys_map)
	: _ent_map(std::move(s_ent_map)), _sys_map(std::move(s_sys_map))
{
}

//void Window::add_comp_to_ent(const Vec2<int>& ent_index,
//	const std::string& key)
//{
//}
//void Window::add_sys_to_ent(const Vec2<int>& ent_index,
//	const std::string& key)
//{
//}
//bool Window::add_comp_to_comp_map(const std::string& key,
//	Component&& to_add)
//{
//}
//bool Window::add_sys_to_sys_map(const std::string& key, System&& to_add)
//{
//}

} // namespace engine

} // namespace dungwich_sandeon
