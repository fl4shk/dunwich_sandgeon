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

#include "window_class.hpp"
#include "engine_class.hpp"
#include "menu_etc_classes.hpp"
#include "comp/drawable_data_map.hpp"

//#include <queue>

namespace dunwich_sandgeon
{
namespace game_engine
{
//--------
//const IntVec2 Window::SCREEN_SIZE_2D(82, 62);
//const IntVec2 Window::SCREEN_SIZE_2D(60, 50);

const std::string
	Window::BORDER_CORNER_KIND_STR("game_engine::Window::BorderCorner"),
	Window::BORDER_HORIZ_KIND_STR("game_engine::Window::BorderHoriz"),
	Window::BORDER_VERT_KIND_STR("game_engine::Window::BorderVert"),
	Window::BLANK_KIND_STR("game_engine::Window::Blank");
//--------
const comp::Drawable::Data& Window::BORDER_CORNER_DRAWABLE_DATA()
{
	return comp::drawable_data_map().at(BORDER_CORNER_KIND_STR);
}
const comp::Drawable::Data& Window::BORDER_HORIZ_DRAWABLE_DATA()
{
	return comp::drawable_data_map().at(BORDER_HORIZ_KIND_STR);
}
const comp::Drawable::Data& Window::BORDER_VERT_DRAWABLE_DATA()
{
	return comp::drawable_data_map().at(BORDER_VERT_KIND_STR);
}
const comp::Drawable::Data& Window::BLANK_DRAWABLE_DATA()
{
	return comp::drawable_data_map().at(BLANK_KIND_STR);
}

Window::Window()
{
}
//Window::Window(const IntVec2& s_some_pos, const IntVec2& s_some_size_2d,
//	bool with_border)
//	: _pos(s_some_pos
//		- (!with_border ? IntVec2(1, 1) : IntVec2(0, 0))),
//	_drawable_data_v2d
//	(
//		s_some_size_2d.y + (!with_border ? 2 : 0),
//		std::vector<DrawData>
//		(
//			s_some_size_2d.x + (!with_border ? 2 : 0)
//		)
//	)
//	//_cleared_ent_id_v2d
//	//(
//	//	s_some_size_2d.y
//	//		+ (!with_border ? 2 : 0),
//	//	ecs::EntIdVec
//	//	(
//	//		s_some_size_2d.x
//	//			+ (!with_border ? 2 : 0),
//	//		ecs::ENT_NULL_ID
//	//	)
//	//)
//{
//	//init_set_border();
//	//_ent_id_v2d = _cleared_ent_id_v2d;
//}
//Window::Window(const IntVec2& s_some_pos, const IntVec2& s_some_end_pos,
//	bool with_border)
//	: _pos(s_some_pos
//		- (!with_border ? IntVec2(1, 1) : IntVec2(0, 0))),
//	_drawable_data_v2d
//	(
//		s_some_end_pos.y - s_some_pos.y + 1
//			+ (!with_border ? 2 : 0),
//		std::vector<DrawData>
//		(
//			s_some_end_pos.x - s_some_pos.x + 1
//				+ (!with_border ? 2 : 0)
//		)
//	)
//	//_cleared_ent_id_v2d
//	//(
//	//	s_some_end_pos.y - s_some_pos.y + 1
//	//		+ (!with_border ? 2 : 0),
//	//	ecs::EntIdVec
//	//	(
//	//		s_some_end_pos.x - s_some_pos.x + 1
//	//			+ (!with_border ? 2 : 0),
//	//		ecs::ENT_NULL_ID
//	//	)
//	//)
//{
//	//init_set_border();
//	//_ent_id_v2d = _cleared_ent_id_v2d;
//}
Window::Window(const IntVec2& s_some_pos,
	const IntVec2& s_some_size_2d_or_end_pos, bool use_end_pos,
	bool with_border)
	: _pos(s_some_pos
		- (!with_border ? IntVec2(1, 1) : IntVec2(0, 0))),
	_drawable_data_v2d
	(
		s_some_size_2d_or_end_pos.y
			+ (use_end_pos ? (-s_some_pos.y + 1) : 0)
			+ (!with_border ? 2 : 0),
		std::vector<DrawData>
		(
			s_some_size_2d_or_end_pos.x
				+ (use_end_pos ? (-s_some_pos.x + 1) : 0)
				+ (!with_border ? 2 : 0)
		)
	)
{
}
Window::~Window()
{
}

//Window::operator binser::Value () const
//{
//	binser::Value ret;
//
//	MEMB_SER_LIST_WINDOW(BINSER_MEMB_SERIALIZE);
//
//	return ret;
//}

//void Window::deserialize(const binser::Value& bv)
//{
//	//printout("Window::deserialize() before: ", engine == nullptr, "\n");
//	MEMB_SER_LIST_WINDOW(BINSER_MEMB_DESERIALIZE);
//	//_ent_id_v2d = _cleared_ent_id_v2d;
//	//printout("Window::deserialize() after: ", engine == nullptr, "\n");
//}

void Window::clear()
{
	for (int j=0; j<with_border_size_2d().y; ++j)
	{
		for (int i=0; i<with_border_size_2d().x; ++i)
		{
			const IntVec2 index(i, j);
			if ((j == 0) || (j == with_border_size_2d().y - 1))
			{
				if ((i == 0) || (i == with_border_size_2d().x - 1))
				{
					with_border_drawable_data_at(index)
						= BORDER_CORNER_DRAWABLE_DATA();
				}
				else
				{
					with_border_drawable_data_at(index)
						= BORDER_HORIZ_DRAWABLE_DATA();
				}
			}
			else if ((i == 0) || (i == with_border_size_2d().x - 1))
			{
				with_border_drawable_data_at(index)
					= BORDER_VERT_DRAWABLE_DATA();
			}
			else
			{
				with_border_drawable_data_at(index)
					= BLANK_DRAWABLE_DATA();
			}
		}
	}
}

void Window::draw(const Window& src, bool leave_corner)
{
	IntVec2 src_pos;
	for (src_pos.y=0;
		src_pos.y<i32(src.with_border_size_2d().y);
		++src_pos.y)
	{
		for (src_pos.x=0;
			src_pos.x<i32(src.with_border_size_2d().x);
			++src_pos.x)
		{
			const auto& SRC_DRAWABLE_DATA
				= src.with_border_drawable_data_at(src_pos);
			const auto DST_POS = src.pos() + src_pos;
			auto& dst_drawable_data = with_border_drawable_data_at(DST_POS);

			if (!leave_corner
				|| (dst_drawable_data != BORDER_CORNER_DRAWABLE_DATA()))
			{
				dst_drawable_data = SRC_DRAWABLE_DATA;
			}
		}
	}
}

void Window::draw(const Menu& menu)
{
	draw(static_cast<MsgLog>(menu));
}

void Window::draw(const MsgLog& msg_log)
{
	IntVec2 temp_pos(0, 0);

	//if (msg_log.center().y
	//	&& (msg_log.data().size() < msg_log.window_size_2d().y))
	if (msg_log.center().y
		&& (msg_log.data().size() <= msg_log.window_size_2d().y))
	{
		temp_pos.y
			= ((msg_log.window_size_2d().y - msg_log.data().size()) / 2);
	}

	for (uint j=msg_log.scroll();
		((j - msg_log.scroll()) < msg_log.window_size_2d().y)
			&& (j < msg_log.internal_height())
			&& (j < msg_log.data().size());
		++j, ++temp_pos.y)
	{
		const auto& ROPE = msg_log.data().at(j);

		uint rope_size = 0;

		for (uint i=0; i<ROPE.size(); ++i)
		{
			rope_size += ROPE.at(i).str.size();

			if ((!msg_log.keep_sep()) && ((i + 1) < ROPE.size()))
			{
				++rope_size;
			}
		}
		//printout("rope_size: ", rope_size, " ", 
		//	//std::string("This is a red str. asdf asdf asdf asdf").size(),
		//	"\n");
		//for (uint i=0; i<ROPE.size(); ++i)
		//{
		//	uint temp_rope_size = ROPE.at(i).str.size();

		//	if ((!msg_log.keep_sep()) && ((i + 1) < ROPE.size()))
		//	{
		//		++temp_rope_size;
		//	}

		//	printout(temp_rope_size, " ",
		//		"\"", ROPE.at(i).str, "\"", "; ");
		//}
		//printout("\n\n");

		//if (msg_log.center().x
		//	&& ((rope_size - 1) < msg_log.window_size_2d().x))
		if (msg_log.center().x
			&& (rope_size <= msg_log.window_size_2d().x))
		{
			//temp_pos.x 
			//	= ((msg_log.window_size_2d().x - rope_size) / 2) - 1;
			temp_pos.x 
				= ((msg_log.window_size_2d().x - rope_size) / 2);
		}
		else
		{
			temp_pos.x = 0;
		}

		auto draw_at_temp_pos
			= [this, &temp_pos](const comp::Drawable::Data& drawable_data)
			-> void
		{
			//const auto DST_ENT_ID = ent_id_at(temp_pos);
			//auto dst = engine->ecs_engine
			//	.casted_comp_at<comp::Drawable>(DST_ENT_ID, file_num());

			//dst->set_data(drawable_data);
			drawable_data_at(temp_pos) = drawable_data;
		};

		for (const auto& rope_part: ROPE)
		{
			for (uint i=0; i<rope_part.str.size(); ++i, ++temp_pos.x)
			{
				draw_at_temp_pos
				(
					comp::Drawable::Data
					{
						.c=rope_part.str.at(i),
						.color_pair=rope_part.color_pair,
						.gs_color_pair=rope_part.gs_color_pair
					}
				);
			}

			if ((!msg_log.keep_sep()) && (temp_pos.x < i32(size_2d().x)))
			{
				draw_at_temp_pos
				(
					comp::Drawable::Data
					{
						.c=' ',
						.color_pair=rope_part.color_pair,
						.gs_color_pair=rope_part.gs_color_pair
					}
				);

				++temp_pos.x;
			}
		}
		for (; temp_pos.x<i32(size_2d().x); ++temp_pos.x)
		{
			draw_at_temp_pos
			(
				comp::Drawable::Data
				{
					.c=' ',
					.color_pair=FontColor::Black,
					.gs_color_pair=FontColor::Black
				}
			);
		}
	}
}

//void Window::draw(const Hud& hud)
//{
//}

//void Window::draw(const LayeredWindow& layered_win)
//{
//	// This might need `std::greater` instead of `std::less`
//	std::priority_queue<std::pair<uint, std::string>> pq;
//
//	for (const auto& pair: layered_win.layer_prio_map())
//	{
//		pq.push(std::pair(pair.second, pair.first));
//	}
//
//	while (!pq.empty())
//	{
//		draw(layered_win.layer_at(pq.top().second));
//		pq.pop();
//	}
//}
//--------
//LayeredWindow::LayeredWindow()
//{
//}
//LayeredWindow::LayeredWindow(const IntVec2& s_pos,
//	const IntVec2& s_size_2d,
//	const std::map<std::string, uint>& s_layer_prio_map)
//	: _layer_prio_map(s_layer_prio_map)
//{
//	for (const auto& pair: layer_prio_map())
//	{
//		_layer_map[pair.first] = Window(s_pos, s_size_2d);
//	}
//}
//LayeredWindow::~LayeredWindow()
//{
//}
//
//void LayeredWindow::tick(InputKind input_kind)
//{
//	// Derived classes should override this function
//}
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon
