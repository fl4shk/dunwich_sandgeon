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

#ifndef src_engine_entity_class_etc_hpp
#define src_engine_entity_class_etc_hpp

// src/engine/entity_class_etc.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"

namespace dungwich_sandeon
{

namespace engine
{
//--------
class Window;
class System;

class Component
{
public:		// functions
	Component() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Component);
	virtual ~Component() = default;

	virtual std::string base_key() const;
};

class System
{
public:		// functions
	System() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(System);
	virtual ~System() = default;
};

using ComponentMap = std::map<std::string, std::unique_ptr<Component>>;
using SystemMap = std::map<std::string, std::unique_ptr<System>>;
//--------
class Entity
{
	friend class Window;
public:		// types
protected:		// variables
	i32 _id = 0;
	ComponentMap _comp_map;
	// Which `System`s affect this `Entity`?
	StrKeySet _sys_key_set;
public:		// functions
	Entity() = default;
	Entity(i32 s_id, ComponentMap&& s_comp_map, StrKeySet&& s_sys_key_set);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Entity);
	virtual ~Entity() = default;

	bool insert_comp(const std::string& key, Component* comp);
	bool insert_or_replace_comp(const std::string& key, Component* comp);
	size_t erase_comp(const std::string& key);
	bool insert_sys_key(const std::string& key);
	inline size_t erase_sys_key(const std::string& key);

	GEN_GETTER_AND_SETTER_BY_VAL(id);
	GEN_GETTER_BY_CON_REF(comp_map);
	GEN_GETTER_BY_CON_REF(sys_key_set);
};
//--------
} // namespace engine

} // namespace dungwich_sandeon

#endif		// src_engine_entity_class_etc_hpp
