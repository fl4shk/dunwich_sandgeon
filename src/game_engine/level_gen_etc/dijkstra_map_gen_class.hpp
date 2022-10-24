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
	using Dmap = std::vector<std::vector<float>>;

	class Goal final {
	public:		// variables
		IntVec2 pos;
		float val;
	};
	//class Goal final {
	//public:		// variables
	//	float val;
	//};
public:		// constants
	static constexpr float
		//DEFAULT_FLIP_SCALE = 1.2f;
		DEFAULT_FLIP_BONUS = -0.2f,
		VERY_HIGH_NUM
			= float(PFIELD_PHYS_SIZE_2D.x + PFIELD_PHYS_SIZE_2D.y) + 50.0f;
	//static const BgTileUset
	//	DEFAULT_NO_PASS_USET;
private:		// variables
	//std::unordered_map<IntVec2, float> _goal_umap;
	std::vector<Goal> _goal_vec;
public:		// functions
	DijkstraMapGen();
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DijkstraMapGen);
	~DijkstraMapGen();

	// add a goal
	DijkstraMapGen& add(const IntVec2& pos, float val=0.0f);

	Dmap gen_basic(
		const FloorLayout& floor_layout,
		const BgTileUset& no_pass_uset
	) const;
	Dmap gen_flipped(
		const FloorLayout& floor_layout,
		const BgTileUset& no_pass_uset,
		float bonus=DEFAULT_FLIP_BONUS
	) const;
	Dmap& flip(Dmap& dmap, float bonus=DEFAULT_FLIP_BONUS) const;

	//GEN_GETTER_BY_CON_REF(goal_umap);
	GEN_GETTER_BY_CON_REF(goal_vec);
};
//--------
} // namespace level_gen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_dijkstra_map_gen_class_hpp
