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
#include "basic_window_classes.hpp"
#include "comp/general_comp_classes.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{

class RopePart final
{
public:		// types
	class CtorArgs final
	{
	public:		// variables
		std::string str;
		FgBgColorPair
			color_pair,
			gs_color_pair;
	};
public:		// variables
	std::string str;
	FgBgColorPair
		color_pair = FontColor::White,
		gs_color_pair = FontColor::White;
public:		// variables
	inline RopePart() = default;

	inline RopePart(const CtorArgs& ctor_args)
		: str(ctor_args.str), color_pair(ctor_args.color_pair),
		gs_color_pair(ctor_args.gs_color_pair)
	{
	}
	inline RopePart(CtorArgs&& ctor_args)
		: str(std::move(ctor_args.str)),
		color_pair(ctor_args.color_pair),
		gs_color_pair(ctor_args.gs_color_pair)
	{
	}
	inline RopePart(comp::Drawable::Data drawable_data)
		: str(""), color_pair(drawable_data.color_pair),
		gs_color_pair(drawable_data.gs_color_pair)
	{
		str += drawable_data.c;
	}

	inline RopePart(const std::string& s_str,
		FgBgColorPair s_color_pair, FgBgColorPair s_gs_color_pair)
		: str(s_str), color_pair(s_color_pair),
		gs_color_pair(s_gs_color_pair)
	{
	}
	inline RopePart(std::string&& s_str,
		FgBgColorPair s_color_pair, FgBgColorPair s_gs_color_pair)
		: str(std::move(s_str)), color_pair(s_color_pair),
		gs_color_pair(s_gs_color_pair)
	{
	}
	inline RopePart(char c,
		FgBgColorPair s_color_pair, FgBgColorPair s_gs_color_pair)
		: str(""), color_pair(s_color_pair),
		gs_color_pair(s_gs_color_pair)
	{
		str += c;
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(RopePart);
	inline ~RopePart() = default;
};

using Rope = std::deque<RopePart>;
using RopeDeque = std::deque<Rope>;

Rope split_rope_by_whitespace(const Rope& rope);
RopeDeque wrap_rope(const Rope& rope, size_t row_length);

class MsgLog final
{
public:		// constants
	static constexpr size_t
		TAB_SPACING_SIZE = 4u,
		WIDGET_SPACING_SIZE = 6u;
	static const std::string
		TAB_SPACING_STR,
		WIDGET_SPACING_STR;
private:		// variables
	RopeDeque _data;
	SizeVec2 _size_2d = Window::SCREEN_SIZE_2D;
public:		// functions
	inline MsgLog(const SizeVec2& s_size_2d=Window::SCREEN_SIZE_2D)
		: _size_2d(s_size_2d)
	{
	}
	MsgLog(const RopeDeque& s_data,
		const SizeVec2& s_size_2d=Window::SCREEN_SIZE_2D);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(MsgLog);
	inline ~MsgLog() = default;

	void clear();

	void pop_front();
	void push_back(const Rope& to_push, bool do_pop_front=true);
	void push_back(const RopePart& to_push, bool do_pop_front=true);

	//void wrap();

	GEN_GETTER_BY_CON_REF(data);
	GEN_GETTER_BY_CON_REF(size_2d);
};


class Menu final
{
public:		// constants
	// The maximum value of `variable` when using a `HorizPicker` or
	// `HorizPickerWrap` `kind`.
	static constexpr int HORIZ_PICKER_VAR_MAX = 999;

	static constexpr FgBgColorPair
		WIDGET_UNSELECTED_COLOR_PAIR = FontColor::White,
		WIDGET_SELECTED_COLOR_PAIR = FontColor::Gray;
	static const std::string
		WIDGET_BUTTON_STR,

		WIDGET_CHECK_BUTTON_UNCHECKED_STR,
		WIDGET_CHECK_BUTTON_CHECKED_STR,

		WIDGET_HORIZ_PICKER_LEFT_STR,
		WIDGET_HORIZ_PICKER_INNER_BLANK_STR,
		WIDGET_HORIZ_PICKER_RIGHT_STR;
	static constexpr size_t 
		WIDGET_SPACING_SIZE = MsgLog::WIDGET_SPACING_SIZE;

	static const std::string
		START_NODE_KEY, END_NODE_KEY;

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
	public:		// functions
		//--------
		inline std::string widget_horiz_picker_str() const
		{
			std::string ret;

			ret += WIDGET_HORIZ_PICKER_LEFT_STR;

			const std::string DATA_STR
				= sconcat(std::get<DataValue>(data)());
			{
				size_t i;
				for (i=0; i<DATA_STR.size(); ++i)
				{
					ret += DATA_STR.at(i);
				}
				for (; i<WIDGET_HORIZ_PICKER_INNER_BLANK_STR.size(); ++i)
				{
					ret += " ";
				}
			}
			ret += WIDGET_HORIZ_PICKER_RIGHT_STR;

			return ret;
		}
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
	SizeVec2 _size_2d = Window::SCREEN_SIZE_2D;
public:		// functions
	Menu() = default;
	Menu(const std::string& s_start_key, const NodeMap& s_node_map,
		const SizeVec2& s_size_2d=Window::SCREEN_SIZE_2D);
	Menu(const std::string& s_start_key, NodeMap&& s_node_map,
		const SizeVec2& s_size_2d=Window::SCREEN_SIZE_2D);
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
	GEN_GETTER_BY_CON_REF(size_2d);
};

//class Hud final
//{
//private:		// variables
//};

} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_menu_etc_classes_hpp
