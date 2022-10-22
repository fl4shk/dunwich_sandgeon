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

#ifndef src_game_engine_dijkstra_map_gen_class_hpp
#define src_game_engine_dijkstra_map_gen_class_hpp

// src/game_engine/dijkstra_map_gen_class.hpp

#include "../../misc_includes.hpp"
#include "../../misc_types.hpp"
#include "../global_shape_constants_etc.hpp"
#include "floor_layout_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace level_gen_etc {
//--------
// See the below links for more information:
// http://www.roguebasin.com/index.php/The_Incredible_Power_of_Dijkstra_Maps
// http://www.roguebasin.com/index.php/Dijkstra_Maps_Visualized
//class DijkstraMap final {
//public:		// types
//	using Data = std::vector<std::vector<float>>;
//	class Goal final {
//	public:		// variables
//		IntVec2 pos;
//		float val;
//	};
//private:		// variables
//	Data _data;
//public:		// functions
//	DijkstraMap 
//};
class DijkstraMapGen final {
public:		// types
	//using Goal = std::pair<IntVec2, float>;
	//using DmapV2d = std::vector<std::vector<float>>;
	using Dmap = std::unordered_map<IntVec2, float>;

	//class Goal final {
	//public:		// variables
	//	IntVec2 pos;
	//	float val;
	//};
public:		// constants
	static constexpr float
		FLIP_SCALE = 1.2f;
private:		// variables
	std::unordered_map<IntVec2, float> _goal_umap;
public:		// functions
	DijkstraMapGen();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DijkstraMapGen);
	~DijkstraMapGen();

	// add a `Goal`
	DijkstraMapGen& add(const IntVec2& pos, float val);

	Dmap gen_basic(const FloorLayout& floor_layout) const;
	Dmap gen_flipped(const FloorLayout& floor_layout) const;

	GEN_GETTER_BY_CON_REF(goal_umap);
};
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_dijkstra_map_gen_class_hpp
