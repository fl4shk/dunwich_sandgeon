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

#ifndef src_misc_types_hpp
#define src_misc_types_hpp

// src/misc_types.hpp

#include "misc_includes.hpp"
#include "misc_funcs.hpp"

namespace dunwich_sandgeon
{

using IntVec2 = math::Vec2<i32>;
using IntVec3 = math::Vec3<i32>;

////using PosVec2 = binser::Vec2Ex<i32>;
////using PosVec3 = binser::Vec3Ex<i32>;
using IntVec2Ex = binser::Vec2Ex<i32>;
using IntVec3Ex = binser::Vec3Ex<i32>;

using IntHit2 = math::Hit2<i32>;
using IntSweep2 = math::Sweep2<i32>;
using IntLineSeg2 = math::LineSeg2<i32>;
using IntRect2 = math::Rect2<i32>;

using IntLineSeg2Ex = binser::LineSeg2Ex<i32>;
using IntRect2Ex = binser::Rect2Ex<i32>;

//using SizeVec2 = math::Vec2<u32>;
////using SizeVec2 = binser::Vec2Ex<u32>;
//using SizeVec2Ex = binser::Vec2Ex<u32>;
//
//using DblVec2 = math::Vec2<double>;
//using DblVec2Ex = binser::Vec2Ex<double>;
using DblVec2 = math::Vec2<double>;
using DblVec3 = math::Vec3<double>;

using DblVec2Ex = binser::Vec2Ex<double>;
using DblVec3Ex = binser::Vec3Ex<double>;

using DblHit2 = math::Hit2<double>;
using DblSweep2 = math::Sweep2<double>;
using DblLineSeg2 = math::LineSeg2<double>;
using DblRect2 = math::Rect2<double>;

using DblLineSeg2Ex = binser::LineSeg2Ex<double>;
using DblRect2Ex = binser::Rect2Ex<double>;

//template<typename FirstT, typename OtherT>
//inline void set_vec2(Vec2<FirstT>& self, const Vec2<OtherT>& other)
//{
//	self.x = other.x;
//	self.y = other.y;
//}

} // namespace dunwich_sandgeon

#endif		// src_misc_types_hpp
