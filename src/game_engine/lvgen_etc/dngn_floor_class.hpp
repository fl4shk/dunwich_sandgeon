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

#ifndef src_game_engine_lvgen_etc_dngn_floor_class_hpp
#define src_game_engine_lvgen_etc_dngn_floor_class_hpp

// src/game_engine/lvgen_etc/dngn_floor_class.hpp

#include "../../misc_includes.hpp"
//#include "../shape_classes.hpp"
#include "../w_bbox_base_classes.hpp"
#include "../global_shape_constants_etc.hpp"
//#include "path_class.hpp"
//#include "../comp/general_comp_classes.hpp"
#include "bg_tile_enum.hpp"
#include "room_tunnel_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
class Engine;
//--------
namespace lvgen_etc {
//--------
class DngnGen;
//--------
enum class AltTerrainState: u8 {
	Normal,
	Destroyed,
	ShowAlt,
};
class AltTerrainInfo final {
public:		// types
public:		// variables
	#define MEMB_LIST_LVGEN_ETC_ALT_TERRAIN_STATE(X) \
		X(state, std::nullopt) \
		X(alt_bg_tile, std::nullopt) \
		X(key, std::nullopt) \

	//bool show = false;
	//BgTile bg_tile = BgTile::Error;
	//bool destroyed = false;
	//bool destroyed: 1 = false;
	//bool show_alt: 1 = false;
	AltTerrainState state = AltTerrainState::Normal;
	BgTile alt_bg_tile = BgTile::Error;
	ecs::EntId key = ecs::ENT_NULL_ID;
public:		// functions
	static AltTerrainInfo from_bv(const binser::Value& bv);
	operator binser::Value () const;
};
//--------
// The dungeon while it's either being generated has finished generating.
// This includes generated items on the floor.
class DngnFloor final {
	#include "dngn_floor_friends.hpp"
public:		// constants
public:		// types
private:		// variables
	std::vector<RoomTunnelSptr> _rt_data;
	std::unordered_map<RoomTunnel*, size_t> _rt_to_id_umap;
	CollGridT _coll_grid;
	//binser::VectorEx<RoomTunnel> _rt_data;
	//double
	//	_layout_noise_pos_scale = 0.0d,
	//	_layout_noise_pos_offset = 0.0d;
public:		// variables
	IntVec2
		ustairs_pos;
	std::optional<IntVec2>
		dstairs_pos = std::nullopt;
private:		// serialized variables
	#define MEMB_SER_LIST_LVGEN_ETC_FLOOR_LAYOUT(X) \
		X(_pos3_z, std::nullopt) \
		/* X(destroyed_alt_terrain_uset, std::nullopt) */ \
		X(alt_terrain_state_umap, std::nullopt) \
		/* X(gnd_item_umap, std::nullopt) */ \

	i32 _pos3_z = -1;
public:		// serialized variables
	//IntVec2Uset
	//	destroyed_alt_terrain_uset;
	std::unordered_map<IntVec2, AltTerrainInfo>
		alt_terrain_state_umap;
	//std::unordered_map<IntVec2, ecs::EntIdUset> gnd_item_umap;
public:		// functions
	//--------
	DngnFloor();
	DngnFloor(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(DngnFloor);
	~DngnFloor() = default;

	operator binser::Value () const;
	//--------
	std::optional<BgTile> bg_tile_at(const IntVec2& pos, size_t i) const;
	std::optional<BgTile> phys_bg_tile_at(const IntVec2& pos) const;
	//inline std::optional<BgTile> left_phys_bg_tile_at(const IntVec2& pos)
	//const {
	//	return phys_bg_tile_at(pos + LEFT_OFFSET);
	//}
	//inline std::optional<BgTile> top_phys_bg_tile_at(const IntVec2& pos)
	//const {
	//	return phys_bg_tile_at(pos + TOP_OFFSET);
	//}
	//inline std::optional<BgTile> right_phys_bg_tile_at(const IntVec2& pos)
	//const {
	//	return phys_bg_tile_at(pos + RIGHT_OFFSET);
	//}
	//inline std::optional<BgTile> bottom_phys_bg_tile_at(const IntVec2& pos)
	//const {
	//	return phys_bg_tile_at(pos + BOTTOM_OFFSET);
	//}
	//--------
	inline auto begin() {
		//return _rt_data.data.begin();
		return _rt_data.begin();
	}
	inline auto end() {
		//return _rt_data.data.end();
		return _rt_data.end();
	}
	inline auto cbegin() const {
		//return _rt_data.data.cbegin();
		return _rt_data.cbegin();
	}
	inline auto cend() const {
		//return _rt_data.data.cend();
		return _rt_data.cend();
	}
private:		// functions
	inline RoomTunnel& _raw_at(size_t index) {
		//return _rt_data.data.at(index);
		return *_rt_data.at(index);
	}
	//RoomTunnel& _raw_phys_at(const IntVec2& phys_pos);
public:		// functions
	//inline RoomTunnel& at(size_t index) {
	//	//return _rt_data.data.at(index);
	//	return *_rt_data.at(index);
	//}
	inline const RoomTunnel& at(size_t index) const {
		//return _rt_data.data.at(index);
		return *_rt_data.at(index);
	}
	std::optional<size_t> phys_pos_to_rt_index(const IntVec2& phys_pos)
	const;
	//inline RoomTunnel::Xdata& xdata_at(size_t index) {
	//	return _rt_data.at(index)->xdata;
	//}
	//inline const RoomTunnel::Xdata& xdata_at(size_t index) const {
	//	return _rt_data.at(index)->xdata;
	//}
	void push_back(RoomTunnel&& to_push);
	//void pop_back() {
	//	_rt_to_id_umap.erase(_rt_data.back().get());
	//	_coll_grid.erase(_rt_data.back().get());
	//	_rt_data.pop_back();
	//}
	inline size_t size() const {
		//return _rt_data.data.size();
		return _rt_data.size();
	}
	// Note that this function *DOESN'T* clear `destroyed_alt_terrain_uset`
	// because that is serialized
	void clear_before_gen(
		//double n_layout_noise_pos_scale,
		//double n_layout_noise_pos_offset
	);
	// Note that this function *DOES* erase elements of
	// `destroyed_alt_terrain_uset`
	bool erase_path_during_gen(size_t index);
	CollGridT::DataElPtrUsetT cg_neighbors(RoomTunnel& rt) const;
	CollGridT::DataElPtrUsetT cg_neighbors(size_t index) const;
	CollGridT::DataElPtrUsetT cg_neighbors(const IntVec2& pos) const;

	void draw() const;
	//--------
	GEN_GETTER_BY_CON_REF(rt_data);
	GEN_GETTER_BY_CON_REF(rt_to_id_umap);
	GEN_GETTER_BY_CON_REF(coll_grid);
	GEN_GETTER_BY_VAL(pos3_z);
	//GEN_GETTER_BY_CON_REF(path_darr);
	//GEN_GETTER_BY_CON_REF(layout_noise_pos_scale);
	//GEN_GETTER_BY_CON_REF(layout_noise_pos_offset);
	//--------
};
//--------
} // namespace lvgen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_lvgen_etc_dngn_floor_class_hpp
