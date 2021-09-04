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

#ifndef src_game_engine_comp_ui_etc_comp_classes_hpp
#define src_game_engine_comp_ui_etc_comp_classes_hpp

// src/game_engine/comp/ui_etc_comp_classes.hpp

#include "../../misc_includes.hpp"
#include "../font_color_enum.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace comp
{

class Text final: public ecs::Comp
{
public:		// variables
	std::string str = " "s;
public:		// functions
	inline Text() = default;
	inline Text(const std::string& s_str)
		: str(s_str)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Text);
	virtual ~Text() = default;

	virtual std::string kind_str() const;
};

class CheckButton final: public ecs::Comp
{
public:		// constants
	static constexpr FgBgColorPair DRAWABLE_DATA_COLOR_PAIR
		= FontColor::Red;
	static const std::string
		UNCHECKED_STR, CHECKED_STR;
public:		// variables
	bool checked = false;
public:		// functions
	inline CheckButton() = default;
	inline CheckButton(bool s_checked)
		: checked(s_checked)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(CheckButton);
	virtual ~CheckButton() = default;

	virtual std::string kind_str() const;
};

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon


#endif		// src_game_engine_comp_ui_etc_comp_classes_hpp
