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

#include "gm_title_screen_class.hpp"
#include "../engine_class.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace sys
{
//--------
const std::string
	GmTitleScreen::KIND_STR("GmTitleScreen");

std::string GmTitleScreen::kind_str() const
{
	return KIND_STR;
}
//--------
void GmTitleScreen::init(ecs::Engine* ecs_engine)
{
	_init_start();

	uint i = 0;
	engine->aux_menu = Menu
	(
		"file_select",
		engine->aux_window.size_2d(),
		Menu::build_node_map
		({
			Menu::build_text_only_knc_pair("title", "Dunwich Sandgeon"),
			Menu::build_spaces_knc_pair(i++),
			Menu::build_text_only_knc_pair("author", "A game by FL4SHK"),
			Menu::build_spaces_knc_pair(i++),
			Menu::build_spaces_knc_pair(i++),
			Menu::build_spaces_knc_pair(i++),
			Menu::build_action_button_knc_pair
			(
				"file_select",
				"File Select",
				this,
				std::function<void(GmTitleScreen*)>
					(&_aux_menu_file_select_func)
			),
			Menu::build_action_button_knc_pair
			(
				"options",
				"Options",
				this,
				std::function<void(GmTitleScreen*)>
					(&_aux_menu_options_func)
			),
			Menu::build_action_button_knc_pair
			(
				"quit_game",
				"Quit Game",
				this,
				std::function<void(GmTitleScreen*)>
					(&_aux_menu_quit_game_func)
			),
		}),
		Vec2(false, true),
		7
	);
}
void GmTitleScreen::tick(ecs::Engine* ecs_engine)
{
	if (_tick_helper(ecs_engine,
		engine->game_mode() == GameMode::TitleScreen))
	{
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
//--------
void GmTitleScreen::_aux_menu_file_select_func(GmTitleScreen* self)
{
	engine->set_game_mode(GameMode::FileSelect);
}

void GmTitleScreen::_aux_menu_options_func(GmTitleScreen* self)
{
	engine->set_game_mode(GameMode::Options);
}
void GmTitleScreen::_aux_menu_quit_game_func(GmTitleScreen* self)
{
	engine->save_and_quit();
}
//--------
} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon
