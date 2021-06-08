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

#include "entity_class_etc.hpp"

namespace dungwich_sandeon
{

namespace engine
{
//--------
std::string Component::base_key() const
{
	return "";
}
//--------
bool Entity::insert_comp(const std::string& key, Component* comp)
{
	if (!_comp_map.contains(key))
	{
		_comp_map[key] = std::unique_ptr<Component>(comp);
		return false;
	}
	return true;
}
bool Entity::insert_or_replace_comp(const std::string& key,
	Component* comp)
{
	if (!_comp_map.contains(key))
	{
		_comp_map[key] = std::unique_ptr<Component>(comp);
		return false;
	}
	else // if (_comp_map.contains(key))
	{
		_comp_map[key].reset(comp);
		return true;
	}
}
size_t Entity::erase_comp(const std::string& key)
{
	return _comp_map.erase(key);
}
bool Entity::insert_sys_key(const std::string& key)
{
	if (!_sys_key_set.contains(key))
	{
		_sys_key_set.insert(key);

		return false;
	}
	return true;
}
size_t Entity::erase_sys_key(const std::string& key)
{
	return _sys_key_set.erase(key);
}
//--------
} // namespace engine

} // namespace dungwich_sandeon
