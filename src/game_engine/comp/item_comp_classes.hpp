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

#ifndef src_game_engine_comp_item_comp_classes_hpp
#define src_game_engine_comp_item_comp_classes_hpp

// src/game_engine/comp/item_comp_classes.hpp

#include "../../misc_includes.hpp"
#include "../../misc_types.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace comp {
//--------
// A regular key; unlocks most doors
class ItemKey final: public ecs::Comp {
public:		// constants
	static const std::string KIND_STR;
public:		// variables
	#define MEMB_LIST_COMP_ITEM_KEY(X)

public:		// functions
	inline ItemKey() = default;
	ItemKey(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ItemKey);
	virtual ~ItemKey() = default;

	virtual std::string kind_str() const;
	virtual operator binser::Value () const;
};
//--------
} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_comp_item_comp_classes_hpp
