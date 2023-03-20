// This file is part of Dunwich Sandgeon.
// 
// Copyright 2023 FL4SHK
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

#include "room_tunnel_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace lvgen_etc {
//--------
const std::vector<i32>
	// Chosen arbitrarily; might need to adjust later
	RoomTunnel::MIN_NUM_ROOM_TUNNELS_DARR({
		//--------
		// Level 1 (index 0)
		25,

		// Level 2 (index 1)
		25,

		// Level 3 (index 2)
		25,

		// Level 4 (index 3)
		25,

		// Level 5 (index 4)
		25,
		//--------
		////= 3,
		////= 5,
		////= 8,
		////= 10,
		////= 13,
		////= 15,
		////= 20,
		//= 25,
		//--------
	}),
	RoomTunnel::MAX_NUM_ROOM_TUNNELS_DARR({
		//--------
		// Level 1 (index 0)
		64,

		// Level 2 (index 1)
		64,

		// Level 3 (index 2)
		64,

		// Level 4 (index 3)
		64,

		// Level 5 (index 4)
		64,
		//--------
		////= 3;
		////= 5;
		////= 8;
		////= 15;
		////= 42;
		//= 64,
		//--------
	}),
	RoomTunnel::MIN_NUM_ROOMS_DARR({
		//--------
		// Level 1 (index 0)
		10,

		// Level 2 (index 1)
		10,

		// Level 3 (index 2)
		10,

		// Level 4 (index 3)
		10,

		// Level 5 (index 4)
		10,
		//--------
		////= 5;
		////= 7;
		//= 10;
		//--------
	});
const std::vector<i32>
	RoomTunnel::TUNNEL_MIN_LEN_DARR({
		//--------
		// Level 1 (index 0)
		4,

		// Level 2 (index 1)
		4,

		// Level 3 (index 2)
		4,

		// Level 4 (index 3)
		4,

		// Level 5 (index 4)
		4,
		//--------
		////= 2,
		////= 3,
		//= 4,
		////= 5,
		//--------
	}),
	RoomTunnel::TUNNEL_MAX_LEN_DARR({
		//--------
		// Level 1 (index 0)
		12,

		// Level 2 (index 1)
		12,

		// Level 3 (index 2)
		12,

		// Level 4 (index 3)
		12,

		// Level 5 (index 4)
		12,
		//--------
		////= 32;
		////= 20;
		////= 15;
		//= 12;
		////= 10;
		////= 8;
		//--------
	}),

	RoomTunnel::MIN_NUM_LOCKS_DARR({
		//--------
		// Level 1 (index 0)
		3,

		// Level 2 (index 1)
		3,

		// Level 3 (index 2)
		3,

		// Level 4 (index 3)
		3,

		// Level 5 (index 4)
		3,
		//--------
	}),
	RoomTunnel::MAX_NUM_LOCKS_DARR({
		//--------
		// Level 1 (index 0)
		5,

		// Level 2 (index 1)
		5,

		// Level 3 (index 2)
		5,

		// Level 4 (index 3)
		5,

		// Level 5 (index 4)
		5,
		//--------
	});

	//MIN_NUM_TUNNELS = 1,
	//MAX_NUM_TUNNELS = 64;

const std::vector<IntVec2>
	RoomTunnel::ROOM_MIN_SIZE_2D_DARR({
		//--------
		// Level 1 (index 0)
		{5, 5},

		// Level 2 (index 1)
		{5, 5},

		// Level 3 (index 2)
		{5, 5},

		// Level 4 (index 3)
		{5, 5},

		// Level 5 (index 4)
		{5, 5},
		//--------
		////= {3, 3},
		////= {4, 4},
		//= {5, 5},
		//--------
	}),
	RoomTunnel::ROOM_MAX_SIZE_2D_DARR({
		//--------
		// Level 1 (index 0)
		{12, 12},

		// Level 2 (index 1)
		{12, 12},

		// Level 3 (index 2)
		{12, 12},

		// Level 4 (index 3)
		{12, 12},

		// Level 5 (index 4)
		{12, 12},
		//--------
		////= {9, 9};
		////= {10, 10};
		//= {12, 12};
		////= {15, 15};
		//--------
	});
//--------
RoomTunnel::RoomTunnel() {}
RoomTunnel::RoomTunnel(const IntRect2& s_rect)
	: rect(s_rect) {}
RoomTunnel::~RoomTunnel() {}
//--------
//const std::string
//auto RoomTunnel::from_bv(const binser::Value& bv) -> RoomTunnel {
//	RoomTunnel ret;
//
//	MEMB_LIST_COMP_DUNGEON_ROOM_TUNNEL(BINSER_MEMB_FROM_BV_DESERIALIZE);
//
//	//if (!ret.is_valid())
//	if (!ret.fits_in_pfield_nb()) {
//		//throw std::invalid_argument(sconcat(
//		//		(func_name ? sconcat(*func_name, "(): ") : std::string()),
//		//		(msg ? sconcat(*msg, ": ") : std::string()),
//		//		data_str, " < ", min_str,
//		//			" || ", data_str, " || ", max_str,
//		//			": ",
//		//		data, " ", min, " ", max
//		//));
//		throw std::invalid_argument(sconcat(
//			"game_engine::lvgen_etc::RoomTunnel::from_bv(): ",
//			"`ret.rect` does not fit in the playfield: ", ret.rect
//		));
//	}
//	if (!ret.is_tunnel() && !ret.is_room()) {
//		throw std::invalid_argument(sconcat(
//			"game_engine::lvgen_etc::RoomTunnel::from_bv(): ",
//			"`ret.rect` is the wrong shape to be a path or a room: ",
//			ret.rect
//		));
//	}
//
//	return ret;
//}
//RoomTunnel::operator binser::Value () const {
//	binser::Value ret;
//
//	//MEMB_EX_MM_LIST_COMP_DUNGEON_ROOM_TUNNEL(BINSER_MEMB_SERIALIZE);
//	//MEMB_EX_CS_LIST_COMP_DUNGEON_ROOM_TUNNEL(BINSER_MEMB_SERIALIZE);
//	//MEMB_AUTOSER_LIST_COMP_DUNGEON_ROOM_TUNNEL(BINSER_MEMB_SERIALIZE);
//	//BINSER_MEMB_SERIALIZE(rect);
//	MEMB_LIST_COMP_DUNGEON_ROOM_TUNNEL(BINSER_MEMB_SERIALIZE);
//
//	return ret;
//}
//--------
//std::unordered_map<IntVec2, ecs::EntId>& RoomTunnel::upper_layer_umap(
//	PfieldLayerPrio priority
//) {
//	//switch (priority) {
//	//case PfieldLayerPrio::ItemsTraps
//	//}
//}
//const std::unordered_map<IntVec2, ecs::EntId>&
//RoomTunnel::upper_layer_umap(
//	PfieldLayerPrio priority
//) const {
//	//switch (priority) {
//	////--------
//	//case PfieldLayerPrio::
//	////--------
//	//}
//}
//--------
} // namespace lvgen_etc
} // namespace game_engine
} // namespace dunwich_sandgeon
