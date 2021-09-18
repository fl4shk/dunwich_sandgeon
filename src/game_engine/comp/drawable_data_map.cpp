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

#include "drawable_data_map.hpp"
#include "../basic_window_classes.hpp"
#include "player_comp_class.hpp"
#include "block_comp_classes.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace comp
{

const std::map<std::string, Drawable::Data> DRAWABLE_DATA_MAP
= {
	// ' ', 32
	{
		Window::BLANK_KIND_STR,
		{
			.c=' ',
			.color_pair=FontColor::LightGray,
			.gs_color_pair=FontColor::LightGray
		}
	},
	// '#', 35
	{
		Wall::KIND_STR,
		{
			.c='#',
			.color_pair=FontColor::LightGray,
			.gs_color_pair=FontColor::LightGray
		}
	},

	// '+', 43
	{
		Window::BORDER_CORNER_KIND_STR,
		{
			.c='+',
			.color_pair=FontColor::Green,
			.gs_color_pair=FontColor::White
		}
	},
	// '-', 45
	{
		Window::BORDER_HORIZ_KIND_STR,
		{
			.c='-',
			.color_pair=FontColor::Green,
			.gs_color_pair=FontColor::White
		}
	},

	// '.', 46
	{
		Floor::KIND_STR,
		{
			.c='.',
			.color_pair=FontColor::LightGray,
			.gs_color_pair=FontColor::LightGray
		}
	},

	// '@', 64
	{
		Player::KIND_STR,
		{
			.c='@',
			.color_pair=FontColor::White,
			.gs_color_pair=FontColor::White
		}
	},

	// 'S', 83
	{
		UpStairs::KIND_STR,
		{
			.c='S',
			.color_pair=FontColor::White,
			.gs_color_pair=FontColor::White
		}
	},

	// 's', 115
	{
		DownStairs::KIND_STR,
		{
			.c='s',
			.color_pair=FontColor::White,
			.gs_color_pair=FontColor::White
		}
	},

	// '|', 124
	{
		Window::BORDER_VERT_KIND_STR,
		{
			.c='|',
			.color_pair=FontColor::Green,
			.gs_color_pair=FontColor::White
		}
	},
};

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon
