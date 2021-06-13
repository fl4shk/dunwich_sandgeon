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

#include "screen_class.hpp"

#include <queue>

namespace dungwich_sandeon
{

namespace game_engine
{
//--------
//const SizeVec2 Screen::SIZE_2D(80, 60),
//	Screen::PLAYFIELD_POS(0, 0),
//	Screen::PLAYFIELD_SIZE_2D(60, 50);
const SizeVec2 Screen::SIZE_2D(80, 60);
//--------
Screen::Screen()
	: _ent_id_v2d(SIZE_2D.y, ecs::EntIdVec(SIZE_2D.x, ecs::ENT_NULL_ID))
{
}
Screen::~Screen()
{
}

void Screen::draw(const Window& win)
{
	for (int j=0; j<win.pos().y; ++j)
	{
		for (int i=0; i<win.pos().x; ++i)
		{
			const PosVec2 curr_pos(i, j);
			ent_id_at(curr_pos) = win.ent_id_at(curr_pos);
		}
	}
}
void Screen::draw(const LayeredWindow& layered_win)
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
} // namespace game_engine

} // namespace dungwich_sandeon
