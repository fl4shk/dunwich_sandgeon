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
