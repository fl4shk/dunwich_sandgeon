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

#ifndef src_misc_funcs_hpp
#define src_misc_funcs_hpp

// src/misc_funcs.hpp

#include "misc_includes.hpp"

namespace dungwich_sandeon
{

template<typename Type>
extern u32 _is_vec2_func(const Vec2<Type>&);
template<typename Type>
extern u8 _is_vec2_func(const Type&);

#define IS_VEC2(T) \
	(sizeof(_is_vec2_func(std::declval<T>())) == sizeof(u32))

template<typename Type>
extern u32 _is_vec3_func(const Vec3<Type>&);
template<typename Type>
extern u8 _is_vec3_func(const Type&);

#define IS_VEC3(T) \
	(sizeof(_is_vec3_func(std::declval<T>())) == sizeof(u32))

template<typename Type>
extern u32 _is_std_vec_func(const std::vector<Type>&);
template<typename Type>
extern u8 _is_std_vec_func(const Type&);

#define IS_STD_VEC(T) \
	(sizeof(_is_std_vec_func(std::declval<T>())) == sizeof(u32))


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
inline Json::Value vec2_to_jv(const Vec2<Type>& vec)
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
inline Json::Value vec3_to_jv(const Vec3<Type>& vec)
{
	Json::Value ret;

	ret["x"] = vec.x;
	ret["y"] = vec.y;
	ret["z"] = vec.z;

	return ret;
}

template<typename Type>
inline Type val_from_jv(const Json::Value& jv)
{
	//--------
	if constexpr (std::is_same<Type, int>())
	{
		return jv.asInt();
	}
	else if constexpr (std::is_same<Type, uint>())
	{
		return jv.asUInt();
	}
	else if constexpr (std::is_same<Type, float>())
	{
		return jv.asFloat();
	}
	else if constexpr (std::is_same<Type, double>())
	{
		return jv.asDouble();
	}
	else if constexpr (std::is_same<Type, bool>())
	{
		return jv.asBool();
	}
	else if constexpr (std::is_same<Type, std::string>())
	{
		return jv.asString();
	}
	//--------
	else if constexpr (IS_VEC2(Type))
	{
		return vec2_from_jv<decltype(Type().x)>(jv);
	}
	else if constexpr (IS_VEC3(Type))
	{
		return vec3_from_jv<decltype(Type().x)>(jv);
	}
	//--------
	else if constexpr (IS_STD_VEC(Type))
	{
		Type ret;

		for (Json::ArrayIndex i=0; i<jv.size(); ++i)
		{
			ret.push_back(val_from_jv<decltype(Type().at(0))>(jv[i]));
		}

		return ret;
	}
	//--------
	else if constexpr (std::is_constructible<Type, const Json::Value&>())
	{
		return Type(jv);
	}
	else
	{
		// Assume a static member function called `from_jv` exists
		return Type::from_jv(jv);
	}
	//--------
}

template<typename Type>
inline Type get_jv_memb(const Json::Value& jv,
	const std::string& name)
{
	if constexpr (std::is_same<Type, i64>())
	{
		i64 ret = 0;

		ret = static_cast<i64>(val_from_jv<uint>
			(jv[sconcat(name, ".high")]) << static_cast<i64>(32u))
			| static_cast<i64>(val_from_jv<uint>
				(jv[sconcat(name, ".low")]));

		return ret;
	}
	else if constexpr (std::is_same<Type, u64>())
	{
		u64 ret = 0;

		ret = static_cast<u64>(val_from_jv<uint>
			(jv[sconcat(name, ".high")]) << static_cast<u64>(32u))
			| static_cast<u64>(val_from_jv<uint>
				(jv[sconcat(name, ".low")]));

		return ret;
	}
	else
	{
		return val_from_jv<Type>(jv[name]);
	}
}

template<typename Type>
inline void _set_jv(Json::Value& jv, const Type& val)
{
	static_assert((!std::is_same<Type, i64>())
		&& (!std::is_same<Type, u64>()));

	//--------
	if constexpr (IS_VEC2(Type))
	{
		jv = vec2_to_jv(val);
	}
	else if constexpr (IS_VEC3(Type))
	{
		jv = vec3_to_jv(val);
	}
	//--------
	else if constexpr (IS_STD_VEC(Type))
	{
		for (Json::ArrayIndex i=0; i<val.size(); ++i)
		{
			jv[i] = val.at(i);
		}
	}
	//--------
	else
	{
		jv = val;
	}
	//--------
}

template<typename Type>
inline void set_jv_memb(Json::Value& jv, const std::string& name,
	const Type& val)
{
	//--------
	//if constexpr (std::is_same<Type, int>()
	//	|| std::is_same<Type, uint>()
	//	|| std::is_same<Type, float>()
	//	|| std::is_same<Type, double>())
	if constexpr (std::is_same<Type, i64>()
		|| std::is_same<Type, u64>())
	{
		jv[sconcat(name, ".high")] 
			= static_cast<u32>(static_cast<u64>(val)
				>> static_cast<u64>(32u));
		jv[sconcat(name, ".low")]
			= static_cast<u32>(static_cast<u64>(val)
				& static_cast<u64>(0xffffffffu));
	}
	else
	{
		_set_jv(jv[name], val);
	}
}

} // namespace dungwich_sandeon

#endif		// src_misc_funcs_hpp
