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

#include "window_size_2d_constants.hpp"
#include "menu_etc_classes.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
//--------
const SizeVec2
	WITH_BORDER_SCREEN_SIZE_2D(82, 62),

	SCREEN_SIZE_2D
		(WITH_BORDER_SCREEN_SIZE_2D - SizeVec2(2, 2));
//--------
const PosVec2 
	PFIELD_WINDOW_POS(0, 0),

	PFIELD_WINDOW_END_POS
		(WITH_BORDER_SCREEN_SIZE_2D.x - 1 - 20,
		WITH_BORDER_SCREEN_SIZE_2D.y - 1 - 10);
const PosVec2Ex
	PFIELD_WINDOW_EX_RANGE
	= {
		.data=PosVec2(),
		.max=PFIELD_WINDOW_END_POS,
		.min=PFIELD_WINDOW_POS
	};

const SizeVec2
	PFIELD_WINDOW_SIZE_2D
		(PFIELD_WINDOW_END_POS.x
			- PFIELD_WINDOW_POS.x + 1,
		PFIELD_WINDOW_END_POS.y
			- PFIELD_WINDOW_POS.y + 1);

const PosVec2 
	LOG_WINDOW_POS
		(0,
		PFIELD_WINDOW_END_POS.y),

	LOG_WINDOW_END_POS
		(PFIELD_WINDOW_END_POS.x,
		WITH_BORDER_SCREEN_SIZE_2D.y - 1),

	HUD_WINDOW_POS
		(PFIELD_WINDOW_END_POS.x,
		PFIELD_WINDOW_POS.y),

	HUD_WINDOW_END_POS
		(WITH_BORDER_SCREEN_SIZE_2D.x - 1,
		WITH_BORDER_SCREEN_SIZE_2D.y - 1),

	POPUP_WINDOW_POS
		(13,
		10),

	POPUP_WINDOW_END_POS
		(HUD_WINDOW_POS.x - 1,
		WITH_BORDER_SCREEN_SIZE_2D.y - 15),

	YES_NO_WINDOW_POS
		(2,
		WITH_BORDER_SCREEN_SIZE_2D.y / 2),

	YES_NO_WINDOW_END_POS
		(YES_NO_WINDOW_POS.x + 3
		+ MsgLog::WIDGET_SELECTED_SPACING_SIZE + Menu::WIDGET_SPACING_SIZE
		+ 1,
		YES_NO_WINDOW_POS.y + 2 + 1 + 2),

	TEXT_YES_NO_WINDOW_POS
		(2,
		WITH_BORDER_SCREEN_SIZE_2D.y / 2),

	TEXT_YES_NO_WINDOW_END_POS
		(TEXT_YES_NO_WINDOW_POS.x + 30 + 1 + 2,
		TEXT_YES_NO_WINDOW_POS.y + 4 + 1 + 2);

} // namespace game_engine
} // namespace dunwich_sandgeon
