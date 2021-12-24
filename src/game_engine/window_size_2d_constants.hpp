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

#ifndef src_game_engine_window_size_2d_constants_hpp
#define src_game_engine_window_size_2d_constants_hpp

// src/game_engine/window_size_2d_constants.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{

// This constant has values in the amount of tilemap entries
extern const SizeVec2
	WITH_BORDER_SCREEN_SIZE_2D,
	SCREEN_SIZE_2D;
extern const PosVec2
	PLAYFIELD_WINDOW_POS, PLAYFIELD_WINDOW_END_POS;
extern const SizeVec2
	PLAYFIELD_WINDOW_SIZE_2D;

extern const PosVec2
	LOG_WINDOW_POS, LOG_WINDOW_END_POS,
	HUD_WINDOW_POS, HUD_WINDOW_END_POS,
	POPUP_WINDOW_POS, POPUP_WINDOW_END_POS,
	YES_NO_WINDOW_POS, YES_NO_WINDOW_END_POS,
	TEXT_YES_NO_WINDOW_POS, TEXT_YES_NO_WINDOW_END_POS;

} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_window_size_2d_constants_hpp
