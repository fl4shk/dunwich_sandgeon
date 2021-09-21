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
Rope split_rope_by_whitespace(const Rope& rope, bool keep_sep)
{
	// Create a new `Rope` that consists of the contents of `rope` split by
	// whatever amount of whitespace characters is between each
	// colored `std::string`. As such, whitespace characters in this
	// new `Rope` are nonexistent.
	Rope ret;

	for (const auto& rope_part: rope)
	{
		auto str_vec = split_str_by_whitespace(rope_part.str, keep_sep);

		for (const auto& str: str_vec)
		{
			ret.push_back(RopePart({.str=str,
				.color_pair=rope_part.color_pair,
				.gs_color_pair=rope_part.gs_color_pair}));
		}
	}

	return ret;
}
RopeDeque wrap_rope(const Rope& rope, size_t row_length, bool keep_sep)
{
	RopeDeque ret;

	if (rope.size() == 0)
	{
		return ret;
	}

	Rope split_rope(split_rope_by_whitespace(rope, keep_sep));

	if (split_rope.size() == 0)
	{
		return ret;
	}

	ret.push_back(Rope());

	size_t col = 0;

	bool added_rope = false;

	for (size_t i=0; i<split_rope.size(); ++i)
	{
		auto& rope_part = split_rope.at(i);

		col += rope_part.str.size();

		if ((!added_rope) && (col > row_length))
		{
			ret.push_back(Rope());
			col = 0;
		}

		added_rope = false;

		ret.back().push_back(std::move(rope_part));
		const size_t j = ret.back().size() - 1;

		if (((i + 1) < split_rope.size())
			&& ((col + split_rope.at(i + 1).str.size()) >= row_length))
		{
			ret.push_back(Rope());
			col = 0;
			added_rope = true;
		}

		if ((!keep_sep) && (col > 0))
		{
			++col;
		}
		//else // if (keep_sep)
		//{
		//	if (!added_rope)
		//	{
		//	}
		//}
	}

	return ret;
}
//--------
const std::string
	MsgLog::TAB_SPACING_STR(spaces_str(MsgLog::TAB_SPACING_SIZE)),

	MsgLog::WIDGET_SELECTED_SPACING_STR(spaces_str
		(MsgLog::WIDGET_SELECTED_SPACING_SIZE)),
	MsgLog::WIDGET_SPACING_STR(spaces_str(MsgLog::WIDGET_SPACING_SIZE));

MsgLog::MsgLog(const RopeDeque& s_data, const SizeVec2& s_size_2d,
	bool s_keep_sep)
{
	_size_2d = s_size_2d;
	_keep_sep = s_keep_sep;

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
	//_data.push_back(wrap_rope(to_push, size_2d().x, _keep_sep));
	auto wrapped = wrap_rope(to_push, size_2d().x, _keep_sep);

	for (auto& single_rope: wrapped)
	{
		_data.push_back(std::move(single_rope));

		while (do_pop_front && (_data.size() > size_2d().y))
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
	Menu::WIDGET_SELECTED_STR("=> "),

	Menu::WIDGET_BUTTON_STR("(*)   "),

	Menu::WIDGET_CHECK_BUTTON_UNCHECKED_STR("[ ]   "),
	Menu::WIDGET_CHECK_BUTTON_CHECKED_STR("[x]   "),

	Menu::WIDGET_HORIZ_PICKER_LEFT_STR("["),
	Menu::WIDGET_HORIZ_PICKER_INNER_BLANK_STR("   "),
	Menu::WIDGET_HORIZ_PICKER_RIGHT_STR("] ");

const std::string
	Menu::START_NODE_KEY("<start>"),
	Menu::END_NODE_KEY("<end>");

Menu::Node::Node()
{
}

// This constructor takes an `std::monostate` for `s_data`
Menu::Node::Node(const std::string& s_text, Kind s_kind, u32 s_flags,
	const std::string& s_up, const std::string& s_down,
	std::monostate s_data, int s_variable,
	const OnUpdateFunc& s_on_update_func)
	: text(s_text),
	kind(s_kind),
	flags(s_flags),
	up(s_up), down(s_down),
	data(s_data),
	variable(s_variable),
	on_update_func(s_on_update_func)
{
}

// This constructor takes a `DataValue` for `s_data`
Menu::Node::Node(const std::string& s_text, Kind s_kind, u32 s_flags,
	const std::string& s_up, const std::string& s_down,
	const DataValue& s_data, int s_variable,
	const OnUpdateFunc& s_on_update_func)
	: text(s_text),
	kind(s_kind),
	flags(s_flags),
	up(s_up), down(s_down),
	data(s_data),
	variable(s_variable),
	on_update_func(s_on_update_func)
{
}

// This constructor takes a `DataActionFunc` for `s_data`
Menu::Node::Node(const std::string& s_text, Kind s_kind, u32 s_flags,
	const std::string& s_up, const std::string& s_down,
	const DataActionFunc& s_data, int s_variable,
	const OnUpdateFunc& s_on_update_func)
	: text(s_text),
	kind(s_kind),
	flags(s_flags),
	up(s_up), down(s_down),
	data(s_data),
	variable(s_variable),
	on_update_func(s_on_update_func)
{
}

//// This constructor takes a `DataActionParamFunc` for `s_data`
//Menu::Node::Node(const std::string& s_text, Kind s_kind, u32 s_flags,
//	const std::string& s_up, const std::string& s_down,
//	const DataActionParamFunc& s_data, int s_variable,
//	const OnUpdateFunc& s_on_update_func)
//	: text(s_text),
//	kind(s_kind),
//	flags(s_flags),
//	up(s_up), down(s_down),
//	data(s_data),
//	variable(s_variable),
//	on_update_func(s_on_update_func)
//{
//}
Menu::Node::~Node()
{
}

std::string Menu::Node::widget_horiz_picker_str() const
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

Menu::Menu(const std::string& s_sel_key, const SizeVec2& s_size_2d,
	const NodeMap& s_node_map)
	: _sel_key(s_sel_key), _size_2d(s_size_2d), _node_map(s_node_map)
{
}
Menu::Menu(const std::string& s_sel_key, const SizeVec2& s_size_2d,
	NodeMap&& s_node_map)
	: _sel_key(s_sel_key), _size_2d(s_size_2d),
	_node_map(std::move(s_node_map))
{
}

Menu::operator MsgLog() const
{
	RopeDeque ret_data;

	for (const std::string* key=&at(Menu::START_NODE_KEY).down;
		(*key)!=Menu::END_NODE_KEY;
		key=&at(*key).down)
	{
		const FgBgColorPair COLOR_PAIR
			= ((*key) != _sel_key)
			? WIDGET_UNSELECTED_COLOR_PAIR
			: WIDGET_SELECTED_COLOR_PAIR;
		const std::string CURR_WIDGET_SELECTED_STR
			= ((*key) != _sel_key)
			? MsgLog::WIDGET_SELECTED_SPACING_STR
			: WIDGET_SELECTED_STR;
		const auto& NODE = at(*key);

		switch (NODE.kind)
		{
		//--------
		case Node::Kind::Start:
			fprintf(stderr,
				"game_engine::Menu::operator MsgLog(): Internal error.\n");
			exit(1);
			break;
		case Node::Kind::End:
			fprintf(stderr,
				"game_engine::Menu::operator MsgLog(): Internal error.\n");
			exit(1);
			break;

		case Node::Kind::TextOnly:
			ret_data.push_back(Rope
				({
					RopePart
					({
						.str=sconcat(CURR_WIDGET_SELECTED_STR,
							MsgLog::WIDGET_SPACING_STR, NODE.text), 
						.color_pair=COLOR_PAIR,
						.gs_color_pair=COLOR_PAIR
					})
				}));
			break;

		case Node::Kind::ActionButton:
			ret_data.push_back(Rope
				({
					RopePart
					({
						.str=sconcat(CURR_WIDGET_SELECTED_STR,
							Menu::WIDGET_BUTTON_STR, NODE.text), 
						.color_pair=COLOR_PAIR,
						.gs_color_pair=COLOR_PAIR
					})
				}));
			break;
		//case Node::Kind::ActionButtonParam:
		//	break;

		case Node::Kind::ExitButton:
			break;

		case Node::Kind::HorizPicker:
			ret_data.push_back(Rope
				({
					RopePart
					({
						.str=sconcat(CURR_WIDGET_SELECTED_STR,
							NODE.widget_horiz_picker_str(), NODE.text), 
						.color_pair=COLOR_PAIR,
						.gs_color_pair=COLOR_PAIR
					})
				}));
			break;
		//case Node::Kind::HorizPickerWrap:
		//	break;

		default:
			fprintf(stderr,
				"game_engine::Menu::operator MsgLog(): "
				"Internal error.\n");
			exit(1);
			break;
		//--------
		}
	}

	return MsgLog(ret_data, size_2d(), true);
}
//--------
} // namespace game_engine
} // namespace dungwich_sandeon
