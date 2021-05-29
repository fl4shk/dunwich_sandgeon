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
#include "text_handler_sdl_class.hpp"

namespace dungwich_sandeon
{

class RealMainSdl final
{
public:		// types
	enum class InputKind
	{
		MoveLeft,
		MoveUp,
		MoveRight,
		MoveDown,
		TargetEnemy,
		TargetItem,

		ExitMenu,
		OpenInvMenu,
		OpenSaveMenu,

		ZoomIn,
		ZoomOut,
	};
	using FontColor = TextHandlerSdl::FontColor;
public:		// constants
	// These constants have values in amount of tilemap entries
	static const Vec2<int> SCREEN_TM_SIZE_2D, PLAYFIELD_TM_POS,
		PLAYFIELD_TM_SIZE_2D;
	// Default values for some member variables
	static constexpr int DEF_ZOOM = 2;
private:		// variables
	Vec2<int> _screen_size_2d;
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

private:		// functions
};

} // namespace dungwich_sandeon

#endif		// src_real_main_sdl_class_hpp
