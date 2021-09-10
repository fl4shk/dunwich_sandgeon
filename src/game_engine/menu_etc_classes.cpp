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
void MsgLog::push_back(const DataElem& to_push)
{
	_data.push_back(to_push);
}
void MsgLog::push_back(DataElem&& to_push)
{
	_data.push_back(std::move(to_push));
}

void MsgLog::wrap(size_t row_length)
{
}

void MsgLog::_wrap_back(size_t row_length)
{
}

const std::string
	Menu::BUTTON_STR("(    )"),

	Menu::CHECK_BUTTON_UNCHECKED_STR("[   ]"),
	Menu::CHECK_BUTTON_CHECKED_STR("[ x ]"),

	Menu::HORIZ_PICKER_VAR_LEFT_STR("["),
	Menu::HORIZ_PICKER_VAR_INNER_BLANK_STR("   "),
	Menu::HORIZ_PICKER_VAR_RIGHT_STR("]");

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
