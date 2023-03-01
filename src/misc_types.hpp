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

#ifndef src_misc_types_hpp
#define src_misc_types_hpp

// src/misc_types.hpp

#include "misc_includes.hpp"
#include "misc_funcs.hpp"

namespace dunwich_sandgeon {
//--------
template<typename T>
using Vec2Uset = std::unordered_set<Vec2<T>>;
template<typename T>
using Vec3Uset = std::unordered_set<Vec3<T>>;

using IntVec2 = Vec2<i32>;
using IntVec3 = Vec3<i32>;
using IntVec2Uset = Vec2Uset<i32>;
using IntVec3Uset = Vec3Uset<i32>;

////using PosVec2 = binser::Vec2Ex<i32>;
////using PosVec3 = binser::Vec3Ex<i32>;
using IntVec2Ex = binser::Vec2Ex<i32>;
using IntVec3Ex = binser::Vec3Ex<i32>;

using IntHit2 = Hit2<i32>;
using IntSweep2 = Sweep2<i32>;
using IntLineSeg2 = LineSeg2<i32>;
using IntRect2 = Rect2<i32>;

using IntLineSeg2Ex = binser::LineSeg2Ex<i32>;
using IntRect2Ex = binser::Rect2Ex<i32>;

//using SizeVec2 = Vec2<u32>;
////using SizeVec2 = binser::Vec2Ex<u32>;
//using SizeVec2Ex = binser::Vec2Ex<u32>;
//
//using FltVec2 = Vec2<float>;
//using FltVec2Ex = binser::Vec2Ex<float>;
using FltVec2 = Vec2<float>;
using FltVec3 = Vec3<float>;
using FltVec2Uset = Vec2Uset<float>;
using FltVec3Uset = Vec3Uset<float>;

using FltVec2Ex = binser::Vec2Ex<float>;
using FltVec3Ex = binser::Vec3Ex<float>;

using FltHit2 = Hit2<float>;
using FltSweep2 = Sweep2<float>;
using FltLineSeg2 = LineSeg2<float>;
using FltRect2 = Rect2<float>;

using FltLineSeg2Ex = binser::LineSeg2Ex<float>;
using FltRect2Ex = binser::Rect2Ex<float>;

using FltDynarr = std::vector<float>;
using FltDyna2d = std::vector<FltDynarr>;

using BoolDynarr = std::vector<bool>;
using BoolDyna2d = std::vector<BoolDynarr>;

using DblVec2 = Vec2<double>;
using DblVec2Uset = Vec2Uset<double>;
using DblLineSeg2 = LineSeg2<double>;
using DblTri2 = Tri2<double>;
using DblRect2 = Rect2<double>;

//template<typename FirstT, typename OtherT>
//inline void set_vec2(Vec2<FirstT>& self, const Vec2<OtherT>& other) {
//	self.x = other.x;
//	self.y = other.y;
//}
//--------
} // namespace dunwich_sandgeon

#endif		// src_misc_types_hpp
