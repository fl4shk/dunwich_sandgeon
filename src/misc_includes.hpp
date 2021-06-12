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

#ifndef src_misc_includes_hpp
#define src_misc_includes_hpp

// src/misc_includes.hpp

#include "liborangepower_src/misc/misc_includes.hpp"
#include "liborangepower_src/misc/misc_output_classes.hpp"
#include "liborangepower_src/misc/misc_types.hpp"
#include "liborangepower_src/misc/misc_utility_funcs.hpp"
#include "liborangepower_src/misc/misc_bitwise_funcs.hpp"
#include "liborangepower_src/misc/misc_defines.hpp"
#include "liborangepower_src/gen_class_innards_defines.hpp"
#include "liborangepower_src/strings/string_conversion_stuff.hpp"
#include "liborangepower_src/containers/vec2_classes.hpp"
#include "liborangepower_src/containers/prev_curr_pair_classes.hpp"
#include "liborangepower_src/game_stuff/ecs_classes.hpp"

#include "liborangepower_src/sdl2/sdl.hpp"
#include "liborangepower_src/sdl2/dpi_stuff.hpp"
#include "liborangepower_src/sdl2/keyboard_stuff.hpp"
#include "liborangepower_src/sdl2/sdl_video.hpp"
#include "liborangepower_src/sdl2/sdl_render.hpp"
#include "liborangepower_src/sdl2/sdl_surface.hpp"
#include "liborangepower_src/sdl2/sdl_rect.hpp"
#include <SDL_events.h>

using namespace liborangepower::misc_output;
using namespace liborangepower::integer_types;
using namespace liborangepower::misc_util;
using namespace liborangepower::bitwise;
using namespace liborangepower::strings;
using namespace liborangepower::containers;
namespace sdl = liborangepower::sdl;
using sdl::KeycModPair, sdl::KeyStatus;
namespace ecs = liborangepower::game::ecs;

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <functional>
#include <type_traits>
#include <concepts>


#endif		// src_misc_includes_hpp
