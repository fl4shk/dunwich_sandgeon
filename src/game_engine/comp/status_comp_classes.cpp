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

#include "status_comp_classes.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace comp
{

const std::string StatusOnFire::KIND_STR("StatusOnFire");
StatusOnFire::StatusOnFire(const Json::Value& jv)
{
	//timer = val_from_jv<decltype(timer)>(jv["timer"]);
	MEMB_LIST_COMP_STATUS_ON_FIRE(MEMB_DESERIALIZE);
}
std::string StatusOnFire::kind_str() const
{
	return KIND_STR;
}
StatusOnFire::operator Json::Value () const
{
	Json::Value ret;

	//ret["timer"] = timer;
	MEMB_LIST_COMP_STATUS_ON_FIRE(MEMB_SERIALIZE);

	return ret;
}

const std::string StatusPoisoned::KIND_STR("StatusPoisoned");
StatusPoisoned::StatusPoisoned(const Json::Value& jv)
{
	//timer = val_from_jv<decltype(timer)>(jv["timer"]);
	MEMB_LIST_COMP_STATUS_POISONED(MEMB_DESERIALIZE);
}
std::string StatusPoisoned::kind_str() const
{
	return KIND_STR;
}
StatusPoisoned::operator Json::Value () const
{
	Json::Value ret;

	//ret["timer"] = timer;
	MEMB_LIST_COMP_STATUS_POISONED(MEMB_SERIALIZE);

	return ret;
}

const std::string StatusAsleep::KIND_STR("StatusAsleep");
StatusAsleep::StatusAsleep(const Json::Value& jv)
{
	//timer = val_from_jv<decltype(timer)>(jv["timer"]);
	MEMB_LIST_COMP_STATUS_ASLEEP(MEMB_DESERIALIZE);
}
std::string StatusAsleep::kind_str() const
{
	return KIND_STR;
}
StatusAsleep::operator Json::Value () const
{
	Json::Value ret;

	//ret["timer"] = timer;
	MEMB_LIST_COMP_STATUS_ASLEEP(MEMB_SERIALIZE);

	return ret;
}

const std::string StatusTravelSpeed::KIND_STR("StatusTravelSpeed");
StatusTravelSpeed::StatusTravelSpeed(const Json::Value& jv)
{
	//timer = val_from_jv<decltype(timer)>(jv["timer"]);
	//val = val_from_jv<decltype(val)>(jv["val"]);
	MEMB_LIST_COMP_STATUS_TRAVEL_SPEED(MEMB_DESERIALIZE);
}
std::string StatusTravelSpeed::kind_str() const
{
	return KIND_STR;
}
StatusTravelSpeed::operator Json::Value () const
{
	Json::Value ret;

	//ret["timer"] = timer;
	//ret["val"] = val;
	MEMB_LIST_COMP_STATUS_TRAVEL_SPEED(MEMB_SERIALIZE);

	return ret;
}

const std::string StatusActionSpeed::KIND_STR("StatusActionSpeed");
StatusActionSpeed::StatusActionSpeed(const Json::Value& jv)
{
	//timer = val_from_jv<decltype(timer)>(jv["timer"]);
	//val = val_from_jv<decltype(val)>(jv["val"]);
	MEMB_LIST_COMP_STATUS_ACTION_SPEED(MEMB_DESERIALIZE);
}
std::string StatusActionSpeed::kind_str() const
{
	return KIND_STR;
}
StatusActionSpeed::operator Json::Value () const
{
	Json::Value ret;

	//ret["timer"] = timer;
	//ret["val"] = val;
	MEMB_LIST_COMP_STATUS_ACTION_SPEED(MEMB_SERIALIZE);

	return ret;
}

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon
