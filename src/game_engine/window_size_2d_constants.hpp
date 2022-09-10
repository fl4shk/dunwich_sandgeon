// This file is part of Dunwich Sandgeon.
// 
// Copyright 2022 FL4SHK
//
// Dunwich Sandgeon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// Dunwich Sandgeon is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Dunwich Sandgeon.  If not, see <https://www.gnu.org/licenses/>.

#ifndef src_game_engine_window_size_2d_constants_hpp
#define src_game_engine_window_size_2d_constants_hpp

// src/game_engine/window_size_2d_constants.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
//--------
// This constant has values in the amount of tilemap entries
extern const IntVec2
	WITH_BORDER_SCREEN_SIZE_2D,
	SCREEN_SIZE_2D;
//--------
extern const IntVec2
	PFIELD_WINDOW_POS, PFIELD_WINDOW_END_POS;
//extern const IntVec2Ex
//	PFIELD_WINDOW_EX_RANGE;
extern const IntVec2
	PFIELD_WINDOW_SIZE_2D;
//--------
extern const IntVec2
	LOG_WINDOW_POS, LOG_WINDOW_END_POS,
	HUD_WINDOW_POS, HUD_WINDOW_END_POS,
	POPUP_WINDOW_POS, POPUP_WINDOW_END_POS,
	YES_NO_WINDOW_POS, YES_NO_WINDOW_END_POS,
	TEXT_YES_NO_WINDOW_POS, TEXT_YES_NO_WINDOW_END_POS;
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_window_size_2d_constants_hpp
