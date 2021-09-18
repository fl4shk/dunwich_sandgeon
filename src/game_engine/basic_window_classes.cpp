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

#include "basic_window_classes.hpp"
#include "engine_class.hpp"
#include "menu_etc_classes.hpp"
#include "comp/drawable_data_map.hpp"

#include <queue>

namespace dungwich_sandeon
{
namespace game_engine
{
//--------
const SizeVec2
	Window::WITH_BORDER_SCREEN_SIZE_2D(82, 62),

	Window::SCREEN_SIZE_2D
		(Window::WITH_BORDER_SCREEN_SIZE_2D - SizeVec2(2, 2));
//const SizeVec2 Window::SCREEN_SIZE_2D(82, 62);
//const SizeVec2 Window::SCREEN_SIZE_2D(60, 50);

const std::string
	Window::BORDER_CORNER_KIND_STR("game_engine::Window::BorderCorner"),
	Window::BORDER_HORIZ_KIND_STR("game_engine::Window::BorderHoriz"),
	Window::BORDER_VERT_KIND_STR("game_engine::Window::BorderVert"),
	Window::BLANK_KIND_STR("game_engine::Window::Blank");
//--------
Window::Window()
{
}
Window::Window(Engine* s_engine, const PosVec2& s_some_pos,
	const SizeVec2& s_some_size_2d, bool prev_args_are_with_border)
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
	)
{
	//init_set_border();
}
Window::Window(Engine* s_engine, const PosVec2& s_some_pos,
	const PosVec2& s_some_end_pos, bool prev_args_are_with_border)
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
	)
{
	//init_set_border();
}
Window::~Window()
{
}

void Window::init_set_border()
{
	ecs::EntId id = ecs::ENT_NULL_ID;
	auto add_border_drawable
		= [this, &id](comp::Drawable::Data drawable_data) -> void
	{
		_engine->ecs_engine.insert_comp(id,
			ecs::CompUptr(new comp::Drawable(drawable_data)));
	};
	for (size_t j=0; j<with_border_size_2d().y; ++j)
	{
		for (size_t i=0; i<with_border_size_2d().x; ++i)
		{
			if ((j == 0) || (j == (with_border_size_2d().y - 1)))
			{
				if ((i == 0) || (i == (with_border_size_2d().x - 1)))
				{
					id = _engine->ecs_engine.create();
					with_border_ent_id_at(PosVec2(i, j)) = id;
					add_border_drawable(BORDER_CORNER_DRAWABLE_DATA());

					id = _engine->ecs_engine.create();
					_cleared_ent_id_v2d.at(j).at(i) = id;
					add_border_drawable(BORDER_CORNER_DRAWABLE_DATA());
				}
				else
				{
					id = _engine->ecs_engine.create();
					with_border_ent_id_at(PosVec2(i, j)) = id;
					add_border_drawable(BORDER_HORIZ_DRAWABLE_DATA());

					id = _engine->ecs_engine.create();
					_cleared_ent_id_v2d.at(j).at(i) = id;
					add_border_drawable(BORDER_HORIZ_DRAWABLE_DATA());
				}
			}
			else if ((i == 0) || (i == (with_border_size_2d().x - 1)))
			{
				id = _engine->ecs_engine.create();
				with_border_ent_id_at(PosVec2(i, j)) = id;
				add_border_drawable(BORDER_VERT_DRAWABLE_DATA());

				id = _engine->ecs_engine.create();
				_cleared_ent_id_v2d.at(j).at(i) = id;
				add_border_drawable(BORDER_VERT_DRAWABLE_DATA());
			}
			else
			{
				id = _engine->ecs_engine.create();
				with_border_ent_id_at(PosVec2(i, j)) = id;
				_engine->ecs_engine.insert_comp(id,
					ecs::CompUptr(new comp::Drawable
						(BLANK_DRAWABLE_DATA())));

				id = _engine->ecs_engine.create();
				_cleared_ent_id_v2d.at(j).at(i) = id;
				_engine->ecs_engine.insert_comp(id,
					ecs::CompUptr(new comp::Drawable
						(BLANK_DRAWABLE_DATA())));
			}
		}
	}
}

void Window::tick(InputKind input_kind)
{
	// Derived classes should override this function
};

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
				(SRC_ENT_ID, comp::Drawable::KIND_STR))
			{
				const auto DST_POS = win.pos() + src_pos;
				const auto DST_ENT_ID = with_border_ent_id_at(DST_POS);

				//printout("Window::draw(): ", src_pos.x, " ", src_pos.y,
				//	"; ", DST_POS.x, " ", DST_POS.y,
				//	"; ", win.with_border_size_2d().x, " ",
				//	win.with_border_size_2d().y, "\n");

				auto src = _engine->ecs_engine
					.casted_comp_at<comp::Drawable>(SRC_ENT_ID);

				if (!_engine->ecs_engine.comp_map(DST_ENT_ID)
					.contains(comp::Drawable::KIND_STR))
				{
					_engine->ecs_engine.insert_comp(DST_ENT_ID,
						ecs::CompUptr(new comp::Drawable(src->data())));
				}
				else
				{
					auto dst = _engine->ecs_engine
						.casted_comp_at<comp::Drawable>(DST_ENT_ID);

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
					.casted_comp_at<comp::Drawable>(SRC_ENT_ID),
				dst = _engine->ecs_engine
					.casted_comp_at<comp::Drawable>(DST_ENT_ID);
			*dst = *src;
			//dst->data.color_pair = FontColor::Black;
		}
	}
}

void Window::draw(const Menu& menu)
{
}

void Window::draw(const MsgLog& msg_log)
{
}

//void Window::draw(const Hud& hud)
//{
//}

//void Window::draw(const LayeredWindow& layered_win)
//{
//	// This might need `std::greater` instead of `std::less`
//	std::priority_queue<std::pair<size_t, std::string>> pq;
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
//--------
//LayeredWindow::LayeredWindow()
//{
//}
//LayeredWindow::LayeredWindow(const PosVec2& s_pos,
//	const SizeVec2& s_size_2d,
//	const std::map<std::string, size_t>& s_layer_prio_map)
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
} // namespace dungwich_sandeon
