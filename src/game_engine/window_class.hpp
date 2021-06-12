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

#ifndef src_game_engine_window_class_hpp
#define src_game_engine_window_class_hpp

// src/game_engine/window_class.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"

namespace dungwich_sandeon
{

namespace game_engine
{

// A window made out of `Entity`s
class Window
{
protected:		// variables
	bool _active = false;
	ecs::EntIdMap _ent_id_map;
public:		// functions
	Window();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Window);
	virtual ~Window();

	inline auto& ent_id_at(const ecs::EntIdMapFullIndex& full_index)
	{
		return _ent_id_map.at(full_index.first).at(full_index.second.y)
			.at(full_index.second.x);
	}
	inline const auto& ent_id_at(const ecs::EntIdMapFullIndex& full_index)
		const
	{
		return _ent_id_map.at(full_index.first).at(full_index.second.y)
			.at(full_index.second.x);
	}

	GEN_GETTER_AND_SETTER_BY_VAL(active);
	GEN_GETTER_AND_SETTER_BY_CON_REF(ent_id_map);
	GEN_SETTER_BY_RVAL_REF(ent_id_map);
};

} // namespace game_engine

} // namespace dungwich_sandeon

#endif		// src_game_engine_window_class_hpp
