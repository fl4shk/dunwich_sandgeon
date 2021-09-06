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

const std::string Drawable::KIND_STR("Drawable");
std::string Drawable::kind_str() const
{
	return KIND_STR;
}

const std::string Position::KIND_STR("Position");
Position::Position(ecs::EntId s_ent_id, const PosVec3& s_pos,
	PlayfieldLayerPrio s_priority)
	: _ent_id(s_ent_id), _pos(s_pos), priority(s_priority)
{
	engine.position_ctor_callback(this);
}
Position::~Position()
{
	engine.position_dtor_callback(this);
}
void Position::set_pos(const PosVec3& n_pos)
{
	engine.position_set_pos_callback(this, n_pos);
}
std::string Position::kind_str() const
{
	return KIND_STR;
}

const std::string Weight::KIND_STR("Weight");
std::string Weight::kind_str() const
{
	return KIND_STR;
}

const std::string BaseStats::KIND_STR("BaseStats");
std::string BaseStats::kind_str() const
{
	return KIND_STR;
}

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon
