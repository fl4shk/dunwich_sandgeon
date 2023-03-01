// This file is part of Dunwich Sandgeon.
// 
// Copyright 2023 FL4SHK
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

#ifndef src_game_engine_comp_drawable_data_map_hpp
#define src_game_engine_comp_drawable_data_map_hpp

// src/game_engine/comp/drawable_data_umap.hpp

#include "../../misc_includes.hpp"
#include "general_comp_classes.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
namespace comp {
//--------
const std::unordered_map<std::string, Drawable::Data>& drawable_data_umap();
template<ecs::EngineDerivedFromComp T>
inline ecs::CompSptr make_drawable() {
	return ecs::CompSptr(new Drawable
		(drawable_data_umap().at(T::KIND_STR)));
}
//--------
} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_comp_drawable_data_map_hpp
