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

namespace dungwich_sandeon
{

namespace engine
{

class Entity
{
public:		// types
	using KeySet = std::set<std::string>;
protected:		// variables
	// `Component` KeySet, `System` KeySet
	KeySet _comp_key_set, _sys_key_set;
public:		// functions
	Entity() = default;
	Entity(KeySet&& s_comp_key_set, KeySet&& s_sys_key_set);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Entity);
	virtual ~Entity() = default;

	GEN_GETTER_BY_CON_REF(comp_key_set);
	GEN_GETTER_BY_CON_REF(sys_key_set);
};

class Component
{
public:		// functions
	
};

class System
{
public:		// functions
	
};

using ComponentMap = std::map<std::string, Component>;
using SystemMap = std::map<std::string, Component>;

} // namespace engine

} // namespace dungwich_sandeon

#endif		// src_engine_entity_class_etc_hpp
