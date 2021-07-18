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

#include "block_comp_classes.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace comp
{

std::string Wall::kind_str() const
{
	return "Wall";
}

std::string Floor::kind_str() const
{
	return "Floor";
}

std::string DownStairs::kind_str() const
{
	return "DownStairs";
}

std::string UpStairs::kind_str() const
{
	return "UpStairs";
}

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon
