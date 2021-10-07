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

#include "gm_title_screen_class.hpp"
#include "../engine_class.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace sys
{

const std::string
	GmTitleScreen::KIND_STR("GmTitleScreen");

std::string GmTitleScreen::kind_str() const
{
	return KIND_STR;
}

void GmTitleScreen::init(ecs::Engine* ecs_engine)
{
	did_init = true;

	size_t i = 0;
	engine->aux_menu = Menu
	(
		"start_game",
		engine->aux_window.size_2d(),
		Menu::build_node_map
		({
			Menu::build_text_only_knc_pair("title", "Dungwich Sandeon"),
			Menu::build_spaces_knc_pair(i++),
			Menu::build_text_only_knc_pair("author", "A game by FL4SHK"),
			Menu::build_spaces_knc_pair(i++),
			Menu::build_spaces_knc_pair(i++),
			Menu::build_spaces_knc_pair(i++),
			Menu::build_action_button_knc_pair
			(
				"start_game",
				"Start Game!",
				this,
				std::function<void(GmTitleScreen*)>
					(&GmTitleScreen::_aux_menu_start_game_func)
			),
			//Menu::build_text_only_knc_pair("testificate[0]",
			//	"Testificate"),
			Menu::build_action_button_knc_pair
			(
				"options",
				"Options",
				this,
				std::function<void(GmTitleScreen*)>
					(&GmTitleScreen::_aux_menu_options_func)
			),
			//Menu::build_text_only_knc_pair("testificate[1]",
			//	"Testificate"),
		}),
		Vec2(false, true),
		7
	);
}
void GmTitleScreen::tick(ecs::Engine* ecs_engine)
{
	auto engine = game_engine::engine;

	if (engine->game_mode() == GameMode::TitleScreen)
	{
		//printout("GmTitleScreen::tick(): testificate\n");

		if (!did_init)
		{
			init(ecs_engine);
		}

		auto
			& screen_window = engine->screen_window,
			& aux_window = engine->aux_window;

		auto& aux_menu = engine->aux_menu;

		aux_menu.tick(engine->key_status);

		aux_window.clear();
		aux_window.draw(aux_menu);

		screen_window.clear();
		screen_window.draw(aux_window);
	}
}

void GmTitleScreen::_aux_menu_start_game_func(GmTitleScreen* self)
{
	printout("game_engine::sys::GmTitleScreen::",
		"_aux_menu_start_game_func(): testificate\n");

	//game_engine::engine->set_game_mode(GameMode::PrepareBeforeGame);
}

void GmTitleScreen::_aux_menu_options_func(GmTitleScreen* self)
{
	printout("game_engine::sys::GmTitleScreen::",
		"_aux_menu_options_func(): testificate\n");

	game_engine::engine->set_game_mode(GameMode::Options);
}

} // namespace sys
} // namespace game_engine
} // namespace dungwich_sandeon
