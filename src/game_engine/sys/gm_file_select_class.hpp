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

#ifndef src_game_engine_sys_gm_file_select_class_hpp
#define src_game_engine_sys_gm_file_select_class_hpp

// src/game_engine/sys/gm_file_select_class.hpp

#include "../../misc_includes.hpp"
#include "../menu_etc_classes.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace sys
{

// Game Mode: Prepare Before Game
class GmFileSelect final: public ecs::Sys
{
public:		// constants
	static const std::string KIND_STR;

	static constexpr int
		NUM_FILES = 9;
private:		// variables
	// File numbers selected via HorizPickers
	int
		_src_file_num = 0,
		_copy_dst_file_num = 0;

	bool _show_popup_window = false;
public:		// functions
	GmFileSelect() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(GmFileSelect);
	virtual ~GmFileSelect() = default;

	virtual std::string kind_str() const;
	virtual void init(ecs::Engine* ecs_engine);
	virtual void tick(ecs::Engine* ecs_engine);
private:		// functions
	//--------
	static void _aux_menu_file_qmark_hpick_func(GmFileSelect* self,
		Menu::Node* node);
	static void _aux_menu_start_game_func(GmFileSelect* self);
	static void _aux_menu_copy_file_func(GmFileSelect* self);
	static void _aux_menu_erase_file_func(GmFileSelect* self);
	static void _aux_menu_exit_func(GmFileSelect* self);
	//--------
	// The popup window is used as the file copying window
	static void _popup_menu_dest_file_qmark_hpick_func
		(GmFileSelect* self, Menu::Node* node);
	static void _popup_menu_do_the_copy_func(GmFileSelect* self);
	static void _popup_menu_cancel_func(GmFileSelect* self);
	//--------
};

} // namespace sys
} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_sys_gm_file_select_class_hpp
