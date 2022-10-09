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

#ifndef src_game_engine_menu_etc_classes_hpp
#define src_game_engine_menu_etc_classes_hpp

// src/game_engine/menu_etc_classes.hpp

#include "../misc_includes.hpp"
#include "font_color_enum.hpp"
#include "global_shape_constants.hpp"
#include "comp/general_comp_classes.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
class RopePart final {
public:		// types
	class CtorArgs final {
	public:		// variables
		std::string str;
		FgBgColorPair
			color_pair,
			gs_color_pair;
	};
public:		// variables
	#define MEMB_LIST_ROPE_PART(X) \
		X(str, std::nullopt) \
		X(color_pair, std::nullopt) \
		X(gs_color_pair, std::nullopt)
	std::string str;
	FgBgColorPair
		color_pair = FontColor::White,
		gs_color_pair = FontColor::White;
public:		// variables
	inline RopePart() = default;

	inline RopePart(const CtorArgs& ctor_args)
		: str(ctor_args.str), color_pair(ctor_args.color_pair),
		gs_color_pair(ctor_args.gs_color_pair) {
	}
	inline RopePart(CtorArgs&& ctor_args)
		: str(std::move(ctor_args.str)),
		color_pair(ctor_args.color_pair),
		gs_color_pair(ctor_args.gs_color_pair) {
	}
	inline RopePart(comp::Drawable::Data drawable_data)
		: str(""), color_pair(drawable_data.color_pair),
		gs_color_pair(drawable_data.gs_color_pair) {
		str += drawable_data.c;
	}

	inline RopePart(const std::string& s_str,
		FgBgColorPair s_color_pair, FgBgColorPair s_gs_color_pair)
		: str(s_str), color_pair(s_color_pair),
		gs_color_pair(s_gs_color_pair) {
	}
	inline RopePart(std::string&& s_str,
		FgBgColorPair s_color_pair, FgBgColorPair s_gs_color_pair)
		: str(std::move(s_str)), color_pair(s_color_pair),
		gs_color_pair(s_gs_color_pair) {
	}
	inline RopePart(char c,
		FgBgColorPair s_color_pair, FgBgColorPair s_gs_color_pair)
		: str(""), color_pair(s_color_pair),
		gs_color_pair(s_gs_color_pair) {
		str += c;
	}
	RopePart(const binser::Value& bv);

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(RopePart);
	inline ~RopePart() = default;

	RopePart& operator = (const binser::Value& bv);

	operator binser::Value () const;

};

std::ostream& operator << (std::ostream& os, const RopePart& rope_part);

using Rope = std::deque<RopePart>;
using RopeDeque = std::deque<Rope>;

std::ostream& operator << (std::ostream& os, const Rope& rope);

Rope split_rope_by_whitespace(const Rope& rope, bool keep_sep=false);
RopeDeque wrap_rope(const Rope& rope, i32 row_length,
	bool keep_sep=false);

class MsgLog final {
public:		// constants
	//static constexpr i32
	//	WIDGET_SELECTED_SPACING_SIZE = 3,
	//	WIDGET_SPACING_SIZE = 6;
	static const std::string
		WIDGET_SELECTED_SPACING_STR,
		WIDGET_SPACING_STR;
	//static constexpr i32 DEFAULT_INTERNAL_HEIGHT = 256;
	//static constexpr i32 DEFAULT_INTERNAL_HEIGHT = 70;
	static constexpr i32 DEFAULT_INTERNAL_HEIGHT = 10;
	//static const i32 DEFAULT_INTERNAL_HEIGHT;
private:		// variables
	#define MEMB_LIST_MSG_LOG(X) \
		X(_data, std::nullopt) \
		X(_internal_height, std::nullopt) \
		X(_scroll, std::nullopt) \
		X(_window_size_2d, std::nullopt) \
		X(_center, std::nullopt) \
		X(_keep_sep, std::nullopt)

	RopeDeque _data;

	i32
		// This height allows for scrolling
		_internal_height = DEFAULT_INTERNAL_HEIGHT,
		_scroll = 0;

	IntVec2 _window_size_2d = SCREEN_SIZE_2D;
	Vec2<bool> _center = {false, false};
	bool _keep_sep = false;
public:		// functions
	inline MsgLog(i32 s_internal_height=DEFAULT_INTERNAL_HEIGHT,
		const IntVec2& s_window_size_2d=SCREEN_SIZE_2D,
		Vec2<bool> s_center=Vec2(false, false), bool s_keep_sep=false)
		: _internal_height(s_internal_height),
		_window_size_2d(s_window_size_2d), _center(s_center),
		_keep_sep(s_keep_sep) {
	}
	MsgLog(const RopeDeque& s_data,
		i32 s_internal_height=DEFAULT_INTERNAL_HEIGHT,
		const IntVec2& s_window_size_2d=SCREEN_SIZE_2D,
		Vec2<bool> s_center={false, false}, bool s_keep_sep=false);
	MsgLog(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(MsgLog);
	inline ~MsgLog() = default;

	operator binser::Value () const;

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


class Menu final {
public:		// constants
	static constexpr i32
		// The maximum value of `variable` when using a `HorizPicker` or
		// `HorizPickerWrap` `kind`.
		HORIZ_PICKER_VAR_MAX = 999,
		WHOLE_SCREEN_MENU_TAB_AMOUNT_BIG
			= 7,
			//= 5,
			//= 4,
		WHOLE_SCREEN_MENU_TAB_AMOUNT_SMALL
			= 5;
			//= 3;

	static constexpr FgBgColorPair
		WIDGET_UNSELECTED_COLOR_PAIR = FontColor::Gray,
		WIDGET_SELECTED_COLOR_PAIR = FontColor::White,

		TEXT_ONLY_COLOR_PAIR = FontColor::Brown,
		TEXT_ONLY_GS_COLOR_PAIR = FontColor::White;
	static const std::string
		WIDGET_SELECTED_STR,

		WIDGET_BUTTON_STR,

		WIDGET_CHECK_BUTTON_UNCHECKED_STR,
		WIDGET_CHECK_BUTTON_CHECKED_STR,

		WIDGET_HORIZ_PICKER_LEFT_STR,
		WIDGET_HORIZ_PICKER_INNER_BLANK_STR,
		WIDGET_HORIZ_PICKER_RIGHT_STR;
	//static constexpr i32 
	//	WIDGET_SPACING_SIZE = MsgLog::WIDGET_SPACING_SIZE;

	static const std::string
		START_NODE_KEY, END_NODE_KEY;

	static constexpr i32
		TAB_SIZE = 4;
	static const std::string
		TAB_STR;

public:		// types
	class Node final {
	public:		// types
		//--------
		enum class Kind {
			// Beginning of node list
			Start,

			// End of node list
			End,

			// Just display text on this line.
			TextOnly,

			// Just display text on this line, but with leading whitespace
			// to match start of non-UI stuff of, for example,
			// `ActionButton`
			TextOnlyWithLeadingSpaces,

			// Push button triggers the function pointer
			ActionButton,

			//// Push button triggers the function pointer, which
			//// passes in value
			//ActionButtonParam,

			// Check button triggers the `on_update_func`
			CheckButton,

			//// When picked, set the dialog exit type to `variable`
			//ExitButton,

			// Pick between multiple options, from zero to max defined in
			// `variable` (so use the highest allowed value +1)
			HorizPicker,

			//// Pick between multiple options, but also wrap
			//HorizPickerWrap,
		};
		//--------
		// Value to modify for horiz pickers
		using DataValue = PrevCurrPair<i32>;

		// Button action
		using DataActionFunc = std::function<void()>;

		//// Button action with parameter
		//using DataActionParamFunc = std::function<void(i32)>;

		using DataVariant 
			= std::variant<
				std::monostate,			// Sorry, nothing
				bool,					// CheckButton
				DataValue,				// HorizPicker
				DataActionFunc			// ActionButton
				//DataActionParamFunc	// ActionButtonParam
			>;
		//--------
		// When it's updated at all
		using OnUpdateFunc = std::function<void(Node*)>;
		//--------
		// No connections
		class NoConn final {
		public:		// variables
			std::string text;
			Kind kind;
			DataVariant data = std::monostate();
			i32 variable = 0;
			OnUpdateFunc on_update_func = nullptr;
		};
		class CtorArgs final {
		public:		// variables
			NoConn no_conn;
			std::string up, down;
		};
		//--------
	public:		// variables
		//--------
		// The text displayed to the right of the menu item.
		std::string text;
		//--------
		Kind kind;
		//--------
		DataVariant data = std::monostate();
		//--------
		// Various uses
		i32 variable = 0;
		//--------
		OnUpdateFunc on_update_func = nullptr;
		//--------
		// Where to go, using keyboard or controller; "" if nowhere
		//std::string left, right, up, down;
		std::string up = "", down = "";
		//--------
	public:		// functions
		//--------
		Node();

		// This constructor takes an `std::monostate` for `s_data`
		inline Node(const std::string& s_text, Kind s_kind,
			const auto& s_data, i32 s_variable,
			const OnUpdateFunc& s_on_update_func,
			const std::string& s_up, const std::string& s_down)
		: text(s_text),
			kind(s_kind),
			data(s_data),
			variable(s_variable),
			on_update_func(s_on_update_func),
			up(s_up), down(s_down) {
		}

		Node(const NoConn& s_most_args, const std::string& s_up="",
			const std::string& s_down="");
		Node(const CtorArgs& ctor_args);

		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Node);

		~Node();
		//--------
		std::string widget_horiz_picker_str() const;
		std::string widget_check_button_str() const;
		//--------
	};

	template<typename SelfT>
	class ActionButtonFuncobj final {
	public:		// types
		using Func = std::function<void(SelfT*)>;
	private:		// variables
		SelfT* _self = nullptr;
		Func _func = nullptr;
	public:		// functions
		ActionButtonFuncobj() = default;
		inline ActionButtonFuncobj(SelfT* s_self, const Func& s_func)
			: _self(s_self), _func(s_func) {
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ActionButtonFuncobj);
		~ActionButtonFuncobj() = default;

		inline void operator () () const {
			_func(_self);
		}
	};
	//template<typename SelfT>
	//class ActionButtonParamFuncobj final {
	//protected:		// variables
	//	SelfT* _self = nullptr;
	//	std::function<void(SelfT*, i32)> _func = nullptr;
	//public:		// functions
	//	inline ActionButtonParamFuncobj() = default;
	//	inline ActionButtonParamFuncobj(SelfT* s_self,
	//		const std::function<void(SelfT*, i32)>& s_func)
	//		: _self(s_self), _func(s_func) {
	//	}
	//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ActionButtonParamFuncobj);
	//	inline ~ActionButtonParamFuncobj() = default;

	//	inline void operator () (i32 param) const {
	//		_func(_self, param);
	//	}
	//};
	template<typename SelfT>
	class OnUpdateFuncobj final {
	public:		// types
		using Func = std::function<void(SelfT*, Node*)>;
	private:		// variables
		SelfT* _self = nullptr;
		Func _on_update_func = nullptr;
	public:		// functions
		OnUpdateFuncobj() = default;
		inline OnUpdateFuncobj(SelfT* s_self,
			const Func& s_on_update_func)
			: _self(s_self), _on_update_func(s_on_update_func) {
		}
		GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(OnUpdateFuncobj);
		~OnUpdateFuncobj() = default;

		inline void operator () (Node* node) const {
			_on_update_func(_self, node);
		}
	};

	using NodeMap = std::map<std::string, Node>;
	using KncPair = std::pair<std::string, Node::NoConn>;
private:		// variables
	// The currently-selected `Node`'s key
	std::string _sel_key = "";

	IntVec2 _size_2d = SCREEN_SIZE_2D;
	NodeMap _node_map;
	Vec2<bool> _center = {false, false};
	i32 _tab_amount = 0;
public:		// functions
	Menu() = default;
	Menu(const std::string& s_sel_key, const IntVec2& s_size_2d,
		const NodeMap& s_node_map, Vec2<bool> s_center={false, false},
		i32 s_tab_amount=0);
	Menu(const std::string& s_sel_key, const IntVec2& s_size_2d,
		NodeMap&& s_node_map, Vec2<bool> s_center={false, false},
		i32 s_tab_amount=0);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Menu);
	~Menu() = default;

	inline Node& at(const std::string& key) {
		if (!_node_map.contains(key)) {
			fprintf(stderr, "game_engine::Menu::at(): Internal error.\n");
			//exit(1);
		}

		return _node_map.at(key);
	}
	inline const Node& at(const std::string& key) const {
		if (!_node_map.contains(key)) {
			fprintf(stderr,
				"game_engine::Menu::at() const: Internal error.\n");
			//exit(1);
		}

		return _node_map.at(key);
	}

	inline Node& next_node(const EngineKeyStatus& key_status) {
		return at(next_sel_key(key_status));
	}
	inline const Node& next_node(const EngineKeyStatus& key_status)
		const {
		return at(next_sel_key(key_status));
	}
	inline const std::string& next_sel_key(
		const EngineKeyStatus& key_status
	) const {
		bool did_find = false;
		const std::string& maybe_ret = _inner_next_sel_key(sel_key(),
			key_status, did_find);

		return did_find ? maybe_ret : sel_key();
	}
private:		// functions
	const std::string& _inner_next_sel_key(const std::string& some_sel_key,
		const EngineKeyStatus& key_status, bool& did_find) const;

public:		// functions
	inline std::string tab_amount_str() const {
		return spaces_str(tab_amount() * TAB_SIZE);
	}

	void tick(const EngineKeyStatus& key_status);

	operator MsgLog () const;

	GEN_GETTER_AND_SETTER_BY_CON_REF(sel_key);
	GEN_GETTER_BY_CON_REF(size_2d);
	GEN_GETTER_BY_CON_REF(node_map);
	GEN_GETTER_BY_CON_REF(center);
	GEN_GETTER_BY_VAL(tab_amount);

public:		// static builder functions
	static Node build_start_node(const std::string& down_key);
	static Node build_end_node(const std::string& up_key);

	static KncPair build_text_only_knc_pair(const std::string& key,
		const std::string& s_text);
	static KncPair build_separator_knc_pair(i32 i);
	static KncPair build_spaces_knc_pair(i32 i);

	template<typename SelfT>
	static inline KncPair build_action_button_knc_pair(
		const std::string& key, const std::string& s_text,
		SelfT* self, const std::function<void(SelfT*)>& button_func
	) {
		return {
			key,
			{
				.text=s_text,
				.kind=Node::Kind::ActionButton,
				.data=ActionButtonFuncobj<SelfT>(self, button_func),
				.variable=0x0,
				.on_update_func=nullptr,
			}
		};
	}
	template<typename SelfT>
	static inline KncPair build_check_button_knc_pair(
		const std::string& key, const std::string& s_text, bool s_data,
		SelfT* self,
		const std::function<void(SelfT*, Node*)>& s_on_update_func
	) {
		return {
			key,
			{
				.text=s_text,
				.kind=Node::Kind::CheckButton,
				.data=s_data,
				.variable=0x0,
				.on_update_func=OnUpdateFuncobj<SelfT>(self,
					s_on_update_func),
			}
		};
	}
	template<typename SelfT>
	static inline KncPair build_horiz_picker_knc_pair(
		const std::string& key, const std::string& s_text,
		i32 s_variable, SelfT* self,
		const std::function<void(SelfT*, Node*)>& s_on_update_func
	) {
		return {
			key,
			{
				.text=s_text,
				.kind=Node::Kind::HorizPicker,
				.data=Node::DataValue(),
				.variable=s_variable,
				.on_update_func=OnUpdateFuncobj<SelfT>(self,
					s_on_update_func),
			}
		};
	}

	static NodeMap build_node_map(const std::vector<KncPair>& vec);
};

//class Hud final {
//private:		// variables
//};
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_menu_etc_classes_hpp
