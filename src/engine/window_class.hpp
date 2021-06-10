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

#ifndef src_engine_window_class_hpp
#define src_engine_window_class_hpp

// src/engine/window_class.hpp

#include "../misc_includes.hpp"
#include "entity_etc_classes.hpp"

namespace dungwich_sandeon
{

namespace engine
{

// A window made out of `Entity`s
class Window
{
protected:		// variables
	bool _active = false;
	EntMap _ent_map;
	SystemMap _sys_map;
public:		// functions
	Window() = default;
	Window(EntMap&& s_ent_map, SystemMap&& s_sys_map);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Window);
	virtual ~Window() = default;

	inline Entity* ent_map_at(const std::string& key,
		const Vec2<int>& index)
	{
		return _ent_map.at(key).at(index.y).at(index.x);
	}
	//void add_comp_to_ent(const std::string& ent_key,
	//	const Vec2<int>& ent_map_index, const std::string& comp_key);
	//void add_sys_to_ent(const std::string& ent_key,
	//	const Vec2<int>& ent_map_index, const std::string& sys_key);
	//bool add_comp_to_comp_map(const std::string& key, Component&& to_add);
	//bool add_sys_to_sys_map(const std::string& key, System&& to_add);

	GEN_GETTER_AND_SETTER_BY_VAL(active);
	GEN_GETTER_AND_SETTER_BY_CON_REF(ent_map);
	GEN_SETTER_BY_RVAL_REF(ent_map);
	GEN_GETTER_AND_SETTER_BY_CON_REF(sys_map);
	GEN_SETTER_BY_RVAL_REF(sys_map);
};

} // namespace engine

} // namespace dungwich_sandeon

#endif		// src_engine_window_class_hpp
