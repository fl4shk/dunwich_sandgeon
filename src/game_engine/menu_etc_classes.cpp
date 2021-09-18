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

const std::string
	MsgLog::TAB_SPACING_STR(MsgLog::spaces_str(MsgLog::TAB_SPACING_SIZE)),
	MsgLog::WIDGET_SPACING_STR(MsgLog::spaces_str
		(MsgLog::WIDGET_SPACING_SIZE));

MsgLog::MsgLog(const Data& s_data)
	: _data(s_data)
{
}
MsgLog::MsgLog(Data&& s_data)
	: _data(s_data)
{
}

void MsgLog::pop_front()
{
	_data.pop_front();
}
void MsgLog::push_back(const Rope& to_push)
{
	_data.push_back(to_push);
}
void MsgLog::push_back(Rope&& to_push)
{
	_data.push_back(std::move(to_push));
}

void MsgLog::wrap(size_t row_length)
{
	for (auto& rope: _data)
	{
		wrap_rope(rope, row_length);
	}
}

void MsgLog::wrap_rope(Rope& rope, size_t row_length)
{
	std::array<Rope, 2> temp_rope_arr;

	for (const auto& rope_part: rope)
	{
		for (size_t i=0; i<rope_part.str.size(); ++i)
		{
			auto c = rope_part.str.at(i);

			while (std::isspace(c) && (i < rope_part.str.size()))
			{
				++i;
				c = rope_part.str.at(i);
			}

			bool did_first_push_back = false;

			while ((!std::isspace(c)) && (i < rope_part.str.size()))
			{
				if (!did_first_push_back)
				{
					did_first_push_back = true;
					temp_rope_arr.at(0).push_back(RopePart(c,
						rope_part.color_pair, rope_part.gs_color_pair));
				}
				else // if (did_first_push_back)
				{
					temp_rope_arr.at(0).back().str += c;
				}

				++i;
				c = rope_part.str.at(i);
			}
		}
	}

	rope = std::move(temp_rope_arr.at(1));
}

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

} // namespace game_engine
} // namespace dungwich_sandeon
