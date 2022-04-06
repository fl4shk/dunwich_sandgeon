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

#ifndef src_real_main_sdl_class_hpp
#define src_real_main_sdl_class_hpp

// src/sdl/real_main_sdl_class.hpp

#include "../misc_includes.hpp"
#include "../input_kind_enum.hpp"
#include "../game_engine/engine_class.hpp"
#include "text_handler_sdl_class.hpp"

namespace dunwich_sandgeon
{
namespace io
{

class RealMainSdl final
{
public:		// types
	using FontColor = game_engine::FontColor;
	using FgBgColorPair = game_engine::FgBgColorPair;
	using Window = game_engine::Window;
	using Engine = game_engine::Engine;
	using KeyKind = game_engine::KeyKind;

	using Menu = game_engine::Menu;
	using MsgLog = game_engine::MsgLog;
	using RopePart = game_engine::RopePart;
	using Rope = game_engine::Rope;
	using RopeDeque = game_engine::RopeDeque;
public:		// constants
	// 10 ms global timer for ticking the game engine
	static constexpr Uint32 GLOBAL_TIMER_DELAY = 10u;

	//static constexpr int DEF_ZOOM = 2;
	//static constexpr float
	//	SCALE_MUL_VAL = 0.1f, SCALE_DEFAULT_VAL = 1.0f;
private:		// variables
	SDL_TimerID _global_timer_id;
	bool _did_handle_global_timer = true;
	Uint32 _global_timer_interval = 0;
	PosVec2 _logical_size_2d;
	//int _zoom = DEF_ZOOM;
	//float _scale = SCALE_DEFAULT_VAL;
	Engine _engine;
	bool _fullscreen = false;
	sdl::Window _window;
	sdl::Renderer _renderer;
	sdl::KeyStatusMap _key_status_map;
	PrevCurrPair<bool> _mouse_right_button_state;
	TextHandlerSdl _text_handler;
public:		// functions
	RealMainSdl(int argc, char** argv);
	~RealMainSdl() = default;

	int run();

	//GEN_GETTER_BY_VAL(zoom);
private:		// functions
	static Uint32 _global_timer_callback(Uint32 interval, void* self);
	//inline void _set_scale_etc(float n_scale)
	//{
	//	_scale = n_scale;
	//	_update_logical_size_2d();
	//	_update_renderer_scale_etc();
	//}
	//void _update_logical_size_2d(bool use_default_scale=true);
	void _update_logical_size_2d();
	//void _update_renderer_scale_etc(bool use_default_scale=true);
	void _update_engine_key_status();
};

} // namespace io
} // namespace dunwich_sandgeon

#endif		// src_real_main_sdl_class_hpp
