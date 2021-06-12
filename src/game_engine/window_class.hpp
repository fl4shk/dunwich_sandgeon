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
	PosVec2 _pos;
	ecs::EntIdVec2d _ent_id_vec_2d;
public:		// functions
	Window();
	Window(const PosVec2& s_pos, const Vec2<size_t>& s_size_2d);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Window);
	virtual ~Window();

	inline auto& ent_id_at(const PosVec2& index)
	{
		return _ent_id_vec_2d.at(index.y).at(index.x);
	}
	inline const auto& ent_id_at(const PosVec2& index) const
	{
		return _ent_id_vec_2d.at(index.y).at(index.x);
	}

	GEN_GETTER_AND_SETTER_BY_VAL(active);
	GEN_GETTER_BY_CON_REF(pos);
	GEN_GETTER_BY_CON_REF(ent_id_vec_2d);
};

} // namespace game_engine

} // namespace dungwich_sandeon

#endif		// src_game_engine_window_class_hpp
