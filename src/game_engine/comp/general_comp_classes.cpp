// This file is part of Dunwich Sandgeon.
// 
// Copyright 2023 FL4SHK
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
	PfieldLayerPrio s_priority//, EntKind s_ent_kind
)
	//: _ent_id(s_ent_id), _pos(s_pos), priority(s_priority)
	{
	//engine->position_ctor_callback(this);
	_init(s_ent_id, s_pos, s_priority//, s_ent_kind
		);
}
Position::Position(
	ecs::EntId s_ent_id, const IntVec2& s_pos2,
	PfieldLayerPrio s_priority//, EntKind s_ent_kind
) {
	_init(s_ent_id, engine->to_pos3_cf(s_pos2), s_priority
		//, s_ent_kind
	);
}
void Position::_init(
	ecs::EntId s_ent_id, const IntVec3& s_pos,
	PfieldLayerPrio s_priority//, EntKind s_ent_kind
) {
	_ent_id = s_ent_id;
	//_pos = s_pos;
	_pos3() = s_pos;
	_pos3.back_up();
	_prev_floor = prev_pos3().z;
	//_pos2() = engine->to_pos2(s_pos);
	//_pos2.back_up();
	//_floor() = s_pos.z;
	//_floor.back_up();
	priority = s_priority;
	//_ent_kind = s_ent_kind;
	engine->position_ctor_callback(this);
}
Position::Position(const binser::Value& bv) {
	MEMB_AUTOSER_LIST_COMP_POSITION(BINSER_MEMB_DESERIALIZE);
	//priority = static_cast<PfieldLayerPrio>(
	//	get_bv_memb<i32>(bv, "priority")
	//);

	//priority = static_cast<PfieldLayerPrio>(val_from_jv<i32>(
	//	bv["priority"]
	//));

	binser::get_bv_memb_w_stat_cast<i32>
		(priority, bv, "priority", std::nullopt);

	engine->position_ctor_callback(this);
}
Position::~Position() {
	engine->position_dtor_callback(this);
}
void Position::set_pos3(const IntVec3& n_pos3) {
	engine->position_set_pos3_callback(this, n_pos3);
}
void Position::set_pos2(const IntVec2& n_pos2) {
	set_pos3({.x=n_pos2.x, .y=n_pos2.y, .z=floor()});
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
