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

#ifndef src_engine_menu_classes_hpp
#define src_engine_menu_classes_hpp

// src/engine/menu_classes.hpp

#include "../misc_includes.hpp"

namespace dungwich_sandeon
{

namespace engine
{

class Menu final
{
public:		// types
	class Node final
	{
	public:		// everything
		//--------
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

		Kind kind;
		//--------
		u32 flags;
		//--------
		// Where to go, using keyboard or controller; "" if nowhere
		struct 
		{
			std::string left, right, up, down;
		} where;
		//--------
		// Value to modify for horiz pickers
		using DataValue = int*;

		// Button action
		using DataActionFunc = std::function<void()>;

		// Button action with parameter
		using DataActionParamFunc = std::function<void(int)>;

		std::variant<std::monostate, DataValue, DataActionFunc,
			DataActionParamFunc> data;
		//--------
		// Various uses
		int variable;
		//--------
		// When it's updated
		using OnUpdateFunc = std::function<void()>;

		OnUpdateFunc on_update;
		//--------
	};

	using NodeMap = std::map<std::string, Node>;
private:		// variables
	NodeMap _node_map;
public:		// functions
	Menu() = default;
	inline Menu(const NodeMap& s_node_map)
		: _node_map(s_node_map)
	{
	}
	inline Menu(NodeMap&& s_node_map)
		: _node_map(std::move(s_node_map))
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Menu);
	~Menu() = default;
};

} // namespace engine

} // namespace dungwich_sandeon

#endif		// src_engine_menu_classes_hpp
