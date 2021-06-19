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

#include "status_comp_classes.hpp"

namespace dungwich_sandeon
{

namespace game_engine
{

namespace comp
{

std::string StatusOnFire::kind_str() const
{
	return "StatusOnFire";
}

std::string StatusPoisoned::kind_str() const
{
	return "StatusPoisoned";
}

std::string StatusAsleep::kind_str() const
{
	return "StatusAsleep";
}

std::string StatusTravelSpeed::kind_str() const
{
	return "StatusTravelSpeed";
}

std::string StatusActionSpeed::kind_str() const
{
	return "StatusActionSpeed";
}

} // namespace comp

} // namespace game_engine

} // namespace dungwich_sandeon
