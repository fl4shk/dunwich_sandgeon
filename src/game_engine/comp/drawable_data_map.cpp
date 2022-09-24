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

#include "drawable_data_map.hpp"
#include "../window_class.hpp"
#include "player_comp_class.hpp"
//#include "block_comp_classes.hpp"
#include "floor_layout_comp_classes.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace comp
{

static constexpr FgBgColorPair
	WINDOW_BORDER_COLOR_PAIR = FontColor::Green;

const std::unordered_map<std::string, Drawable::Data>& drawable_data_map()
{
	static std::unordered_map<std::string, Drawable::Data>
		DRAWABLE_DATA_MAP
	= {
		// ' ', 32
		{Window::BLANK_KIND_STR,
			{.c=' ', .color_pair=FontColor::Black,
			.gs_color_pair=FontColor::Black}},

		// '#', 35
		{bg_tile_str_map().at(BgTile::Wall),
			{.c='#',
			//.color_pair=FontColor::LightGray,
			//.gs_color_pair=FontColor::LightGray
			.color_pair=FontColor::Brown,
			.gs_color_pair=FontColor::Gray}},

		// '+', 43
		{Window::BORDER_CORNER_KIND_STR,
			{.c='+', .color_pair=WINDOW_BORDER_COLOR_PAIR,
			.gs_color_pair=FontColor::White}},

		// '-', 45
		{Window::BORDER_HORIZ_KIND_STR,
			{.c='-', .color_pair=WINDOW_BORDER_COLOR_PAIR,
			.gs_color_pair=FontColor::White}},

		// '.', 46
		{bg_tile_str_map().at(BgTile::Floor),
			{.c='.',
			//.color_pair=FontColor::LightGray,
			//.gs_color_pair=FontColor::LightGray
			.color_pair=FontColor::Gray,
			.gs_color_pair=FontColor::Gray}},

		// '<', 60
		{bg_tile_str_map().at(BgTile::DownStairs),
			{.c='<', .color_pair=FontColor::Brown,
			.gs_color_pair=FontColor::White}},

		// '>', 62
		{bg_tile_str_map().at(BgTile::UpStairs),
			{.c='>', .color_pair=FontColor::Brown,
			.gs_color_pair=FontColor::White}},

		// '@', 64
		{Player::KIND_STR,
			{.c='@', .color_pair=FontColor::White,
			.gs_color_pair=FontColor::White}},

		// '^', 94,
		{bg_tile_str_map().at(BgTile::Spikes),
			{.c='^', .color_pair=FontColor::Gray,
			.gs_color_pair=FontColor::Gray}},

		// '|', 124
		{Window::BORDER_VERT_KIND_STR,
			{.c='|', .color_pair=WINDOW_BORDER_COLOR_PAIR,
			.gs_color_pair=FontColor::White}},

		// '~', 126
		{bg_tile_str_map().at(BgTile::Water),
			{.c='~', .color_pair=FontColor::Blue,
			.gs_color_pair=FontColor::White}},
	};

	return DRAWABLE_DATA_MAP;
}

} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon
