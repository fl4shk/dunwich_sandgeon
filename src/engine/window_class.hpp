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

#ifndef src_engine_window_class_hpp
#define src_engine_window_class_hpp

// src/engine/window_class.hpp

#include "../misc_includes.hpp"
#include "game_obj_class.hpp"

namespace dungwich_sandeon
{

namespace engine
{

// A window made out of tiles
class Window
{
public:		// types
	enum class Side
	{
		Left,
		Top,
		Right,
		Bottom,
	};
protected:		// variables
	std::map<Side, bool> _filled_side_map;
	std::vector<std::vector<GameObj>> _tilemap;
};

} // namespace engine

} // namespace dungwich_sandeon

#endif		// src_engine_window_class_hpp
