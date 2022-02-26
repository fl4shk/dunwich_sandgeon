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

#include "gm_file_select_class.hpp"
#include "../engine_class.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace sys
{

const std::string
	GmFileSelect::KIND_STR("GmFileSelect"),
	GmFileSelect::AUX_MENU_KEY_FILE_QMARK("file_qmark");

std::string GmFileSelect::kind_str() const
{
	return KIND_STR;
}

void GmFileSelect::init(ecs::Engine* ecs_engine)
{
	_init_start();

	//engine->src_file_num = *engine->curr_file_num();

	*engine->curr_file_num() = engine->src_file_num = 0;
	engine->fn_state = Engine::FnState::Src;

	_win_state = WinState::Aux;

	uint i = 0;
	for (int j=0; j<Engine::NUM_FILES; ++j)
	{
		engine->aux_menu(j) = Menu
		(
			AUX_MENU_KEY_FILE_QMARK,
			engine->aux_window(j).size_2d(),
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
					AUX_MENU_KEY_FILE_QMARK,
					"File?",
					game_engine::Engine::NUM_FILES - 1,
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
}
void GmFileSelect::tick(ecs::Engine* ecs_engine)
{
	if (_tick_helper(ecs_engine,
		engine->game_mode() == GameMode::FileSelect))
	{
		//const int& cfn = *engine->curr_file_num();
		const int& sfn = engine->src_file_num;
		auto& screen_window = engine->screen_window();

		auto
			& aux_menu_sfn = engine->aux_menu(sfn),
			& popup_menu_sfn = engine->popup_menu(sfn),
			& text_yes_no_menu_sfn = engine->text_yes_no_menu(sfn);

		screen_window.clear();

		switch (_win_state)
		{
		//--------
		case WinState::Aux:
			aux_menu_sfn.tick(engine->key_status);
			engine->draw_aux_menu_w_pre_clear(sfn);
			break;
		case WinState::Popup:
			//printout("testificate: ", popup_window_sfn.size_2d().x,
			//	" ", popup_window_sfn.size_2d().y, "\n");
			engine->draw_aux_menu_w_pre_clear(sfn);

			popup_menu_sfn.tick(engine->key_status);
			engine->draw_popup_menu_w_pre_clear(sfn);
			break;
		case WinState::TextYesNoCopy:
			engine->draw_aux_menu_w_pre_clear(sfn);
			engine->draw_popup_menu_w_pre_clear(sfn);

			text_yes_no_menu_sfn.tick(engine->key_status);
			engine->draw_text_yes_no_menu_w_pre_clear(sfn);
			break;
		case WinState::TextYesNoErase:
			engine->draw_aux_menu_w_pre_clear(sfn);

			text_yes_no_menu_sfn.tick(engine->key_status);
			engine->draw_text_yes_no_menu_w_pre_clear(sfn);
			break;
		default:
			printerr("game_engine::sys::GmFileSelect::tick(): ",
				"Internal error.\n");
			exit(1);
			break;
		//--------
		}
	}
}
//--------
void GmFileSelect::_aux_menu_file_qmark_hpick_func(GmFileSelect* self,
	Menu::Node* node)
{
	//*engine->curr_file_num()
	//	= std::get<Menu::Node::DataValue>(node->data)();
	int& sfn = engine->src_file_num;
	sfn = std::get<Menu::Node::DataValue>(node->data)();

	for (int j=0; j<Engine::NUM_FILES; ++j)
	{
		Menu& aux_menu = engine->aux_menu(j);
		Menu::Node& other_node = aux_menu.at(AUX_MENU_KEY_FILE_QMARK);
		std::get<Menu::Node::DataValue>(other_node.data)() = sfn;
	}
}
void GmFileSelect::_aux_menu_start_game_func(GmFileSelect* self)
{
	//*engine->curr_file_num() = engine->src_file_num;
	//engine->fn_state = Engine::FnState::Curr;

	// TODO: finish this function
}
void GmFileSelect::_aux_menu_copy_file_func(GmFileSelect* self)
{
	self->_win_state = WinState::Popup;

	uint i = 0;
	for (int j=0; j<Engine::NUM_FILES; ++j)
	{
		engine->popup_menu(j) = Menu
		(
			"dst_file_qmark",
			engine->popup_window(j).size_2d(),
			Menu::build_node_map
			({
				//--------
				Menu::build_text_only_knc_pair("title",
					sconcat("Copy File ", j, " To?")),
				//--------
				Menu::build_separator_knc_pair(i++),
				//--------
				Menu::build_horiz_picker_knc_pair
				(
					"dst_file_qmark",
					"Destination File?",
					Engine::NUM_FILES,
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
}
void GmFileSelect::_aux_menu_erase_file_func(GmFileSelect* self)
{
	self->_win_state = WinState::TextYesNoErase;
	for (int j=0; j<Engine::NUM_FILES; ++j)
	{
		engine->text_yes_no_menu(j) = engine->build_text_yes_no_menu
		(
			self, j,
			sconcat("Really erase file ", j, "?"),
			std::function<void(GmFileSelect*)>
				(&_text_yes_no_menu_erase_yes_func),
			std::function<void(GmFileSelect*)>
				(&_text_yes_no_menu_erase_no_func)
		);
	}
}
void GmFileSelect::_aux_menu_exit_func(GmFileSelect* self)
{
	engine->set_game_mode(GameMode::TitleScreen);
	*engine->curr_file_num() = engine->src_file_num;
	engine->fn_state = Engine::FnState::Curr;
}
//--------
void GmFileSelect::_popup_menu_dest_file_qmark_hpick_func
	(GmFileSelect* self, Menu::Node* node)
{
	engine->copy_dst_file_num
		= std::get<Menu::Node::DataValue>(node->data)();
}
void GmFileSelect::_popup_menu_do_the_copy_func(GmFileSelect* self)
{
	self->_win_state = WinState::TextYesNoCopy;
	for (int j=0; j<Engine::NUM_FILES; ++j)
	{
		engine->text_yes_no_menu(j) = engine->build_text_yes_no_menu
		(
			self, j,
			sconcat("Really copy file ", j, " to file ",
				engine->copy_dst_file_num, "?"),
			std::function<void(GmFileSelect*)>
				(&_text_yes_no_menu_copy_yes_func),
			std::function<void(GmFileSelect*)>
				(&_text_yes_no_menu_copy_no_func)
		);
	}
}
void GmFileSelect::_popup_menu_cancel_func(GmFileSelect* self)
{
	self->_win_state = WinState::Aux;
}
//--------
void GmFileSelect::_text_yes_no_menu_copy_yes_func(GmFileSelect* self)
{
	self->_win_state = WinState::Aux;
	engine->copy_file();
}
void GmFileSelect::_text_yes_no_menu_copy_no_func(GmFileSelect* self)
{
	self->_win_state = WinState::Aux;
}
void GmFileSelect::_text_yes_no_menu_erase_yes_func(GmFileSelect* self)
{
	self->_win_state = WinState::Aux;
	engine->erase_file();
}
void GmFileSelect::_text_yes_no_menu_erase_no_func(GmFileSelect* self)
{
	self->_win_state = WinState::Aux;
}
//--------
} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon
