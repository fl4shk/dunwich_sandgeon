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

#ifndef src_game_engine_comp_ui_etc_comp_classes_hpp
#define src_game_engine_comp_ui_etc_comp_classes_hpp

// src/game_engine/comp/ui_etc_comp_classes.hpp

#include "../../misc_includes.hpp"
#include "../font_color_enum.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace comp {
//--------
//static constexpr FgBgColorPair
//	UI_SELECTED_COLOR = FontColor::Red,
//	UI_UNSELECTED_COLOR = FontColor::White;
//
//// A single character.
//class Char final: public ecs::Comp {
//public:		// constants
//	static constexpr FgBgColorPair
//		SELECTED_COLOR = FontColor::Red,
//		UNSELECTED_COLOR = FontColor::White;
//public:		// variables
//	i32 c = ' ';
//public:		// functions
//};

//class Text final: public ecs::Comp {
//public:		// variables
//	std::string str = " ";
//public:		// functions
//	inline Text() = default;
//	inline Text(const std::string& s_str)
//		: str(s_str) {
//	}
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Text);
//	virtual ~Text() = default;
//
//	virtual std::string kind_str() const;
//};
//
//class Button final: public ecs::Comp {
//public:		// constants
//	static const std::string
//		UNSELECTED_STR, SELECTED_STR;
//public:		// types
//	using OnEnableFunc = std::function<void(Button*)>;
//public:		// variables
//	OnEnableFunc on_enable_func = nullptr;
//public:		// functions
//	inline Button() = default;
//	inline Button(const OnEnableFunc& s_on_enable_func)
//		: on_enable_func(s_on_enable_func) {
//	}
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Button);
//	virtual ~Button() = default;
//
//	virtual std::string kind_str();
//};
//
//class CheckButton final: public ecs::Comp {
//public:		// constants
//	static const std::string
//		UNSELECTED_UNCHECKED_STR, SELECTED_UNCHECKED_STR,
//		UNSELECTED_CHECKED_STR, SELECTED_CHECKED_STR;
//public:		// types
//	using OnActFunc = std::function<void(CheckButton*)>;
//public:		// variables
//	bool checked = false;
//	OnActFunc on_check_func = nullptr, on_uncheck_func = nullptr;
//public:		// functions
//	inline CheckButton() = default;
//	inline CheckButton(bool s_checked, const OnActFunc& s_on_check_func,
//		const OnActFunc& s_on_uncheck_func)
//		: checked(s_checked), on_check_func(s_on_check_func),
//		on_uncheck_func(s_on_uncheck_func) {
//	}
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(CheckButton);
//	virtual ~CheckButton() = default;
//
//	virtual std::string kind_str() const;
//};
//--------
} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon


#endif		// src_game_engine_comp_ui_etc_comp_classes_hpp
