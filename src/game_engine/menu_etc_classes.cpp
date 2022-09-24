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

#include "menu_etc_classes.hpp"
#include "engine_class.hpp"
#include <cctype>

namespace dunwich_sandgeon
{
namespace game_engine
{
//--------
RopePart::RopePart(const binser::Value& bv)
{
	MEMB_LIST_ROPE_PART(BINSER_MEMB_DESERIALIZE);
}
RopePart::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_ROPE_PART(BINSER_MEMB_SERIALIZE);

	return ret;
}
RopePart& RopePart::operator = (const binser::Value& bv)
{
	*this = RopePart(bv);

	return *this;
}
std::ostream& operator << (std::ostream& os, const RopePart& rope_part)
{
	return osprintout(os,
		rope_part.str.size(), " ",
		"\"", rope_part.str, "\"");
}

std::ostream& operator << (std::ostream& os, const Rope& rope)
{
	for (i32 i=0; i<i32(rope.size()); ++i)
	{
		os << rope.at(i);

		if ((i + 1) < i32(rope.size()))
		{
			os << "; ";
		}
	}

	return os;
}
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

		//printout("split_rope_by_whitespace(): ",
		//	"\"", rope_part.str, "\"", "\n");
		for (const auto& str: str_vec)
		{
			//printout(str.size(), " ",
			//	"\"", str, "\"; ");
			ret.push_back(RopePart({.str=str,
				.color_pair=rope_part.color_pair,
				.gs_color_pair=rope_part.gs_color_pair}));
		}
		//printout("\n");
	}
	//printout("\n");

	return ret;
}
RopeDeque wrap_rope(const Rope& rope, i32 row_length, bool keep_sep)
{
	RopeDeque ret;

	if (rope.size() == 0)
	{
		return ret;
	}

	Rope split_rope(split_rope_by_whitespace(rope, keep_sep));

	//printout("wrap_rope():\n");
	//for (const auto& rope_part: split_rope)
	//{
	//	printout(rope_part.str.size(), " ",
	//		"\"", rope_part.str, "\"; ");
	//}
	//printout("\n");

	//printout("row_length: ", row_length, "\n");

	if (split_rope.size() == 0)
	{
		return ret;
	}

	ret.push_back(Rope());

	i32 col = 0;

	bool added_rope = false;

	for (i32 i=0; i<i32(split_rope.size()); ++i)
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
		//const i32 j = ret.back().size() - 1;

		if (((i + 1) < i32(split_rope.size()))
			&& ((col + i32(split_rope.at(i + 1).str.size())) > row_length))
		{
			//printout("add rope 2: ",
			//	col, "; ", i, "\n",
			//	rope, "\n");

			ret.push_back(Rope());
			col = 0;
			added_rope = true;
		}

		if ((!keep_sep) && (col > 0))
		{
			//printout("(!keep_sep) && (col > 0)\n");
			++col;
		}
	}

	//printout("wrap_rope() (continued):\n");
	//for (const auto& rope: ret)
	//{
	//}

	return ret;
}
//--------
const std::string
	MsgLog::WIDGET_SELECTED_SPACING_STR(spaces_str
		(MSG_LOG_WIDGET_SELECTED_SPACING_SIZE)),
	MsgLog::WIDGET_SPACING_STR(spaces_str(MSG_LOG_WIDGET_SPACING_SIZE));

//const i32
//	MsgLog::DEFAULT_INTERNAL_HEIGHT = SCREEN_SIZE_2D.y;

MsgLog::MsgLog(const RopeDeque& s_data, i32 s_internal_height,
	const IntVec2& s_window_size_2d, Vec2<bool> s_center,
	bool s_keep_sep)
{
	_internal_height = s_internal_height;
	_window_size_2d = s_window_size_2d;
	_center = s_center;
	_keep_sep = s_keep_sep;

	for (const auto& rope: s_data)
	{
		push_back(rope);
	}
}
MsgLog::MsgLog(const binser::Value& bv)
{
	MEMB_LIST_MSG_LOG(BINSER_MEMB_DESERIALIZE);
}

MsgLog::operator binser::Value () const
{
	binser::Value ret;

	MEMB_LIST_MSG_LOG(BINSER_MEMB_SERIALIZE);

	return ret;
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
	//_data.push_back(wrap_rope(to_push, window_size_2d().x, _keep_sep));
	auto wrapped = wrap_rope(to_push, window_size_2d().x, _keep_sep);

	for (auto& single_rope: wrapped)
	{
		_data.push_back(std::move(single_rope));

		//while (do_pop_front && (data().size() > window_size_2d().y))
		while (do_pop_front && (i32(data().size()) > internal_height()))
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

const std::string
	Menu::TAB_STR(spaces_str(Menu::TAB_SIZE));


Menu::Node::Node()
{
}

Menu::Node::Node(const NoConn& s_most_args, const std::string& s_up,
	const std::string& s_down)
{
	text = s_most_args.text;
	kind = s_most_args.kind;
	up = s_up;
	down = s_down;
	data = s_most_args.data;
	variable = s_most_args.variable;
	on_update_func = s_most_args.on_update_func;
}
Menu::Node::Node(const CtorArgs& ctor_args)
{
	*this = Node(ctor_args.no_conn, ctor_args.up, ctor_args.down);
}
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
		i32 i;
		for (i=0; i<i32(DATA_STR.size()); ++i)
		{
			ret += DATA_STR.at(i);
		}
		for (; i<i32(WIDGET_HORIZ_PICKER_INNER_BLANK_STR.size()); ++i)
		{
			ret += " ";
		}
	}
	ret += WIDGET_HORIZ_PICKER_RIGHT_STR;

	return ret;
}
std::string Menu::Node::widget_check_button_str() const
{
	return (!std::get<bool>(data))
		? WIDGET_CHECK_BUTTON_UNCHECKED_STR
		: WIDGET_CHECK_BUTTON_CHECKED_STR;
}

Menu::Menu(const std::string& s_sel_key, const IntVec2& s_size_2d,
	const NodeMap& s_node_map, Vec2<bool> s_center, i32 s_tab_amount)
	: _sel_key(s_sel_key), _size_2d(s_size_2d), _node_map(s_node_map),
	_center(s_center), _tab_amount(s_tab_amount)
{
}
Menu::Menu(const std::string& s_sel_key, const IntVec2& s_size_2d,
	NodeMap&& s_node_map, Vec2<bool> s_center, i32 s_tab_amount)
	: _sel_key(s_sel_key), _size_2d(s_size_2d),
	_node_map(std::move(s_node_map)), _center(s_center),
	_tab_amount(s_tab_amount)
{
}

const std::string& Menu::_inner_next_sel_key
	(const std::string& some_sel_key, const EngineKeyStatus& key_status,
	bool& did_find) const
{
	const auto& curr_node = at(some_sel_key);

	auto temp_func = [&](const std::string& up_or_down)
		-> const std::string&
	{
		//const auto& temp_sel_key = _inner_next_sel_key(up_or_down,
		//	key_status);

		//const auto& temp_node = at(temp_sel_key);

		const auto& temp_node = at(up_or_down);

		if ((temp_node.kind == Node::Kind::ActionButton)
			|| (temp_node.kind == Node::Kind::CheckButton)
			|| (temp_node.kind == Node::Kind::HorizPicker))
		{
			did_find = true;
			return up_or_down;
		}
		else
		{
			return _inner_next_sel_key(up_or_down, key_status, did_find);
		}
	};

	if (key_status.key_just_went_down(KeyKind::UpL)
		&& key_status.key_up_now(KeyKind::DownL))
	{
		if (curr_node.up == Menu::START_NODE_KEY)
		{
			return some_sel_key;
		}
		else
		{
			return temp_func(curr_node.up);
		}
	}
	else if (key_status.key_just_went_down(KeyKind::DownL)
		&& key_status.key_up_now(KeyKind::UpL))
	{
		if (curr_node.down == Menu::END_NODE_KEY)
		{
			return some_sel_key;
		}
		else
		{
			return temp_func(curr_node.down);
		}
	}
	else
	{
		return some_sel_key;
	}
}
void Menu::tick(const EngineKeyStatus& key_status)
{
	set_sel_key(next_sel_key(key_status));

	Node& sel_node = at(sel_key());

	switch (sel_node.kind)
	{
	//--------
	case Node::Kind::ActionButton:
		if (!std::holds_alternative<Node::DataActionFunc>(sel_node.data))
		{
			fprintf(stderr,
				"game_engine::Menu::tick() ActionButton: "
				"Internal error.\n");
			exit(1);
		}

		if (key_status.key_just_went_down(KeyKind::DownR))
		{
			std::get<Node::DataActionFunc>(sel_node.data)();

			if (sel_node.on_update_func)
			{
				sel_node.on_update_func(&sel_node);
			}
		}
		break;

	case Node::Kind::CheckButton:
		if (!std::holds_alternative<bool>(sel_node.data))
		{
			fprintf(stderr,
				"game_engine::Menu::tick() CheckButton: "
				"Internal error.\n");
			exit(1);
		}

		if (key_status.key_just_went_down(KeyKind::DownR))
		{
			auto& data = std::get<bool>(sel_node.data);
			data = !data;

			if (sel_node.on_update_func)
			{
				sel_node.on_update_func(&sel_node);
			}
		}
		break;

	case Node::Kind::HorizPicker:
		if (!std::holds_alternative<Node::DataValue>(sel_node.data))
		{
			fprintf(stderr,
				"game_engine::Menu::tick() HorizPicker: "
				"Internal error.\n");
			exit(1);
		}

		if (key_status.key_just_went_down(KeyKind::LeftL)
			&& key_status.key_up_now(KeyKind::RightL))
		{
			auto& value = std::get<Node::DataValue>(sel_node.data);
			const i32 temp_value = value() - 1;

			value.back_up_and_update
			(
				(temp_value < 0) ? sel_node.variable : temp_value
			);

			if (sel_node.on_update_func)
			{
				sel_node.on_update_func(&sel_node);
			}
		}
		if (key_status.key_just_went_down(KeyKind::RightL)
			&& key_status.key_up_now(KeyKind::LeftL))
		{
			auto& value = std::get<Node::DataValue>(sel_node.data);
			const i32 temp_value = value() + 1;

			value.back_up_and_update
			(
				(temp_value > sel_node.variable) ? 0 : temp_value
			);

			if (sel_node.on_update_func)
			{
				sel_node.on_update_func(&sel_node);
			}
		}
		break;

	default:
		// Don't need to do anything in this case.
		break;
	//--------
	}
}

Menu::operator MsgLog() const
{
	RopeDeque ret_data;

	//printout("game_engine::Menu::operator MsgLog(): ",
	//	MsgLog::WIDGET_SELECTED_SPACING_STR.size(), " ",
	//	"\"", MsgLog::WIDGET_SELECTED_SPACING_STR, "\"; ",
	//	WIDGET_SELECTED_STR.size(), " ",
	//	"\"", WIDGET_SELECTED_STR, "\"", "\n");

	for (const std::string* key=&at(Menu::START_NODE_KEY).down;
		*key!=Menu::END_NODE_KEY;
		key=&at(*key).down)
	{
		const FgBgColorPair COLOR_PAIR
			= (*key != _sel_key)
			? WIDGET_UNSELECTED_COLOR_PAIR
			: WIDGET_SELECTED_COLOR_PAIR;
		const std::string CURR_WIDGET_SELECTED_STR
			= (*key != _sel_key)
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
						.str=sconcat(tab_amount_str(), NODE.text),
						//.color_pair=COLOR_PAIR,
						.color_pair=TEXT_ONLY_COLOR_PAIR,
						.gs_color_pair=TEXT_ONLY_GS_COLOR_PAIR
					}),
				}));
			break;

		case Node::Kind::TextOnlyWithLeadingSpaces:
			ret_data.push_back(Rope
				({
					RopePart
					({
						.str=sconcat(tab_amount_str(),
							spaces_str(CURR_WIDGET_SELECTED_STR.size()),
							MsgLog::WIDGET_SPACING_STR, NODE.text),
						.color_pair=TEXT_ONLY_COLOR_PAIR,
						.gs_color_pair=TEXT_ONLY_GS_COLOR_PAIR
					}),
				}));
			break;

		case Node::Kind::ActionButton:
			ret_data.push_back(Rope
				({
					RopePart
					({
						.str=sconcat(tab_amount_str(),
							CURR_WIDGET_SELECTED_STR,
							Menu::WIDGET_BUTTON_STR, NODE.text),
						//.str=sconcat(CURR_WIDGET_SELECTED_STR,
						//	Menu::WIDGET_BUTTON_STR, "Z"),
						.color_pair=COLOR_PAIR,
						.gs_color_pair=COLOR_PAIR
					}),
				}));
			break;
		//case Node::Kind::ActionButtonParam:
		//	break;

		//case Node::Kind::ExitButton:
		//	break;

		case Node::Kind::HorizPicker:
			ret_data.push_back(Rope
				({
					RopePart
					({
						.str=sconcat(tab_amount_str(),
							CURR_WIDGET_SELECTED_STR,
							NODE.widget_horiz_picker_str(), NODE.text),
						.color_pair=COLOR_PAIR,
						.gs_color_pair=COLOR_PAIR
					}),
				}));
			break;
		//case Node::Kind::HorizPickerWrap:
		//	break;

		case Node::Kind::CheckButton:
			ret_data.push_back(Rope
				({
					RopePart
					({
						.str=sconcat(tab_amount_str(),
							CURR_WIDGET_SELECTED_STR,
							NODE.widget_check_button_str(), NODE.text),
						.color_pair=COLOR_PAIR,
						.gs_color_pair=COLOR_PAIR,
					}),
				}));
			break;

		default:
			fprintf(stderr,
				"game_engine::Menu::operator game_engine::MsgLog(): "
				"Internal error.\n");
			exit(1);
			break;
		//--------
		}
	}

	MsgLog ret(ret_data, MsgLog::DEFAULT_INTERNAL_HEIGHT, size_2d(),
		center(), true);

	//for (i32 j=0; j<ret.data().size(); ++j)
	//{
	//	const auto& ROPE = ret.data().at(j);

	//	for (i32 i=0; i<ROPE.size(); ++i)
	//	{
	//		printout(ROPE.at(i).str.size(), " ",
	//			"\"", ROPE.at(i).str, "\"; ");
	//	}
	//	printout("\n");
	//}

	//MsgLog ret(ret_data, MsgLog::DEFAULT_INTERNAL_HEIGHT, size_2d(),
	//	center(), center().x);
	//MsgLog ret(ret_data, MsgLog::DEFAULT_INTERNAL_HEIGHT, size_2d(),
	//	center(), !center().x);
	//ret.set_scroll(1);
	return ret;
}

auto Menu::build_start_node(const std::string& down_key) -> Node
{
	return Node
	(
		START_NODE_KEY,		// text
		Node::Kind::Start,	// kind
		std::monostate(),	// data
		0x0,				// variable
		nullptr,				// on_update_func
		"", down_key		// where
	);
}
auto Menu::build_end_node(const std::string& up_key) -> Node
{
	return Node
	(
		END_NODE_KEY,		// text
		Node::Kind::End,	// kind
		std::monostate(),	// data
		0x0,				// variable
		nullptr,			// on_update_func
		up_key, ""			// where
	);
}


auto Menu::build_text_only_knc_pair(const std::string& key,
	const std::string& s_text) -> KncPair 
{
	return
		{key, {.text=s_text, .kind=Menu::Node::Kind::TextOnly}};
}
auto Menu::build_separator_knc_pair(i32 i) -> KncPair
{
	return build_text_only_knc_pair(sconcat("<separator[", i, "]>"),
		"================");
}
auto Menu::build_spaces_knc_pair(i32 i) -> KncPair 
{
	return build_text_only_knc_pair(sconcat("<blank[", i, "]>"), " ");
}
auto Menu::build_node_map(const std::vector<KncPair>& vec)-> NodeMap 
{
	NodeMap ret;

	ret[START_NODE_KEY] = build_start_node(vec.front().first);
	ret[END_NODE_KEY] = build_end_node(vec.back().first);

	for (i32 i=0; i<i32(vec.size()); ++i)
	{
		std::string s_up, s_down;

		if (i == 0)
		{
			s_up = START_NODE_KEY;
		}
		else // if (i > 0)
		{
			s_up = vec.at(i - 1).first;

			if (s_up == START_NODE_KEY)
			{
				fprintf(stderr,
					"game_engine::Menu::build_node_map(): "
					"`s_up == START_NODE_KEY` Internal error.\n");
				exit(1);
			}
			else if (s_up == END_NODE_KEY)
			{
				fprintf(stderr,
					"game_engine::Menu::build_node_map(): "
					"`s_up == END_NODE_KEY` Internal error.\n");
				exit(1);
			}
		}

		if ((i + 1) == i32(vec.size()))
		{
			s_down = END_NODE_KEY;
		}
		else // if ((i + 1) < vec.size())
		{
			s_down = vec.at(i + 1).first;

			if (s_down == START_NODE_KEY)
			{
				fprintf(stderr,
					"game_engine::Menu::build_node_map(): "
					"`s_down == START_NODE_KEY` Internal error.\n");
				exit(1);
			}
			else if (s_down == END_NODE_KEY)
			{
				fprintf(stderr,
					"game_engine::Menu::build_node_map(): "
					"`s_down == END_NODE_KEY` Internal error.\n");
				exit(1);
			}
		}

		if (ret.contains(vec.at(i).first))
		{
			fprintf(stderr,
				"game_engine::Menu::build_node_map(): "
				"`ret.contains(%s)` Internal error.\n",
				vec.at(i).first.c_str());
			exit(1);
		}

		ret[vec.at(i).first] = Node(vec.at(i).second, s_up, s_down);
	}

	//if (vec.back().first == "exit_wo_save")
	//{
	//	printout("Menu::build_node_map() start\n");

	//	for (std::string key=ret.at(START_NODE_KEY).down;
	//		key!=END_NODE_KEY;
	//		key=ret.at(key).down)
	//	{
	//		printout("\"", key, "\"; ",
	//			"up: \"", ret.at(key).up, "\"; ",
	//			"down: \"", ret.at(key).down, "\"", "\n");
	//	}

	//	printout("Menu::build_node_map() end\n");
	//}

	return ret;
}
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon
