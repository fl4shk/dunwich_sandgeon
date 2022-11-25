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

#ifndef src_game_engine_sys_gm_main_class_hpp
#define src_game_engine_sys_gm_main_class_hpp

// src/game_engine/sys/gm_main_class.hpp

#include "../../misc_includes.hpp"
#include "../../input_kind_enum.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
class Engine;
//--------
namespace sys {
//--------
// The main "loop
class GmMain final: public ecs::Sys {
public:		// types
	class PlayerAction final {
	public:		// variables
		//std::optional<PathDir> move_dir = std::nullopt;
		InputKind kind = InputKind::None;
	};
private:		// variables
	//std::optional<ecs::EntId>
	//	_player_id = std::nullopt;
	ecs::EntId _player_id = ecs::ENT_NULL_ID;
public:		// constants
	static const std::string
		KIND_STR;
public:		// functions
	GmMain() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(GmMain);
	virtual ~GmMain() = default;

	virtual std::string kind_str() const;
private:		// functions
	virtual void _init(ecs::Engine* ecs_engine);
public:		// functions
	virtual void tick(ecs::Engine* ecs_engine);
};
//--------
} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_sys_gm_main_class_hpp
