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
	{Player::KIND_STR, {'@', FontColor::White, FontColor::White}},

	{Wall::KIND_STR, {'#', FontColor::LightGray, FontColor::LightGray}},
	{Floor::KIND_STR, {'.', FontColor::LightGray, FontColor::LightGray}},
	{DownStairs::KIND_STR, {'s', FontColor::White, FontColor::White}},
	{UpStairs::KIND_STR, {'S', FontColor::White, FontColor::White}},
};

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon
