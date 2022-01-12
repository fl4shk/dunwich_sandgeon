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
inline Type val_from_jv(const Json::Value& jv)
{
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
	else
	{
		return Type(jv);
	}
}

} // namespace dungwich_sandeon

#endif		// src_misc_funcs_hpp
