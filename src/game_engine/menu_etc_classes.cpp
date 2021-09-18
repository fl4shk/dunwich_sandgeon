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

#include "menu_etc_classes.hpp"
#include <cctype>

namespace dungwich_sandeon
{
namespace game_engine
{
//--------
Rope split_rope_by_whitespace(const Rope& rope)
{
	// Create a new `Rope` that consists of the contents of `rope` split by
	// whatever amount of whitespace characters is between each
	// colored `std::string`. As such, whitespace characters in this
	// new `Rope` are nonexistent.
	Rope ret;

	for (const auto& rope_part: rope)
	{
		auto str_vec = split_str_by_whitespace(rope_part.str);

		for (const auto& str: str_vec)
		{
			ret.push_back(RopePart({.str=str,
				.color_pair=rope_part.color_pair,
				.gs_color_pair=rope_part.gs_color_pair}));
		}
	}

	return ret;
}
RopeDeque wrap_rope(const Rope& rope, size_t row_length)
{
	RopeDeque ret;

	if (rope.size() == 0)
	{
		return ret;
	}

	Rope split_rope(split_rope_by_whitespace(rope));

	if (split_rope.size() == 0)
	{
		return ret;
	}

	size_t
		col = 0,
		prev_col = 0;

	for (size_t i=0; i<split_rope.size(); ++i)
	{
		auto& rope_part = split_rope.at(i);
		const size_t next_col = col + 1u + rope_part.str.size();

		if (col <= prev_col)
		{
			ret.push_back(Rope());
		}
		ret.back().push_back(std::move(rope_part));

		prev_col = col;
		col = (next_col < row_length) ? next_col : 0;
	}

	return ret;
}
//--------
const std::string
	MsgLog::TAB_SPACING_STR(spaces_str(MsgLog::TAB_SPACING_SIZE)),
	MsgLog::WIDGET_SPACING_STR(spaces_str(MsgLog::WIDGET_SPACING_SIZE));

MsgLog::MsgLog(const RopeDeque& s_data, const SizeVec2& s_size_2d)
{
	_size_2d = s_size_2d;

	for (const auto& rope: s_data)
	{
		push_back(rope);
	}
}

void MsgLog::clear()
{
	_data.clear();
}
void MsgLog::pop_front()
{
	_data.pop_front();
}

void MsgLog::push_back(const Rope& to_push, bool do_pop_front)
{
	//_data.push_back(wrap_rope(to_push, size_2d().x));
	auto wrapped = wrap_rope(to_push, size_2d().x);

	for (auto& single_rope: wrapped)
	{
		_data.push_back(std::move(single_rope));

		// I believe there's no need for a `while` loop here.
		if (do_pop_front && (_data.size() >= size_2d().y))
		{
			pop_front();
		}
	}
}

void MsgLog::push_back(const RopePart& to_push, bool do_pop_front)
{
	Rope to_push_rope;
	to_push_rope.push_back(to_push);
	push_back(to_push_rope, do_pop_front);
}
//--------
const std::string
	Menu::WIDGET_BUTTON_STR("(*)"),

	Menu::WIDGET_CHECK_BUTTON_UNCHECKED_STR("[ ]"),
	Menu::WIDGET_CHECK_BUTTON_CHECKED_STR("[x]"),

	Menu::WIDGET_HORIZ_PICKER_LEFT_STR("["),
	Menu::WIDGET_HORIZ_PICKER_INNER_BLANK_STR("   "),
	Menu::WIDGET_HORIZ_PICKER_RIGHT_STR("]");

Menu::Menu(const std::string& s_start_key, const NodeMap& s_node_map)
	: _start_key(s_start_key), _sel_key(s_start_key),
	_node_map(s_node_map)
{
}
Menu::Menu(const std::string& s_start_key, NodeMap&& s_node_map)
	: _start_key(s_start_key), _sel_key(s_start_key),
	_node_map(std::move(s_node_map))
{
}
//--------
} // namespace game_engine
} // namespace dungwich_sandeon
