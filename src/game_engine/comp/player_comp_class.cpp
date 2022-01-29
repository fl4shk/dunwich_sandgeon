// This file is part of Dungwich Sandeon.
// 
// Copyright 2022 FL4SHK
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

#include "player_comp_class.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace comp
{

const std::string Player::KIND_STR("Player");
Player::Player(const Json::Value& jv)
{
	MEMB_LIST_COMP_PLAYER(MEMB_DESERIALIZE);
}
std::string Player::kind_str() const
{
	return KIND_STR;
}
Player::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_PLAYER(MEMB_SERIALIZE);

	return ret;
}

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon
