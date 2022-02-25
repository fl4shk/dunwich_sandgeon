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

#include <queue>

namespace <dunwich_sandgeon>
{
namespace game_engine
{
//--------
//const SizeVec2 Window::SCREEN_SIZE_2D(82, 62);
//const SizeVec2 Window::SCREEN_SIZE_2D(60, 50);

const std::string
	Window::BORDER_CORNER_KIND_STR("game_engine::Window::BorderCorner"),
	Window::BORDER_HORIZ_KIND_STR("game_engine::Window::BorderHoriz"),
	Window::BORDER_VERT_KIND_STR("game_engine::Window::BorderVert"),
	Window::BLANK_KIND_STR("game_engine::Window::Blank");
//--------
const comp::Drawable::Data& Window::BORDER_CORNER_DRAWABLE_DATA()
{
	return comp::DRAWABLE_DATA_MAP.at(BORDER_CORNER_KIND_STR);
}
const comp::Drawable::Data& Window::BORDER_HORIZ_DRAWABLE_DATA()
{
	return comp::DRAWABLE_DATA_MAP.at(BORDER_HORIZ_KIND_STR);
}
const comp::Drawable::Data& Window::BORDER_VERT_DRAWABLE_DATA()
{
	return comp::DRAWABLE_DATA_MAP.at(BORDER_VERT_KIND_STR);
}
const comp::Drawable::Data& Window::BLANK_DRAWABLE_DATA()
{
	return comp::DRAWABLE_DATA_MAP.at(BLANK_KIND_STR);
}

Window::Window()
{
}
Window::Window(Engine* s_engine, const PosVec2& s_some_pos,
	const SizeVec2& s_some_size_2d, int s_file_num,
	bool prev_args_are_with_border)
	: _engine(s_engine),
	_pos(s_some_pos
		- ((!prev_args_are_with_border) ? PosVec2(1, 1) : PosVec2(0, 0))),
	_ent_id_v2d
	(
		s_some_size_2d.y
			+ ((!prev_args_are_with_border) ? 2 : 0),
		ecs::EntIdVec
		(
			s_some_size_2d.x
				+ ((!prev_args_are_with_border) ? 2 : 0),
			ecs::ENT_NULL_ID
		)
	),
	_cleared_ent_id_v2d
	(
		s_some_size_2d.y
			+ ((!prev_args_are_with_border) ? 2 : 0),
		ecs::EntIdVec
		(
			s_some_size_2d.x
				+ ((!prev_args_are_with_border) ? 2 : 0),
			ecs::ENT_NULL_ID
		)
	),
	_file_num(s_file_num)
{
	//init_set_border();
}
Window::Window(Engine* s_engine, const PosVec2& s_some_pos,
	const PosVec2& s_some_end_pos, int s_file_num,
	bool prev_args_are_with_border)
	: _engine(s_engine),
	_pos(s_some_pos
		- ((!prev_args_are_with_border) ? PosVec2(1, 1) : PosVec2(0, 0))),
	_ent_id_v2d
	(
		s_some_end_pos.y - s_some_pos.y + 1
			+ ((!prev_args_are_with_border) ? 2 : 0),
		ecs::EntIdVec
		(
			s_some_end_pos.x - s_some_pos.x + 1
				+ ((!prev_args_are_with_border) ? 2 : 0),
			ecs::ENT_NULL_ID
		)
	),
	_cleared_ent_id_v2d
	(
		s_some_end_pos.y - s_some_pos.y + 1
			+ ((!prev_args_are_with_border) ? 2 : 0),
		ecs::EntIdVec
		(
			s_some_end_pos.x - s_some_pos.x + 1
				+ ((!prev_args_are_with_border) ? 2 : 0),
			ecs::ENT_NULL_ID
		)
	),
	_file_num(s_file_num)
{
	//init_set_border();
}
Window::~Window()
{
}

// This function exists and is called outside of the constructor because in
// the `game_engine::engine` class, the `game_engine::Window`s are
// constructed before the `game_engine::Engine` that is passed to the
// `game_engine::Window` constructor.
void Window::init_set_border()
{
	ecs::EntId id = ecs::ENT_NULL_ID;
	auto add_border_drawable
		= [this, &id](comp::Drawable::Data drawable_data) -> void
	{
		_engine->ecs_engine.insert_comp(id,
			ecs::CompUptr(new comp::Drawable(drawable_data)),
			file_num());
	};
	for (uint j=0; j<with_border_size_2d().y; ++j)
	{
		for (uint i=0; i<with_border_size_2d().x; ++i)
		{
			if ((j == 0) || (j == (with_border_size_2d().y - 1)))
			{
				if ((i == 0) || (i == (with_border_size_2d().x - 1)))
				{
					id = _engine->ecs_engine.create(file_num());
					with_border_ent_id_at(PosVec2(i, j)) = id;
					add_border_drawable(BORDER_CORNER_DRAWABLE_DATA());

					id = _engine->ecs_engine.create(file_num());
					_cleared_ent_id_v2d.at(j).at(i) = id;
					add_border_drawable(BORDER_CORNER_DRAWABLE_DATA());
				}
				else
				{
					id = _engine->ecs_engine.create(file_num());
					with_border_ent_id_at(PosVec2(i, j)) = id;
					add_border_drawable(BORDER_HORIZ_DRAWABLE_DATA());

					id = _engine->ecs_engine.create(file_num());
					_cleared_ent_id_v2d.at(j).at(i) = id;
					add_border_drawable(BORDER_HORIZ_DRAWABLE_DATA());
				}
			}
			else if ((i == 0) || (i == (with_border_size_2d().x - 1)))
			{
				id = _engine->ecs_engine.create(file_num());
				with_border_ent_id_at(PosVec2(i, j)) = id;
				add_border_drawable(BORDER_VERT_DRAWABLE_DATA());

				id = _engine->ecs_engine.create(file_num());
				_cleared_ent_id_v2d.at(j).at(i) = id;
				add_border_drawable(BORDER_VERT_DRAWABLE_DATA());
			}
			else
			{
				id = _engine->ecs_engine.create(file_num());
				with_border_ent_id_at(PosVec2(i, j)) = id;
				_engine->ecs_engine.insert_comp(id,
					ecs::CompUptr(new comp::Drawable
						(BLANK_DRAWABLE_DATA())),
					file_num());

				id = _engine->ecs_engine.create(file_num());
				_cleared_ent_id_v2d.at(j).at(i) = id;
				_engine->ecs_engine.insert_comp(id,
					ecs::CompUptr(new comp::Drawable
						(BLANK_DRAWABLE_DATA())),
					file_num());
			}
		}
	}
}

void Window::tick(InputKind input_kind)
{
	// Derived classes should override this function
};

void Window::clear()
{
	PosVec2 src_pos;
	for (src_pos.y=0; src_pos.y<with_border_size_2d().y; ++src_pos.y)
	{
		for (src_pos.x=0; src_pos.x<with_border_size_2d().x; ++src_pos.x)
		{
			const auto
				SRC_ENT_ID = _cleared_ent_id_v2d.at(src_pos.y)
					.at(src_pos.x),
				DST_ENT_ID = with_border_ent_id_at(src_pos);
			auto
				src = _engine->ecs_engine
					.casted_comp_at<comp::Drawable>(SRC_ENT_ID,
						file_num()),
				dst = _engine->ecs_engine
					.casted_comp_at<comp::Drawable>(DST_ENT_ID,
						file_num());
			*dst = *src;
			//dst->data.color_pair = FontColor::Black;
		}
	}
}

void Window::draw(const Window& win, bool leave_corner)
{
	PosVec2 src_pos;
	for (src_pos.y=0; src_pos.y<win.with_border_size_2d().y; ++src_pos.y)
	{
		for (src_pos.x=0;
			src_pos.x<win.with_border_size_2d().x;
			++src_pos.x)
		{
			const auto SRC_ENT_ID = win.with_border_ent_id_at(src_pos);

			if (_engine->ecs_engine.has_ent_with_comp
				(SRC_ENT_ID, comp::Drawable::KIND_STR, file_num()))
			{
				const auto DST_POS = win.pos() + src_pos;
				const auto DST_ENT_ID = with_border_ent_id_at(DST_POS);

				//printout("Window::draw(): ", src_pos.x, " ", src_pos.y,
				//	"; ", DST_POS.x, " ", DST_POS.y,
				//	"; ", win.with_border_size_2d().x, " ",
				//	win.with_border_size_2d().y, "\n");

				auto src = _engine->ecs_engine
					.casted_comp_at<comp::Drawable>(SRC_ENT_ID,
						file_num());

				if (!_engine->ecs_engine.comp_map(DST_ENT_ID, file_num())
					.contains(comp::Drawable::KIND_STR))
				{
					_engine->ecs_engine.insert_comp(DST_ENT_ID,
						ecs::CompUptr(new comp::Drawable(src->data())),
						file_num());
				}
				else
				{
					auto dst = _engine->ecs_engine
						.casted_comp_at<comp::Drawable>(DST_ENT_ID,
							file_num());

					if ((!leave_corner)
						|| (dst->data() != BORDER_CORNER_DRAWABLE_DATA()))
					{
						*dst = *src;
					}
				}
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
	PosVec2 temp_pos(0, 0);

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
			= [this, &temp_pos](comp::Drawable::Data drawable_data) -> void
		{
			const auto DST_ENT_ID = ent_id_at(temp_pos);
			auto dst = _engine->ecs_engine
				.casted_comp_at<comp::Drawable>(DST_ENT_ID, file_num());

			dst->set_data(drawable_data);
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

			if ((!msg_log.keep_sep()) && (temp_pos.x < size_2d().x))
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
		for (; temp_pos.x < size_2d().x; ++temp_pos.x)
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
//LayeredWindow::LayeredWindow(const PosVec2& s_pos,
//	const SizeVec2& s_size_2d,
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
} // namespace <dunwich_sandgeon>
