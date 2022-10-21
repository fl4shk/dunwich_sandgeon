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

#ifndef src_game_engine_dijkstra_map_classes_hpp
#define src_game_engine_dijkstra_map_classes_hpp

// src/game_engine/dijkstra_map_classes.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"
#include "global_shape_constants_etc.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace level_gen_etc {
//--------
// See the below links for more information:
// http://www.roguebasin.com/index.php/The_Incredible_Power_of_Dijkstra_Maps
// http://www.roguebasin.com/index.php/Dijkstra_Maps_Visualized
class DijkstraMap final {
public:		// types
	using Data = std::vector<std::vector<float>>;
	class Goal final {
	public:		// variables
		IntVec2 pos;
		float val;
	};
private:		// variables
	Data _data;
};
class DijkstraMapGen final {
public:		// types
	//using Goal = std::pair<IntVec2, float>;
	//using DmapV2d = std::vector<std::vector<float>>;
private:		// variables
	IntVec2 size_2d;
	std::vector<DmapElem> _goal_vec;
public:		// functions
	constexpr inline
};
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_dijkstra_map_classes_hpp
