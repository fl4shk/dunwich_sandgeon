// This file is part of Dungwich Sandeon.
// 
// Dungwich Sandeon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// Dungwich Sandeon is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Dungwich Sandeon.  If not, see <https://www.gnu.org/licenses/>.

#ifndef src_misc_types_hpp
#define src_misc_types_hpp

// src/misc_types.hpp

#include "misc_includes.hpp"

namespace dungwich_sandeon
{

using StrKeySet = std::set<std::string>;
using PosVec2 = Vec2<int>;
using SizeVec2 = Vec2<size_t>;

template<typename Type>
class Vec3
{
public:		// variables
	Type x = 0, y = 0, z = 0;
public:		// functions
	inline Vec3() = default;
	inline Vec3(const Type& s_x, const Type& s_y, const Type& s_z)
		: x(s_x), y(s_y), z(s_z)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Vec3);
	virtual inline ~Vec3() = default;
};
using PosVec3 = Vec3<int>;

} // namespace dungwich_sandeon

#endif		// src_misc_types_hpp
