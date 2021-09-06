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

#ifndef src_game_engine_menu_etc_classes_hpp
#define src_game_engine_menu_etc_classes_hpp

// src/game_engine/menu_etc_classes.hpp

#include "../misc_includes.hpp"
#include "font_color_enum.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{

class Menu final
{
public:		// constants
	static constexpr FgBgColorPair
		UI_UNSELECTED_COLOR = FontColor::White,
		UI_SELECTED_COLOR = FontColor::Green;
	static const std::string
		BUTTON_UNSELECTED_STR, BUTTON_SELECTED_STR;

		//CHECK_BUTTON_UNSELECTED_UNCHECKED_STR,
		//CHECK_BUTTON_SELECTED_UNCHECKED_STR,
		//CHECK_BUTTON_UNSELECTED_CHECKED_STR,
		//CHECK_BUTTON_SELECTED_CHECKED_STR;

public:		// types
	class Node final
	{
	public:		// constants
		// The maximum value of `variable` when using a `HorizPicker` or
		// `HorizPickerWrap` `kind`.
		static constexpr int HORIZ_PICKER_VAR_MAX = 999;
		static constexpr size_t SPACING = 6u;
	public:		// types
		//--------
		enum class Kind
		{
			// Beginning of node list
			Start,

			// End of node list
			End,

			// Just display text on this line.
			TextOnly,

			// Push button triggers the function pointer
			ActionButton,

			// Push button triggers the function pointer, which
			// passes in value
			ActionButtonParam,

			// When picked, set the dialog exit type to `variable`
			ExitButton,

			// Pick between multiple options, from zero to max defined in
			// `variable` (so use the highest allowed value +1)
			HorizPicker,

			//// Pick between multiple options, but also wrap
			//HorizPickerWrap,
		};
		//--------
		// Value to modify for horiz pickers
		using DataValue = PrevCurrPair<int>;

		// Button action
		using DataActionFunc = std::function<void()>;

		// Button action with parameter
		using DataActionParamFunc = std::function<void(int)>;
		//--------
		// When it's updated at all
		using OnUpdateFunc = std::function<void()>;
		//--------
	public:		// variables
		//--------
		// The text displayed to the right of the menu item.
		std::string text;
		//--------
		Kind kind;
		//--------
		u32 flags;
		//--------
		// Where to go, using keyboard or controller; "" if nowhere
		struct 
		{
			//std::string left, right, up, down;
			std::string up, down;
		} where;
		//--------
		std::variant<std::monostate, DataValue, DataActionFunc,
			DataActionParamFunc>
			data;
		//--------
		// Various uses
		int variable;
		//--------
		OnUpdateFunc on_update_func;
		//--------
	};

	using NodeMap = std::map<std::string, Node>;
private:		// variables
	std::string
		// The starting `Node`'s key
		_start_key = "",

		// The currently-selected `Node`'s key
		_sel_key = "";

	NodeMap _node_map;
public:		// functions
	Menu() = default;
	inline Menu(const std::string& s_start_key, const NodeMap& s_node_map)
		: _start_key(s_start_key), _sel_key(s_start_key),
		_node_map(s_node_map)
	{
	}
	inline Menu(const std::string& s_start_key, NodeMap&& s_node_map)
		: _start_key(s_start_key), _sel_key(s_start_key),
		_node_map(std::move(s_node_map))
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Menu);
	~Menu() = default;

	inline Node& at(const std::string& key)
	{
		if (!_node_map.contains(key))
		{
			fprintf(stderr, "game_engine::Menu::at(): Internal error.\n");
			//exit(1);
		}

		return _node_map.at(key);
	}
	inline const Node& at(const std::string& key) const
	{
		if (!_node_map.contains(key))
		{
			fprintf(stderr,
				"game_engine::Menu::at() const: Internal error.\n");
			//exit(1);
		}

		return _node_map.at(key);
	}

	GEN_GETTER_BY_CON_REF(start_key);
	GEN_GETTER_AND_SETTER_BY_CON_REF(sel_key);
	GEN_GETTER_BY_CON_REF(node_map);
};

class Log final
{
private:		// variables
};

class Hud final
{
private:		// variables
};

} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_menu_etc_classes_hpp
