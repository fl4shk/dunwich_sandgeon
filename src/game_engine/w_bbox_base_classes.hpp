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

#ifndef src_game_engine_w_bbox_base_classes_hpp
#define src_game_engine_w_bbox_base_classes_hpp

// src/game_engine/w_bbox_base_classes.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
class WIntBboxBase {
public:		// functions
	inline WIntBboxBase() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(WIntBboxBase);
	virtual ~WIntBboxBase() = default;

	virtual inline const IntRect2& bbox() const = 0;
	virtual inline IntRect2& bbox() = 0;
};
class WDblBboxBase {
public:		// functions
	inline WDblBboxBase() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(WDblBboxBase);
	virtual ~WDblBboxBase() = default;

	virtual inline const DblRect2& bbox() const = 0;
	virtual inline DblRect2& bbox() = 0;
};
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_w_bbox_base_classes_hpp
