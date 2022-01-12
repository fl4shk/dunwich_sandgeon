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
#include "misc_funcs.hpp"

namespace dungwich_sandeon
{

using PosVec2 = Vec2<int>;
using PosVec3 = Vec3<int>;
using SizeVec2 = Vec2<uint>;

template<typename Type>
inline Vec2<Type> vec2_from_jv(const Json::Value& jv)
{
	return 
		Vec2<Type>
		(
			val_from_jv<Type>(jv["x"]),
			val_from_jv<Type>(jv["y"])
		);
}
template<typename Type>
inline Json::Value vec2_to_jv(const Vec2<Type> vec)
{
	Json::Value ret;

	ret["x"] = vec.x;
	ret["y"] = vec.y;

	return ret;
}

template<typename Type>
inline Vec3<Type> vec3_from_jv(const Json::Value& jv)
{
	return
		Vec3<Type>
		(
			val_from_jv<Type>(jv["x"]),
			val_from_jv<Type>(jv["y"]),
			val_from_jv<Type>(jv["z"])
		);
}
template<typename Type>
inline Json::Value vec3_to_jv(const Vec3<Type> vec)
{
	Json::Value ret;

	ret["x"] = vec.x;
	ret["y"] = vec.y;
	ret["z"] = vec.z;

	return ret;
}

} // namespace dungwich_sandeon

#endif		// src_misc_types_hpp
