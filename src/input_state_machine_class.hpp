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

#ifndef src_input_state_machine_class_hpp
#define src_input_state_machine_class_hpp

// src/input_state_machine_class.hpp

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

	ZoomIn,
	ZoomOut,
};

class InputStateMachine final
{
private:		// variables
public:		// functions
};

} // namespace dungwich_sandeon


#endif		// src_input_state_machine_class_hpp