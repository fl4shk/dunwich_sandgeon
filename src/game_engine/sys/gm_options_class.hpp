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

#ifndef src_game_engine_sys_gm_options_class_hpp
#define src_game_engine_sys_gm_options_class_hpp

// src/game_engine/sys/gm_options_class.hpp

#include "../../misc_includes.hpp"
#include "../menu_etc_classes.hpp"
#include "../game_options_class.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace sys
{

// Game Mode: Options
class GmOptions final: public ecs::Sys
{
public:		// constants
	static const std::string KIND_STR;
private:		// variables
	GameOptions _game_options;
public:		// functions
	GmOptions() = default;
	//inline GmOptions(const binser::Value& bv)
	//	: ecs::Sys(bv)
	//{
	//}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(GmOptions);
	virtual ~GmOptions() = default;

	virtual std::string kind_str() const;
	virtual void init(ecs::Engine* ecs_engine);
	virtual void tick(ecs::Engine* ecs_engine);
private:		// functions
	static void _aux_menu_grayscale_func(GmOptions* self,
		Menu::Node* node);
	static void _aux_menu_save_and_exit_func(GmOptions* self);
	static void _aux_menu_exit_wo_save_func(GmOptions* self);
};

} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_sys_gm_options_class_hpp
