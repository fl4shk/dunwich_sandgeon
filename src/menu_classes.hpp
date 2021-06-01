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

#ifndef src_menu_classes_hpp
#define src_menu_classes_hpp

// src/menu_classes.hpp

#include "misc_includes.hpp"

namespace dungwich_sandeon
{


class Menu final
{
public:		// types
	struct Node final
	{
	public:		// types
		enum class Kind
		{
			// End of node list
			End,

			// Button triggers the function pointer
			ActionButton,

			// Buttone triggers the function pointer, which passes in value
			ActionButtonParam,

			// When picked, set the dialog exit type to `variable`
			ExitButton,

			// Pick between multiple options, from zero to max defined in
			// `variable` (so use the highested allowed value +1)
			HorizPicker,

			// Pick between multiple options, but also wrap
			HorizPickerWrap,
		};
		// Value to modify for horiz pickers
		using DataValue = int*;

		// Button action
		using DataActionFunc = std::function<void()>;

		// Button action with parameter
		using DataActionParamFunc = std::function<void(int)>;

		using VariantData = std::variant<std::monostate, DataValue,
			DataActionFunc, DataActionParamFunc>;

		using OnUpdateFunc = std::function<void()>;
	public:		// variables
		// Who owns us?
		Menu* parent;

		// Index into `parent->_node_map`
		std::string self_str;

		Kind kind;

		u32 flags;

		// Where to go, using keyboard or controller; "" if nowhere
		std::string left, right, up, down;

		VariantData data;

		// Various uses
		int variable;

		// When it's updated
		OnUpdateFunc on_update;
	};
private:		// variables
	std::map<std::string, Node> _node_map;
public:		// functions
};

} // namespace dungwich_sandeon

#endif		// src_menu_classes_hpp
