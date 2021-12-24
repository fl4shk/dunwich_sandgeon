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

#include "window_size_2d_constants.hpp"
#include "menu_etc_classes.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{

const SizeVec2
	WITH_BORDER_SCREEN_SIZE_2D(82, 62),

	SCREEN_SIZE_2D
		(WITH_BORDER_SCREEN_SIZE_2D - SizeVec2(2, 2));

const PosVec2 
	PLAYFIELD_WINDOW_POS(0, 0),

	PLAYFIELD_WINDOW_END_POS
		(WITH_BORDER_SCREEN_SIZE_2D.x - 1 - 20,
		WITH_BORDER_SCREEN_SIZE_2D.y - 1 - 10);

const SizeVec2
	PLAYFIELD_WINDOW_SIZE_2D
		(PLAYFIELD_WINDOW_END_POS.x
			- PLAYFIELD_WINDOW_POS.x + 1,
		PLAYFIELD_WINDOW_END_POS.y
			- PLAYFIELD_WINDOW_POS.y + 1);

const PosVec2 
	LOG_WINDOW_POS
		(0,
		PLAYFIELD_WINDOW_END_POS.y),

	LOG_WINDOW_END_POS
		(PLAYFIELD_WINDOW_END_POS.x,
		WITH_BORDER_SCREEN_SIZE_2D.y - 1),

	HUD_WINDOW_POS
		(PLAYFIELD_WINDOW_END_POS.x,
		PLAYFIELD_WINDOW_POS.y),

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
} // namespace dungwich_sandeon
