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

using PosVec2 = Vec2<i32>;
using PosVec3 = Vec3<i32>;
//using PosVec2 = binser::Vec2Ex<i32>;
//using PosVec3 = binser::Vec3Ex<i32>;
using PosVec2Ex = binser::Vec2Ex<i32>;
using PosVec3Ex = binser::Vec3Ex<i32>;

using SizeVec2 = Vec2<u32>;
//using SizeVec2 = binser::Vec2Ex<u32>;
using SizeVec2Ex = binser::Vec2Ex<u32>;

} // namespace dunwich_sandgeon

#endif		// src_misc_types_hpp
