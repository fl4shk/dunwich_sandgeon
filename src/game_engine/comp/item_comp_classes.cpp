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

#include "item_comp_classes.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace comp {
//--------
const std::string ItemKey::KIND_STR("ItemKey");
ItemKey::ItemKey(const binser::Value& bv) {
	MEMB_LIST_COMP_ITEM_KEY(BINSER_MEMB_DESERIALIZE);
}
std::string ItemKey::kind_str() const {
	return KIND_STR;
}
ItemKey::operator binser::Value () const {
	binser::Value ret;

	MEMB_LIST_COMP_ITEM_KEY(BINSER_MEMB_SERIALIZE);

	return ret;
}
//--------
} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon
