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

#ifndef src_game_engine_game_options_class_hpp
#define src_game_engine_game_options_class_hpp

// src/game_engine/game_options_class.hpp

#include "../misc_includes.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{

class GameOptions final
{
public:		// variables
	#define MEMB_LIST_GAME_OPTIONS(X) \
		X(grayscale, std::nullopt)
	bool grayscale = false;
public:		// functions
	GameOptions();
	GameOptions(bool s_grayscale);
	GameOptions(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(GameOptions);
	~GameOptions();

	operator Json::Value () const;
};

} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_game_options_class_hpp
