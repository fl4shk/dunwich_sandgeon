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

#include "gm_aux_startup_class.hpp"
#include "../engine_class.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace sys
{

const std::string
	GmAuxStartup::KIND_STR("GmAuxStartup");

std::string GmAuxStartup::kind_str() const
{
	return KIND_STR;
}

void GmAuxStartup::tick(ecs::Engine* ecs_engine)
{
	auto engine = game_engine::engine;

	if (engine->game_mode == GameMode::AuxStartup)
	{
		printout("GmAuxStartup::tick(): testificate\n");

		auto
			& screen_window = engine->screen_window,
			& aux_window = engine->aux_window;

		screen_window.clear();
		screen_window.draw(aux_window);
	}
}

} // namespace sys
} // namespace game_engine
} // namespace dungwich_sandeon
