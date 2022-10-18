// This file is part of Dunwich Sandgeon.
// 
// Copyright 2022 FL4SHK
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

#ifndef src_game_engine_metaball_gen_class_hpp
#define src_game_engine_metaball_gen_class_hpp

// src/game_engine/metaball_gen_class.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
class MetaballGen final {
public:		// types
	class Ball final {
	public:		// variables
		IntVec2 pos;
		FltVec2 size_2d;
	};
	using GenDynarr = std::vector<float>;
	using GenDyna2d = std::vector<GenDynarr>;
private:		// variables
	IntVec2 _size_2d;
	std::vector<Ball> _ball_vec;
public:		// functions
	MetaballGen(const IntVec2& s_size_2d);
	MetaballGen& add(const IntVec2& pos, float range);
	MetaballGen& add(const IntVec2& pos, const FltVec2& range);
	GenDyna2d gen();
};
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_metaball_gen_class_hpp
