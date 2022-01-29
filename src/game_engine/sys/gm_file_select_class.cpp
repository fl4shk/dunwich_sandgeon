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

#include "gm_file_select_class.hpp"
#include "../engine_class.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace sys
{

const std::string
	GmFileSelect::KIND_STR("GmFileSelect");

std::string GmFileSelect::kind_str() const
{
	return KIND_STR;
}

void GmFileSelect::init(ecs::Engine* ecs_engine)
{
	did_init = true;
	_show_popup_window = false;

	uint i = 0;
	engine->aux_menu = Menu
	(
		"file_qmark",
		engine->aux_window.size_2d(),
		Menu::build_node_map
		({
			//--------
			Menu::build_text_only_knc_pair("title", "Select A File"),
			//--------
			//Menu::build_spaces_knc_pair(i++),
			Menu::build_separator_knc_pair(i++),
			//--------
			Menu::build_horiz_picker_knc_pair
			(
				"file_qmark",
				"File?",
				game_engine::Engine::NUM_FILES,
				this,
				std::function<void(GmFileSelect*, Menu::Node*)>
					(&_aux_menu_file_qmark_hpick_func)
			),
			Menu::build_action_button_knc_pair
			(
				"start_game",
				"Start Game",
				this,
				std::function<void(GmFileSelect*)>
					(&_aux_menu_start_game_func)
			),
			Menu::build_action_button_knc_pair
			(
				"copy_file",
				"Copy File",
				this,
				std::function<void(GmFileSelect*)>
					(&_aux_menu_copy_file_func)
			),
			Menu::build_action_button_knc_pair
			(
				"erase_file",
				"Erase File",
				this,
				std::function<void(GmFileSelect*)>
					(&_aux_menu_erase_file_func)
			),
			Menu::build_action_button_knc_pair
			(
				"exit",
				"Exit",
				this,
				std::function<void(GmFileSelect*)>
					(&_aux_menu_exit_func)
			),
			//--------
		}),
		Vec2(false, true),
		7
	);
}
void GmFileSelect::tick(ecs::Engine* ecs_engine)
{
	auto engine = game_engine::engine;

	//if (active() && active.has_changed())
	//{
	//	active.back_up_and_update(true);
	//}
	//else if (active())
	if (engine->game_mode() == GameMode::FileSelect)
	{
		if (active() && active.has_changed())
		{
			active.back_up();
		}
		else if (active())
		{
			if (!did_init)
			{
				init(ecs_engine);
			}

			auto
				& screen_window = engine->screen_window,
				& aux_window = engine->aux_window,
				& popup_window = engine->popup_window;

			auto
				& aux_menu = engine->aux_menu,
				& popup_menu = engine->popup_menu;

			if (!_show_popup_window)
			{
				aux_menu.tick(engine->key_status);
			}
			else // if (_show_popup_window)
			{
				popup_menu.tick(engine->key_status);
			}

			screen_window.clear();

			aux_window.clear();
			aux_window.draw(aux_menu);
			screen_window.draw(aux_window);

			if (_show_popup_window)
			{
				//printout("testificate: ", popup_window.size_2d().x,
				//	" ", popup_window.size_2d().y, "\n");
				popup_window.clear();
				popup_window.draw(popup_menu);
				screen_window.draw(popup_window);
			}
		}
	}
}
//--------
void GmFileSelect::_aux_menu_file_qmark_hpick_func(GmFileSelect* self,
	Menu::Node* node)
{
	engine->src_file_num = std::get<Menu::Node::DataValue>(node->data)();
}
void GmFileSelect::_aux_menu_start_game_func(GmFileSelect* self)
{
}
void GmFileSelect::_aux_menu_copy_file_func(GmFileSelect* self)
{
	self->_show_popup_window = true;

	uint i = 0;
	engine->popup_menu = Menu
	(
		"dst_file_qmark",
		engine->popup_window.size_2d(),
		Menu::build_node_map
		({
			//--------
			Menu::build_text_only_knc_pair("title", sconcat("Copy File ",
				engine->src_file_num, " To?")),
			//--------
			Menu::build_separator_knc_pair(i++),
			//--------
			Menu::build_horiz_picker_knc_pair
			(
				"dst_file_qmark",
				"Destination File?",
				game_engine::Engine::NUM_FILES,
				self,
				std::function<void(GmFileSelect*, Menu::Node*)>
					(&_popup_menu_dest_file_qmark_hpick_func)
			),
			Menu::build_action_button_knc_pair
			(
				"do_the_copy",
				"Do The Copy",
				self,
				std::function<void(GmFileSelect*)>
					(&_popup_menu_do_the_copy_func)
			),
			Menu::build_action_button_knc_pair
			(
				"cancel",
				"Cancel",
				self,
				std::function<void(GmFileSelect*)>
					(&_popup_menu_cancel_func)
			)
			//--------
		}),
		Vec2(false, true),
		0
	);
}
void GmFileSelect::_aux_menu_erase_file_func(GmFileSelect* self)
{
}
void GmFileSelect::_aux_menu_exit_func(GmFileSelect* self)
{
	game_engine::engine->set_game_mode(GameMode::TitleScreen);
}

void GmFileSelect::_popup_menu_dest_file_qmark_hpick_func
	(GmFileSelect* self, Menu::Node* node)
{
	engine->copy_dst_file_num
		= std::get<Menu::Node::DataValue>(node->data)();
}
void GmFileSelect::_popup_menu_do_the_copy_func(GmFileSelect* self)
{
	self->_show_popup_window = false;
}
void GmFileSelect::_popup_menu_cancel_func(GmFileSelect* self)
{
	self->_show_popup_window = false;
}
//--------
} // namespace sys
} // namespace game_engine
} // namespace dungwich_sandeon
