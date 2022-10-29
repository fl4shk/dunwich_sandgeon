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

#include "general_comp_classes.hpp"
#include "../engine_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace comp {
//--------
Drawable::Data Drawable::Data::from_bv(const binser::Value& bv) {
	Data ret;

	MEMB_LIST_COMP_DRAWABLE_DATA(BINSER_MEMB_FROM_BV_DESERIALIZE);

	return ret;
}
Drawable::Data::operator binser::Value () const {
	binser::Value ret;

	MEMB_LIST_COMP_DRAWABLE_DATA(BINSER_MEMB_SERIALIZE);

	return ret;
}

const std::string Drawable::KIND_STR("Drawable");
Drawable::Drawable(const binser::Value& bv) {
	MEMB_LIST_COMP_DRAWABLE(BINSER_MEMB_DESERIALIZE);
}
std::string Drawable::kind_str() const {
	return KIND_STR;
}
Drawable::operator binser::Value () const {
	binser::Value ret;

	MEMB_LIST_COMP_DRAWABLE(BINSER_MEMB_SERIALIZE);

	return ret;
}

const std::string Position::KIND_STR("Position");
Position::Position(
	ecs::EntId s_ent_id, const IntVec3& s_pos,
	PlayfieldLayerPrio s_priority
)
	//: _ent_id(s_ent_id), _pos(s_pos), priority(s_priority)
	{
	//engine->position_ctor_callback(this);
	_init(s_ent_id, s_pos, s_priority);
}
Position::Position(
	ecs::EntId s_ent_id, const IntVec2& s_pos_on_curr_floor,
	PlayfieldLayerPrio s_priority
) {
	_init(s_ent_id, engine->to_pos_3d(s_pos_on_curr_floor), s_priority);
}
void Position::_init(
	ecs::EntId s_ent_id, const IntVec3& s_pos,
	PlayfieldLayerPrio s_priority
) {
	_ent_id = s_ent_id;
	//_pos = s_pos;
	_pos.back_up_and_update(s_pos);
	priority = s_priority;
	engine->position_ctor_callback(this);
}
Position::Position(const binser::Value& bv) {
	MEMB_AUTOSER_LIST_COMP_POSITION(BINSER_MEMB_DESERIALIZE);
	//priority = static_cast<PlayfieldLayerPrio>(
	//	get_bv_memb<i32>(bv, "priority")
	//);

	//priority = static_cast<PlayfieldLayerPrio>(val_from_jv<i32>(
	//	bv["priority"]
	//));

	binser::get_bv_memb_w_stat_cast<i32>
		(priority, bv, "priority", std::nullopt);

	engine->position_ctor_callback(this);
}
Position::~Position() {
	engine->position_dtor_callback(this);
}
IntVec3& Position::set_pos(const IntVec3& n_pos) {
	return engine->position_set_pos_callback(this, n_pos);
}
IntVec3& Position::set_pos(const IntVec2& n_pos_on_curr_floor) {
	return set_pos(engine->to_pos_3d(n_pos_on_curr_floor));
}
std::string Position::kind_str() const {
	return KIND_STR;
}
Position::operator binser::Value () const {
	binser::Value ret;

	MEMB_AUTOSER_LIST_COMP_POSITION(BINSER_MEMB_SERIALIZE);
	//ret["priority"] = static_cast<i32>(priority);
	ret.insert("priority", static_cast<i32>(priority));

	return ret;
}

//const std::string Weight::KIND_STR("Weight");
//Weight::Weight(const binser::Value& bv) {
//	val = val_from_jv<decltype(val)>(bv["val"]);
//}
//std::string Weight::kind_str() const {
//	return KIND_STR;
//}
//Weight::operator binser::Value () const {
//	binser::Value ret;
//
//	ret["val"] = val;
//
//	return ret;
//}

const std::string BaseStats::KIND_STR("BaseStats");
BaseStats::BaseStats(const binser::Value& bv) {
	MEMB_LIST_COMP_BASE_STATS(BINSER_MEMB_DESERIALIZE);
}
std::string BaseStats::kind_str() const {
	return KIND_STR;
}
BaseStats::operator binser::Value () const {
	binser::Value ret;

	MEMB_LIST_COMP_BASE_STATS(BINSER_MEMB_SERIALIZE);

	return ret;
}
//--------
} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon
