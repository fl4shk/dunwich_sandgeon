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

#include "status_comp_classes.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace comp
{

const std::string StatusOnFire::KIND_STR("StatusOnFire");
StatusOnFire::StatusOnFire(const Json::Value& jv)
{
	MEMB_LIST_COMP_STATUS_ON_FIRE(JSON_MEMB_DESERIALIZE);
}
std::string StatusOnFire::kind_str() const
{
	return KIND_STR;
}
StatusOnFire::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_STATUS_ON_FIRE(JSON_MEMB_SERIALIZE);

	return ret;
}

const std::string StatusPoisoned::KIND_STR("StatusPoisoned");
StatusPoisoned::StatusPoisoned(const Json::Value& jv)
{
	MEMB_LIST_COMP_STATUS_POISONED(JSON_MEMB_DESERIALIZE);
}
std::string StatusPoisoned::kind_str() const
{
	return KIND_STR;
}
StatusPoisoned::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_STATUS_POISONED(JSON_MEMB_SERIALIZE);

	return ret;
}

const std::string StatusAsleep::KIND_STR("StatusAsleep");
StatusAsleep::StatusAsleep(const Json::Value& jv)
{
	MEMB_LIST_COMP_STATUS_ASLEEP(JSON_MEMB_DESERIALIZE);
}
std::string StatusAsleep::kind_str() const
{
	return KIND_STR;
}
StatusAsleep::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_STATUS_ASLEEP(JSON_MEMB_SERIALIZE);

	return ret;
}

const std::string StatusTravelSpeed::KIND_STR("StatusTravelSpeed");
StatusTravelSpeed::StatusTravelSpeed(const Json::Value& jv)
{
	MEMB_LIST_COMP_STATUS_TRAVEL_SPEED(JSON_MEMB_DESERIALIZE);
}
std::string StatusTravelSpeed::kind_str() const
{
	return KIND_STR;
}
StatusTravelSpeed::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_STATUS_TRAVEL_SPEED(JSON_MEMB_SERIALIZE);

	return ret;
}

const std::string StatusActionSpeed::KIND_STR("StatusActionSpeed");
StatusActionSpeed::StatusActionSpeed(const Json::Value& jv)
{
	MEMB_LIST_COMP_STATUS_ACTION_SPEED(JSON_MEMB_DESERIALIZE);
}
std::string StatusActionSpeed::kind_str() const
{
	return KIND_STR;
}
StatusActionSpeed::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_STATUS_ACTION_SPEED(JSON_MEMB_SERIALIZE);

	return ret;
}

} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon
