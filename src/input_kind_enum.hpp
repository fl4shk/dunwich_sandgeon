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

#ifndef src_input_kind_enum_hpp
#define src_input_kind_enum_hpp

// src/input_kind_enum.hpp

#include "misc_includes.hpp"

namespace dungwich_sandeon
{

enum class InputKind
{
	MoveLeft,
	MoveUp,
	MoveRight,
	MoveDown,

	TargetEnemy,
	TargetItem,

	ExitMenu,
	OpenInvMenu,
	OpenSaveMenu,

	SwitchWindow,

	ScrollWindowLeft,
	ScrollWindowUp,
	ScrollWindowRight,
	ScrollWindowDown,

	ZoomIn,
	ZoomOut,
};

} // namespace dungwich_sandeon


#endif		// src_input_kind_enum_hpp
