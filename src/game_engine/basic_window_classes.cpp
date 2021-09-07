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
	)
{
	//init_set_border();
}
Window::~Window()
{
}

void Window::init_set_border()
{
	//for (size_t j=0; j<(Window::SCREEN_SIZE_2D.y + 2); ++j)
	//{
	//	for (size_t i=0; i<(Window::SCREEN_SIZE_2D.x + 2); ++i)
	//	{
	//		auto draw_border_char
	//			= [this, &j, &i](int c) -> void
	//		{
	//			_text_handler.draw_char(c, Window::SEP_COLOR,
	//				PosVec2(i, j));
	//		};

	//		if ((j == 0) || (j == (Window::SCREEN_SIZE_2D.y + 1)))
	//		{
	//			if ((i == 0) || (i == (Window::SCREEN_SIZE_2D.x + 1)))
	//			{
	//				draw_border_char(Window::SEP_CORNER_CHAR);
	//			}
	//			else
	//			{
	//				draw_border_char(Window::SEP_HORIZ_CHAR);
	//			}
	//		}
	//		else if ((i == 0) || (i == (Window::SCREEN_SIZE_2D.x + 1)))
	//		{
	//			draw_border_char(Window::SEP_VERT_CHAR);
	//		}
	//		else
	//		{
	//			// Draw the non-border tiles here.
	//		}
	//	}
	//}

	auto add_border_drawable
		= [this](const PosVec2& index, int c) -> void
	{
		const ecs::EntId id = _engine->ecs_engine.create();
		with_border_ent_id_at(index) = id;

		_engine->ecs_engine.insert_comp(id, comp::Drawable::KIND_STR,
			ecs::CompUptr(new comp::Drawable
				(comp::Drawable::Data{.c=c, .color_pair=BORDER_COLOR})));
	};
	for (size_t i=0; i<with_border_size_2d().x; ++i)
	{
		if ((i == 0) || (i == (with_border_size_2d().x - 1)))
		{
			add_border_drawable(PosVec2(i, 0), BORDER_CORNER_CHAR);
			add_border_drawable(PosVec2(i, with_border_size_2d().y - 1),
				BORDER_CORNER_CHAR);

			for (size_t j=1; j<with_border_size_2d().y - 1; ++j)
			{
				add_border_drawable(PosVec2(i, j), BORDER_VERT_CHAR);
			}
		}
		else
		{
			add_border_drawable(PosVec2(i, 0), BORDER_HORIZ_CHAR);
			add_border_drawable(PosVec2(i, with_border_size_2d().y - 1),
				BORDER_HORIZ_CHAR);
		}
	}

	//// This is test code.
	//for (size_t j=0; j<with_border_size_2d().y; ++j)
	//{
	//	for (size_t i=0; i<with_border_size_2d().x; ++i)
	//	{
	//		if ((j == 0) && (i == 0))
	//		{
	//			const PosVec2 index(i, j);
	//			const ecs::EntId id = _engine->ecs_engine.create();
	//			with_border_ent_id_at(index) = id;

	//			const comp::Drawable::Data TO_INSERT_DATA
	//				= {
	//					.c='@',
	//					.color_pair=FgBgColorPair(FontColor::Red,
	//						FontColor::White)
	//				};
	//			_engine->ecs_engine.insert_comp(id,
	//				comp::Drawable::KIND_STR,
	//				ecs::CompUptr(new comp::Drawable(TO_INSERT_DATA)));
	//			printout("Window: ", id, " ", std::hex, 
	//				(void*)(&_engine->ecs_engine.comp_map(id)), std::dec,
	//				"\n");
	//			printout(_engine->ecs_engine.comp_map(id).contains
	//				(comp::Drawable::KIND_STR), "\n");
	//			printout(_engine->ecs_engine.has_ent_with_comp(id,
	//				comp::Drawable::KIND_STR), "\n");


	//			//auto& comp_map = _engine->ecs_engine.comp_map(id);
	//			////printout("Testificate: ",
	//			////	comp_map.at("Drawable")->kind_str(), "\n");
	//			//printout("Testificate: ",
	//			//	comp_map.contains("Drawable"), "\n");
	//		}
	//	}
	//}
}

void Window::tick(InputKind input_kind)
{
	// Derived classes should override this function
};

void Window::draw(const Window& win)
{
	for (int j=0; j<win.pos().y; ++j)
	{
		for (int i=0; i<win.pos().x; ++i)
		{
			const PosVec2 curr_pos(i, j);
			const auto& ent_id = win.ent_id_at(curr_pos);

			if (ent_id != ecs::ENT_NULL_ID)
			{
				ent_id_at(curr_pos) = ent_id;
			}
		}
	}
}
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
