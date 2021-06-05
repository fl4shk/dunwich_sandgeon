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

#ifndef src_screen_class_hpp
#define src_screen_class_hpp

// src/screen_class.hpp

#include "../misc_includes.hpp"
#include "../sdl/text_handler_sdl_class.hpp"

namespace dungwich_sandeon
{

namespace engine
{

class Screen final
{
public:		// constants
	// These constants have values in amount of tilemap entries
	static const Vec2<int> SIZE_2D, PLAYFIELD_POS, PLAYFIELD_SIZE_2D;
private:		// variables
public:		// functions
	Screen() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Screen);
	~Screen() = default;
};

} // namespace engine

} // namespace dungwich_sandeon

#endif		// src_screen_class_hpp
