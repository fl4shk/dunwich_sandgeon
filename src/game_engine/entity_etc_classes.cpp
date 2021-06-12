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

#include "entity_etc_classes.hpp"
#include "engine_class.hpp"

namespace dungwich_sandeon
{

namespace game_engine
{
//--------
void Entity::destroy() const
{
}

bool Entity::insert_comp(const std::string& key, ComponentUptr&& comp)
	const
{
	if (!comp_map().contains(key))
	{
		comp_map()[key] = std::move(comp);
		return false;
	}
	return true;
}
bool Entity::insert_or_replace_comp(const std::string& key,
	ComponentUptr&& comp) const
{
	comp_map()[key] = std::move(comp);
}
size_t Entity::erase_comp(const std::string& key) const
{
	return comp_map().erase(key);
}

EntityComponentMap& Entity::comp_map() const
{
	return _engine->comp_map(id());
}
const EntityComponentMap& comp_map() const
{
	return _engine->comp_map(id());
}
//--------
std::string Component::base_kind_str() const
{
	return "";
}
//--------
void System::tick(const std::vector<Entity*>& vec)
{
}
//--------
} // namespace game_engine

} // namespace dungwich_sandeon
