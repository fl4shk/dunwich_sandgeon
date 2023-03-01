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

#ifndef src_game_engine_w_bbox_base_classes_hpp
#define src_game_engine_w_bbox_base_classes_hpp

// src/game_engine/w_bbox_base_classes.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
template<typename T>
class WBboxBase {
public:		// functions
	inline WBboxBase() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(WBboxBase);
	virtual ~WBboxBase() = default;

	virtual inline const math::Rect2<T>& bbox() const = 0;
	//virtual inline math::Rect2<T>& bbox() = 0;
};
using WIntBboxBase = WBboxBase<i32>;
using WFltBboxBase = WBboxBase<float>;
//class WIntBboxBase {
//public:		// functions
//	inline WIntBboxBase() = default;
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(WIntBboxBase);
//	virtual ~WIntBboxBase() = default;
//
//	virtual inline const IntRect2& bbox() const = 0;
//	virtual inline IntRect2& bbox() = 0;
//};
//class WFltBboxBase {
//public:		// functions
//	inline WFltBboxBase() = default;
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(WFltBboxBase);
//	virtual ~WFltBboxBase() = default;
//
//	virtual inline const FltRect2& bbox() const = 0;
//	virtual inline FltRect2& bbox() = 0;
//};
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_w_bbox_base_classes_hpp
