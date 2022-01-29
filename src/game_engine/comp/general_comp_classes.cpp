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

#include "general_comp_classes.hpp"
#include "../engine_class.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace comp
{

Drawable::Data::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_DRAWABLE_DATA(MEMB_SERIALIZE);

	return ret;
}

const std::string Drawable::KIND_STR("Drawable");
Drawable::Drawable(const Json::Value& jv)
{
	MEMB_LIST_COMP_DRAWABLE(MEMB_DESERIALIZE);
}
std::string Drawable::kind_str() const
{
	return KIND_STR;
}
Drawable::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_DRAWABLE(MEMB_SERIALIZE);

	return ret;
}

const std::string Position::KIND_STR("Position");
Position::Position(ecs::EntId s_ent_id, const PosVec3& s_pos,
	PlayfieldLayerPrio s_priority)
	: _ent_id(s_ent_id), _pos(s_pos), priority(s_priority)
{
	engine->position_ctor_callback(this);
}
Position::Position(const Json::Value& jv)
{
	MEMB_AUTOSER_LIST_COMP_POSITION(MEMB_DESERIALIZE);
	priority = static_cast<PlayfieldLayerPrio>
		(get_jv_memb<uint>(jv, "priority"));

	engine->position_ctor_callback(this);
}
Position::~Position()
{
	engine->position_dtor_callback(this);
}
void Position::set_pos(const PosVec3& n_pos)
{
	engine->position_set_pos_callback(this, n_pos);
}
std::string Position::kind_str() const
{
	return KIND_STR;
}
Position::operator Json::Value () const
{
	Json::Value ret;

	MEMB_AUTOSER_LIST_COMP_POSITION(MEMB_SERIALIZE);
	ret["priority"] = static_cast<uint>(priority);

	return ret;
}

//const std::string Weight::KIND_STR("Weight");
//Weight::Weight(const Json::Value& jv)
//{
//	val = val_from_jv<decltype(val)>(jv["val"]);
//}
//std::string Weight::kind_str() const
//{
//	return KIND_STR;
//}
//Weight::operator Json::Value () const
//{
//	Json::Value ret;
//
//	ret["val"] = val;
//
//	return ret;
//}

const std::string BaseStats::KIND_STR("BaseStats");
BaseStats::BaseStats(const Json::Value& jv)
{
	MEMB_LIST_COMP_BASE_STATS(MEMB_DESERIALIZE);
}
std::string BaseStats::kind_str() const
{
	return KIND_STR;
}
BaseStats::operator Json::Value () const
{
	Json::Value ret;

	MEMB_LIST_COMP_BASE_STATS(MEMB_SERIALIZE);

	return ret;
}

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon
