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

#ifndef src_input_kind_enum_hpp
#define src_input_kind_enum_hpp

// src/input_kind_enum.hpp

#include "misc_includes.hpp"

namespace dunwich_sandgeon
{

enum class InputKind: i32
{
	None,

	Left,
	Up,
	Right,
	Down,

	UpLeft,
	UpRight,
	DownRight,
	DownLeft,

	Escape,
	Enter,

	SwitchWindow,

	OpenInventoryWindow,
	OpenMiscActionsWindow,
	OpenSaveWindow,

	BeginAttack,
	BeginRangedAttack,
	BeginThrow,

	Lim,
};

inline InputKind input_kind_add(InputKind input_kind, i32 amount)
{
	i32 ret_u32 = static_cast<i32>(input_kind);
	ret_u32 += amount;
	return static_cast<InputKind>(ret_u32);
}

extern const std::map<InputKind, std::string> INPUT_KIND_TO_STR_MAP;

} // namespace dunwich_sandgeon

#endif		// src_input_kind_enum_hpp
