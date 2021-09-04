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

#include <queue>

namespace dungwich_sandeon
{
namespace game_engine
{
//--------
//const SizeVec2 Window::SIZE_2D(80, 60),
//	Screen::PLAYFIELD_POS(0, 0),
//	Screen::PLAYFIELD_SIZE_2D(60, 50);
const SizeVec2 Window::SCREEN_SIZE_2D(80, 60);
//const SizeVec2 Window::SCREEN_SIZE_2D(60, 50);
//--------
Window::Window()
{
}
Window::Window(const PosVec2& s_pos, const SizeVec2& s_size_2d)
	: _active(false), _pos(s_pos), 
	_ent_id_v2d(s_size_2d.y, ecs::EntIdVec(s_size_2d.x, ecs::ENT_NULL_ID))
{
}
Window::Window(const PosVec2& s_pos, const PosVec2& s_end_pos)
	: _active(false), _pos(s_pos),
	_ent_id_v2d(s_end_pos.y - s_pos.y + 1,
		ecs::EntIdVec(s_end_pos.x - s_pos.x + 1, ecs::ENT_NULL_ID))
{
}
Window::~Window()
{
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
void Window::draw(const LayeredWindow& layered_win)
{
	// This might need `std::greater` instead of `std::less`
	std::priority_queue<std::pair<size_t, std::string>> pq;

	for (const auto& pair: layered_win.layer_prio_map())
	{
		pq.push(std::pair(pair.second, pair.first));
	}

	while (!pq.empty())
	{
		draw(layered_win.layer_at(pq.top().second));
		pq.pop();
	}
}
//--------
LayeredWindow::LayeredWindow()
{
}
LayeredWindow::LayeredWindow(const PosVec2& s_pos,
	const SizeVec2& s_size_2d,
	const std::map<std::string, size_t>& s_layer_prio_map)
	: _layer_prio_map(s_layer_prio_map)
{
	for (const auto& pair: layer_prio_map())
	{
		_layer_map[pair.first] = Window(s_pos, s_size_2d);
	}
}
LayeredWindow::~LayeredWindow()
{
}

void LayeredWindow::tick(InputKind input_kind)
{
	// Derived classes should override this function
}
//--------
} // namespace game_engine
} // namespace dungwich_sandeon
