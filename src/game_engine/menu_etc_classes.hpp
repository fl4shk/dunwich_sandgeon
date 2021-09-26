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

Rope split_rope_by_whitespace(const Rope& rope, bool keep_sep=false);
RopeDeque wrap_rope(const Rope& rope, size_t row_length,
	bool keep_sep=false);

class MsgLog final
{
public:		// constants
	static constexpr size_t
		TAB_SPACING_SIZE = 4u,
		WIDGET_SELECTED_SPACING_SIZE = 3u,
		WIDGET_SPACING_SIZE = 6u;
	static const std::string
		TAB_SPACING_STR,
		WIDGET_SELECTED_SPACING_STR,
		WIDGET_SPACING_STR;
	static constexpr size_t DEFAULT_INTERNAL_HEIGHT = 256;
private:		// variables
	RopeDeque _data;

	size_t
		// This height allows for scrolling
		_internal_height = DEFAULT_INTERNAL_HEIGHT,
		_scroll = 0;

	SizeVec2 _window_size_2d = Window::SCREEN_SIZE_2D;
	Vec2<bool> _center = Vec2(false, false);
	bool _keep_sep = false;
public:		// functions
	inline MsgLog(size_t s_internal_height=DEFAULT_INTERNAL_HEIGHT,
		const SizeVec2& s_window_size_2d=Window::SCREEN_SIZE_2D,
		Vec2<bool> s_center=Vec2(false, false), bool s_keep_sep=false)
		: _internal_height(s_internal_height),
		_window_size_2d(s_window_size_2d), _center(s_center),
		_keep_sep(s_keep_sep)
	{
	}
	MsgLog(const RopeDeque& s_data,
		size_t s_internal_height=DEFAULT_INTERNAL_HEIGHT,
		const SizeVec2& s_window_size_2d=Window::SCREEN_SIZE_2D,
		Vec2<bool> s_center=Vec2(false, false), bool s_keep_sep=false);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(MsgLog);
	inline ~MsgLog() = default;

	void clear();

	void pop_front();
	void push_back(const Rope& to_push, bool do_pop_front=true);
	void push_back(const RopePart& to_push, bool do_pop_front=true);

	//void wrap();

	GEN_GETTER_BY_CON_REF(data);
	GEN_GETTER_BY_VAL(internal_height);
	GEN_GETTER_AND_SETTER_BY_VAL(scroll);
	GEN_GETTER_BY_CON_REF(window_size_2d);
	GEN_GETTER_BY_CON_REF(center);
	GEN_GETTER_BY_VAL(keep_sep);
};


class Menu final
{
public:		// constants
	// The maximum value of `variable` when using a `HorizPicker` or
	// `HorizPickerWrap` `kind`.
	static constexpr int HORIZ_PICKER_VAR_MAX = 999;

	static constexpr FgBgColorPair
		WIDGET_UNSELECTED_COLOR_PAIR = FontColor::Gray,
		WIDGET_SELECTED_COLOR_PAIR = FontColor::White;
	static const std::string
		WIDGET_SELECTED_STR,

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
	template<typename SelfType>
	class ActionButtonFunctor final
	{
	protected:		// variables
		SelfType* _self = nullptr;
		std::function<void(SelfType*)> _func = nullptr;
	public:		// functions
		inline ActionButtonFunctor() = default;
		inline ActionButtonFunctor(SelfType* s_self,
			const std::function<void(SelfType*)>& s_func)
			: _self(s_self), _func(s_func)
		{
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ActionButtonFunctor);
		inline ~ActionButtonFunctor() = default;

		inline void operator () () const
		{
			_func(_self);
		}
	};
	//template<typename SelfType>
	//class ActionButtonParamFunctor final
	//{
	//protected:		// variables
	//	SelfType* _self = nullptr;
	//	std::function<void(SelfType*, int)> _func = nullptr;
	//public:		// functions
	//	inline ActionButtonParamFunctor() = default;
	//	inline ActionButtonParamFunctor(SelfType* s_self,
	//		const std::function<void(SelfType*, int)>& s_func)
	//		: _self(s_self), _func(s_func)
	//	{
	//	}
	//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ActionButtonParamFunctor);
	//	inline ~ActionButtonParamFunctor() = default;

	//	inline void operator () (int param) const
	//	{
	//		_func(_self, param);
	//	}
	//};

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

			//// Push button triggers the function pointer, which
			//// passes in value
			//ActionButtonParam,

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

		//// Button action with parameter
		//using DataActionParamFunc = std::function<void(int)>;
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
		u32 flags = 0;
		//--------
		// Where to go, using keyboard or controller; "" if nowhere
		//std::string left, right, up, down;
		std::string up, down;
		//--------
		std::variant
		<
			std::monostate,
			DataValue,
			DataActionFunc
			//DataActionParamFunc
		>
			data = std::monostate();
		//--------
		// Various uses
		int variable = 0;
		//--------
		OnUpdateFunc on_update_func = nullptr;
		//--------
	public:		// functions
		//--------
		Node();

		// This constructor takes an `std::monostate` for `s_data`
		Node(const std::string& s_text, Kind s_kind, u32 s_flags,
			const std::string& s_up, const std::string& s_down,
			std::monostate s_data, int s_variable,
			const OnUpdateFunc& s_on_update_func);

		// This constructor takes a `DataValue` for `s_data`
		Node(const std::string& s_text, Kind s_kind, u32 s_flags,
			const std::string& s_up, const std::string& s_down,
			const DataValue& s_data, int s_variable,
			const OnUpdateFunc& s_on_update_func);

		// This constructor takes a `DataActionFunc` for `s_data`
		Node(const std::string& s_text, Kind s_kind, u32 s_flags,
			const std::string& s_up, const std::string& s_down,
			const DataActionFunc& s_data, int s_variable,
			const OnUpdateFunc& s_on_update_func);

		//// This constructor takes a `DataActionParamFunc` for `s_data`
		//Node(const std::string& s_text, Kind s_kind, u32 s_flags,
		//	const std::string& s_up, const std::string& s_down,
		//	const DataActionParamFunc& s_data, int s_variable,
		//	const OnUpdateFunc& s_on_update_func);

		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Node);

		~Node();
		//--------
		std::string widget_horiz_picker_str() const;
		//--------
	};

	using NodeMap = std::map<std::string, Node>;
private:		// variables
	// The currently-selected `Node`'s key
	std::string _sel_key = "";

	SizeVec2 _size_2d = Window::SCREEN_SIZE_2D;
	NodeMap _node_map;
	Vec2<bool> _center = Vec2(false, false);
public:		// functions
	Menu() = default;
	Menu(const std::string& s_sel_key, const SizeVec2& s_size_2d,
		const NodeMap& s_node_map, Vec2<bool> s_center=Vec2(false, false));
	Menu(const std::string& s_sel_key, const SizeVec2& s_size_2d,
		NodeMap&& s_node_map, Vec2<bool> s_center=Vec2(false, false));
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

	GEN_GETTER_AND_SETTER_BY_CON_REF(sel_key);
	GEN_GETTER_BY_CON_REF(size_2d);
	GEN_GETTER_BY_CON_REF(node_map);
	GEN_GETTER_BY_CON_REF(center);
};

//class Hud final
//{
//private:		// variables
//};

} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_menu_etc_classes_hpp
