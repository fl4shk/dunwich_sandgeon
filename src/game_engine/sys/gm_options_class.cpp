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

#include "gm_options_class.hpp"
#include "../engine_class.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace sys
{

const std::string
	GmOptions::KIND_STR("GmOptions");

std::string GmOptions::kind_str() const
{
	return KIND_STR;
}

void GmOptions::_init(ecs::Engine* ecs_engine)
{
	_init_start();

	auto engine = game_engine::engine;
	_game_options = engine->game_options;

	i32 i = 0;
	engine->aux_menu = Menu
	(
		"grayscale",
		engine->aux_window.size_2d(),

		// Menu::build_node_map() start
		// "title";
		//		up: "<start>";
		//		down: "<blank[0]>"
		// "<blank[0]>";
		//		up: "title";
		//		down: "grayscale"
		// "grayscale";
		//		up: "<blank[0]>";
		//		down: "separator[1]"
		// "separator[1]";
		//		up: "grayscale";
		//		down: "save_and_exit"
		// "save_and_exit";
		//		up: "separator[1]";
		//		down: "exit_wo_save"
		// "exit_wo_save";
		//		up: "save_and_exit";
		//		down: "<end>"
		// Menu::build_node_map() end

		Menu::build_node_map
		({
			Menu::build_text_only_knc_pair("title", "Options"),
			Menu::build_spaces_knc_pair(i++),
			Menu::build_check_button_knc_pair
				("grayscale", "Grayscale", _game_options.grayscale, this,
				std::function<void(GmOptions*, Menu::Node*)>
					(&_aux_menu_grayscale_func)),
			Menu::build_separator_knc_pair(i++),
			Menu::build_action_button_knc_pair
				("save_and_exit", "Save And Exit", this,
				std::function<void(GmOptions*)>
					(&_aux_menu_save_and_exit_func)),
			Menu::build_action_button_knc_pair
				("exit_wo_save", "Exit Without Saving", this,
				std::function<void(GmOptions*)>
					(&_aux_menu_exit_wo_save_func)),
		}),
		Vec2(false, true),
		Menu::WHOLE_SCREEN_MENU_TAB_AMOUNT_SMALL
	);
}
void GmOptions::tick(ecs::Engine* ecs_engine)
{
	auto engine = game_engine::engine;

	if (_tick_helper(ecs_engine,
		engine->game_mode() == GameMode::Options))
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

void GmOptions::_aux_menu_grayscale_func(GmOptions* self,
	Menu::Node* node)
{
	//printout("GmOptions::_aux_menu_grayscale_func(): testificate\n");
	self->_game_options.grayscale = std::get<bool>(node->data);
}

void GmOptions::_aux_menu_save_and_exit_func(GmOptions* self)
{
	//printout("GmOptions::_aux_menu_save_and_exit_func(): testificate\n");
	auto engine = game_engine::engine;
	engine->game_options = std::move(self->_game_options);
	engine->set_game_mode(GameMode::TitleScreen);
}

void GmOptions::_aux_menu_exit_wo_save_func(GmOptions* self)
{
	//printout("GmOptions::_aux_menu_exit_wo_save_func(): testificate\n");
	engine->set_game_mode(GameMode::TitleScreen);
}

} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon
