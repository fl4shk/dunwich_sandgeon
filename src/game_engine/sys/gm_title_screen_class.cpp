// This file is part of Dungwich Sandeon.
// 
// Copyright 2022 FL4SHK
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
	_init_start();

	uint i = 0;
	engine->aux_menu_cfn() = Menu
	(
		"file_select",
		engine->aux_window_cfn().size_2d(),
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
	auto engine = game_engine::engine;
	if (_tick_helper(ecs_engine,
		engine->game_mode() == GameMode::TitleScreen))
	{
		auto
			& screen_window = engine->screen_window(),
			& aux_window_cfn = engine->aux_window_cfn();

		auto& aux_menu_cfn = engine->aux_menu_cfn();

		aux_menu_cfn.tick(engine->key_status);

		aux_window_cfn.clear();
		aux_window_cfn.draw(aux_menu_cfn);

		screen_window.clear();
		screen_window.draw(aux_window_cfn);
	}
}

void GmTitleScreen::_aux_menu_file_select_func(GmTitleScreen* self)
{
	game_engine::engine->set_game_mode(GameMode::FileSelect);
}

void GmTitleScreen::_aux_menu_options_func(GmTitleScreen* self)
{
	game_engine::engine->set_game_mode(GameMode::Options);
}
void GmTitleScreen::_aux_menu_quit_game_func(GmTitleScreen* self)
{
	game_engine::engine->save_and_quit();
}

} // namespace sys
} // namespace game_engine
} // namespace dungwich_sandeon
