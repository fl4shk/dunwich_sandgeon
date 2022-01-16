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

#ifndef src_game_engine_comp_base_class_hpp
#define src_game_engine_comp_base_class_hpp

// src/game_engine/comp/base_class.hpp

#include "../../misc_includes.hpp"
#include "../../misc_types.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace comp
{

#define COMP_SERIALIZE(name) \
	set_jv_memb(ret, #name, name);
#define COMP_DESERIALIZE(name) \
	name = get_jv_memb<decltype(name)>(jv, #name);
#define COMP_FROM_JV_DESERIALIZE(name) \
	ret.name = get_jv_memb<decltype(ret.name)>(jv, #name);

class Base: public ecs::Comp
{
public:		// constants
	static const std::string KIND_STR;
public:		// functions
	inline Base() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Base);
	virtual ~Base() = default;

	virtual std::string kind_str() const;
	virtual operator Json::Value () const;
};

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_comp_base_class_hpp
