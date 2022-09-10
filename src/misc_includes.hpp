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
#include "liborangepower_src/strings/string_extra_stuff.hpp"
#include "liborangepower_src/math/vec2_classes.hpp"
#include "liborangepower_src/math/vec3_classes.hpp"
#include "liborangepower_src/math/shape_2d_classes.hpp"
#include "liborangepower_src/containers/prev_curr_pair_classes.hpp"
#include "liborangepower_src/json_stuff/json_stuff.hpp"
#include "liborangepower_src/binser/serialize_funcs.hpp"
#include "liborangepower_src/binser_plus_json_stuff/bv_to_jv_casting_func.hpp"
#include "liborangepower_src/game_stuff/ecs_classes.hpp"
#include "liborangepower_src/game_stuff/engine_key_status_class.hpp"
#include "liborangepower_src/metaprog_defines.hpp"
#include "liborangepower_src/time/time_stuff.hpp"
#include "liborangepower_src/gfx/plot_stuff.hpp"

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
//using namespace liborangepower::math;
namespace math = liborangepower::math;
using math::Vec2;
using math::Vec3;
using namespace liborangepower::time;
namespace json = liborangepower::json;
namespace binser = liborangepower::binser;
namespace sdl = liborangepower::sdl;
using sdl::KeycModPair, sdl::KeyStatus;
using liborangepower::game::EngineKeyStatus;
namespace ecs = liborangepower::game::ecs;

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <initializer_list>
#include <fstream>
#include <deque>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <functional>
#include <type_traits>
#include <concepts>

#include <pcg_random.hpp>

#endif		// src_misc_includes_hpp
