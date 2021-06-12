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
//const PosVec2 Screen::SIZE_2D(80, 60),
//	Screen::PLAYFIELD_POS(0, 0),
//	Screen::PLAYFIELD_SIZE_2D(60, 50);
const PosVec2 Screen::SIZE_2D(80, 60);
//--------
Screen::Screen()
{
}
Screen::~Screen()
{
}

void Screen::draw(const Window& win)
{
}
void Screen::draw(const LayeredWindow& layered_win)
{
	std::priority_queue<std::pair<size_t, std::string>> pq;

	for (const auto& pair: layered_win.layer_prio_map())
	{
		pq.push(std::pair(pair.second, pair.first));
	}

	while (!pq.empty())
	{
		draw(layered_win.layer_at(pq.top().second));
	}
}
//--------
} // namespace game_engine

} // namespace dungwich_sandeon
