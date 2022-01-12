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

	ret["c"] = c;
	ret["color_pair"] = color_pair;
	ret["gs_color_pair"] = gs_color_pair;

	return ret;
}

const std::string Drawable::KIND_STR("Drawable");
Drawable::Drawable(const Json::Value& jv)
{
	_data = Data::from_jv(jv["_data"]);
	_non_blink_color_pair = val_from_jv<decltype(_non_blink_color_pair)>
		(jv["_non_blink_color_pair"]);
	_non_blink_gs_color_pair
		= val_from_jv<decltype(_non_blink_gs_color_pair)>
			(jv["_non_blink_color_pair"]);
	_in_blink = val_from_jv<decltype(_in_blink)>(jv["_in_blink"]);
}
std::string Drawable::kind_str() const
{
	return KIND_STR;
}
Drawable::operator Json::Value () const
{
	Json::Value ret;

	ret["_data"] = _data;
	ret["_non_blink_color_pair"] = _non_blink_color_pair;
	ret["_non_blink_gs_color_pair"] = _non_blink_gs_color_pair;
	ret["_in_blink"] = _in_blink;

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
	_ent_id 
		= (static_cast<u64>(jv["_ent_id.high"].asUInt()) << 32u)
		| static_cast<u64>(jv["_ent_id.low"].asUInt());
	_pos = vec3_from_jv<decltype(_pos.x)>(jv["_pos"]);

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

	ret["_ent_id.high"] = static_cast<u32>(_ent_id >> 32u);
	ret["_ent_id.low"] = static_cast<u32>(_ent_id
		& static_cast<u32>(0xffffffff));
	ret["_pos"] = vec3_to_jv(_pos);

	return ret;
}

const std::string Weight::KIND_STR("Weight");
Weight::Weight(const Json::Value& jv)
{
	val = val_from_jv<decltype(val)>(jv["val"]);
}
std::string Weight::kind_str() const
{
	return KIND_STR;
}
Weight::operator Json::Value () const
{
	Json::Value ret;

	ret["val"] = val;

	return ret;
}

const std::string BaseStats::KIND_STR("BaseStats");
BaseStats::BaseStats(const Json::Value& jv)
{
	hp = val_from_jv<decltype(hp)>(jv["hp"]);
	atk = val_from_jv<decltype(atk)>(jv["atk"]);
	def = val_from_jv<decltype(def)>(jv["def"]);
	mag_atk = val_from_jv<decltype(mag_atk)>(jv["mag_atk"]);
	mag_def = val_from_jv<decltype(mag_def)>(jv["mag_def"]);
}
std::string BaseStats::kind_str() const
{
	return KIND_STR;
}
BaseStats::operator Json::Value () const
{
	Json::Value ret;

	ret["hp"] = hp;
	ret["atk"] = atk;
	ret["def"] = def;
	ret["mag_atk"] = mag_atk;
	ret["mag_def"] = mag_def;

	return ret;
}

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon
