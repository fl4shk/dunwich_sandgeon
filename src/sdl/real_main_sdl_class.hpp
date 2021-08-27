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

#ifndef src_real_main_sdl_class_hpp
#define src_real_main_sdl_class_hpp

// src/sdl/real_main_sdl_class.hpp

#include "../misc_includes.hpp"
#include "../input_kind_enum.hpp"
#include "../game_engine/engine_class.hpp"
#include "text_handler_sdl_class.hpp"

namespace dungwich_sandeon
{
namespace io
{

class RealMainSdl final
{
public:		// types
	using FontColor = game_engine::FontColor;
public:		// constants
	// Default values for some member variables
	static constexpr int DEF_ZOOM = 2;
private:		// variables
	PosVec2 _window_size_2d;
	int _zoom = DEF_ZOOM;
	sdl::Window _window;
	sdl::Renderer _renderer;
	sdl::KeyStatusMap _key_status_map;
	TextHandlerSdl _text_handler;
	InputKind _input_kind;
public:		// functions
	RealMainSdl() = default;
	~RealMainSdl() = default;

	int run();

	GEN_GETTER_BY_VAL(zoom);
private:		// functions
	void _update_window_size_2d();
};

} // namespace io
} // namespace dungwich_sandeon

#endif		// src_real_main_sdl_class_hpp
