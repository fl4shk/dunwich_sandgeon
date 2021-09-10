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

class MsgLog final
{
public:		// constants
	static constexpr size_t
		TAB_SPACING_SIZE = 4u,
		WIDGET_SPACING_SIZE = 6u;
	static const std::string
		TAB_SPACING_STR,
		WIDGET_SPACING_STR;
public:		// types
	using DataInnerElem = std::pair<FgBgColorPair, std::string>;
	using DataElem = std::deque<DataInnerElem>;
	using Data = std::deque<DataElem>;
private:		// variables
	Data _data;
public:		// functions
	MsgLog() = default;
	MsgLog(const Data& s_data);
	MsgLog(Data&& s_data);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(MsgLog);
	~MsgLog() = default;

	static inline std::string spaces_str(size_t length)
	{
		std::string ret;
		for (size_t i=0; i<length; ++i)
		{
			ret += " ";
		}
		return ret;
	}

	void pop_front();
	void push_back(const DataElem& to_push);
	void push_back(DataElem&& to_push);

	void wrap(size_t row_length);

	GEN_GETTER_BY_CON_REF(data);
private:		// functions
	void _wrap_back(size_t row_length);
};


class Menu final
{
public:		// types
	//class WidgetTriple final
	//{
	//public:		// constants
	//	static constexpr size_t
	//		SIZE = 5u, INNER_SIZE = 3u,
	//		LEFT_INDEX = 0u, INNER_INDEX = 1u, RIGHT_INDEX = 4u;
	//public:		// variables
	//	std::array<char, SIZE> data;
	//public:		// functions
	//	constexpr inline WidgetTriple() = default;
	//	constexpr inline WidgetTriple(const WidgetTriple& to_copy)
	//		: data(to_copy.data)
	//	{
	//	}
	//	constexpr inline WidgetTriple(WidgetTriple&& to_move)
	//		: data(std::move(to_move.data))
	//	{
	//	}
	//	constexpr inline WidgetTriple(const std::array<char, SIZE>& s_data)
	//		: data(s_data)
	//	{
	//	}
	//	constexpr inline WidgetTriple(std::array<char, SIZE>&& s_data)
	//		: data(std::move(s_data))
	//	{
	//	}
	//	constexpr inline ~WidgetTriple() = default;
	//	constexpr inline WidgetTriple& operator =
	//		(const WidgetTriple& to_copy)
	//	{
	//		data = to_copy.data;
	//		return *this;
	//	}
	//	constexpr inline WidgetTriple& operator =
	//		(WidgetTriple&& to_move)
	//	{
	//		data = std::move(to_copy.data);
	//		return *this;
	//	}

	//	inline std::string left() const
	//	{
	//		std::string ret;
	//		ret += data.at(LEFT_INDEX);
	//		return ret;
	//	}
	//	inline std::string inner() const
	//	{
	//		std::string ret;
	//		for (size_t i=0; i<INNER_SIZE; ++i)
	//		{
	//			ret += data.at(INNER_INDEX + i);
	//		}
	//		return ret;
	//	}
	//	inline std::string right() const
	//	{
	//		std::string ret;
	//		ret += data.at(RIGHT_INDEX);
	//		return ret;
	//	}
	//};
public:		// constants
	// The maximum value of `variable` when using a `HorizPicker` or
	// `HorizPickerWrap` `kind`.
	static constexpr int HORIZ_PICKER_VAR_MAX = 999;

	static constexpr FgBgColorPair
		UI_UNSELECTED_COLOR_PAIR = FontColor::White,
		UI_SELECTED_COLOR_PAIR = FontColor::LightGray;
	static const std::string
		BUTTON_STR,

		CHECK_BUTTON_UNCHECKED_STR,
		CHECK_BUTTON_CHECKED_STR,

		HORIZ_PICKER_VAR_LEFT_STR, HORIZ_PICKER_VAR_INNER_BLANK_STR,
		HORIZ_PICKER_VAR_RIGHT_STR;
	static constexpr size_t 
		WIDGET_SPACING_SIZE = MsgLog::WIDGET_SPACING_SIZE;

public:		// types
	class Node final
	{
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
	Menu(const std::string& s_start_key, const NodeMap& s_node_map);
	Menu(const std::string& s_start_key, NodeMap&& s_node_map);
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

	operator MsgLog () const;

	GEN_GETTER_BY_CON_REF(start_key);
	GEN_GETTER_AND_SETTER_BY_CON_REF(sel_key);
	GEN_GETTER_BY_CON_REF(node_map);
};

//class Hud final
//{
//private:		// variables
//};

} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_menu_etc_classes_hpp
