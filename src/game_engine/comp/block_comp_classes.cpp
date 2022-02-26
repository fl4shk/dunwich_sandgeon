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

#include "block_comp_classes.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace comp
{

//std::string InBetweenWalls::kind_str() const
//{
//	return "InBetweenWalls";
//}

const std::string Wall::KIND_STR("Wall");
Wall::Wall(const Json::Value& jv)
{
	MEMB_LIST_COMP_WALL(JSON_MEMB_DESERIALIZE);
}
std::string Wall::kind_str() const
{
	return KIND_STR;
}
Wall::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_WALL(JSON_MEMB_SERIALIZE);

	return ret;
}

const std::string Floor::KIND_STR("Floor");
Floor::Floor(const Json::Value& jv)
{
	MEMB_LIST_COMP_FLOOR(JSON_MEMB_DESERIALIZE);
}
std::string Floor::kind_str() const
{
	return KIND_STR;
}
Floor::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_FLOOR(JSON_MEMB_SERIALIZE);

	return ret;
}

const std::string DownStairs::KIND_STR("DownStairs");
DownStairs::DownStairs(const Json::Value& jv)
{
	MEMB_LIST_COMP_DOWN_STAIRS(JSON_MEMB_DESERIALIZE);
}
std::string DownStairs::kind_str() const
{
	return KIND_STR;
}
DownStairs::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_DOWN_STAIRS(JSON_MEMB_SERIALIZE);

	return ret;
}

const std::string UpStairs::KIND_STR("UpStairs");
UpStairs::UpStairs(const Json::Value& jv)
{
	MEMB_LIST_COMP_UP_STAIRS(JSON_MEMB_DESERIALIZE);
}
std::string UpStairs::kind_str() const
{
	return KIND_STR;
}
UpStairs::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_UP_STAIRS(JSON_MEMB_SERIALIZE);

	return ret;
}

} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon
