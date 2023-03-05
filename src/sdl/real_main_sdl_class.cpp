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

#include "real_main_sdl_class.hpp"
#include "../game_engine/global_shape_constants_etc.hpp"

namespace dunwich_sandgeon {
namespace io {
//--------
RealMainSdl::RealMainSdl(i32 argc, char** argv)
	: _engine(argc, argv) {
	game_engine::engine = &_engine;
	//_engine.dbg_check_ecs_engine();

	//_temp_engine.dbg_check_ecs_engine();
	//_temp_engine_1.dbg_check_ecs_engine();
}

i32 RealMainSdl::run() {
	//--------
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't initialize SDL: %s", SDL_GetError());
		exit(1);
	}
	sdl::QuitUponDtor quit_upon_dtor;

	sdl::prevent_dpi_scaling_issues();

	_global_timer_id = SDL_AddTimer(GLOBAL_TIMER_DELAY,
		&_global_timer_callback, this);

	//_zoom = DEF_ZOOM;

	_update_logical_size_2d();

	_window = SDL_CreateWindow("Dunwich Sandgeon",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_logical_size_2d.x, _logical_size_2d.y, SDL_WINDOW_RESIZABLE);
	if (!_window) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't create window: %s", SDL_GetError());
		exit(1);
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	//_renderer = SDL_CreateRenderer(_window, -1, 0);
	if (!_renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't create renderer: %s", SDL_GetError());
		exit(1);
	}
	if (SDL_RenderSetIntegerScale(_renderer, SDL_FALSE)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't set renderer integer size: %s", SDL_GetError());
		exit(1);
	}
	//_set_scale_etc(SCALE_DEFAULT_VAL);
	//SDL_SetWindowSize(_window, _logical_size_2d.x, _logical_size_2d.y);
	if (
		SDL_RenderSetLogicalSize(_renderer, _logical_size_2d.x,
		_logical_size_2d.y)
	) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't set renderer logical size: %s", SDL_GetError());
		exit(1);
	}

	_mouse_right_button_state() = false;
	_mouse_right_button_state.back_up();

	//if (!_text_handler.init(_renderer, _zoom))
	if (!_text_handler.init(_renderer)) {
		exit(1);
	}

	//auto draw_test_chars = [this]() -> void {
	//	_text_handler.draw_char(
	//		'@', {FontColor::White, FontColor::Blue}, IntVec2(0, 0)
	//	);

	//	_text_handler.draw_char('@', FontColor::Red, IntVec2(1, 0));
	//	_text_handler.draw_char('@', FontColor::Green, IntVec2(2, 0));
	//	_text_handler.draw_char('@', FontColor::Brown, IntVec2(3, 0));
	//	_text_handler.draw_char('@', FontColor::Yellow, IntVec2(4, 0));

	//	_text_handler.draw_char('@', FontColor::Blue, IntVec2(5, 0));
	//	_text_handler.draw_char('@', FontColor::Purple, IntVec2(6, 0));
	//	_text_handler.draw_char('@', FontColor::Cyan, IntVec2(7, 0));
	//	_text_handler.draw_char('@', FontColor::White, IntVec2(8, 0));
	//	_text_handler.draw_char('@', FontColor::Gray, IntVec2(9, 0));
	//	//_text_handler.draw_char('@', FontColor::LightGray, IntVec2(9, 0));

	//	//_text_handler.draw_char('@', FontColor::DarkGray, IntVec2(10, 0));
	//};
	//--------
	//auto
		//& screen_window = _engine.screen_window;
		//& aux_window = _engine.aux_window,
		//& pfield_window = _engine.pfield_window,
		//& log_window = _engine.log_window,
		//& hud_window = _engine.hud_window,
		//& popup_window = _engine.popup_window,
		//& yes_no_window = _engine.yes_no_window;
	//MsgLog
	//	msg_log(
	//		{
	//			{
	//				RopePart("This is a red str. asdf asdf asdf asdf", FontColor::Red,
	//					FontColor::Gray),
	//				//RopePart("Red string 2", FontColor::Red,
	//				//	FontColor::Gray),
	//			},
	//			{
	//				RopePart("This is a green str.", FontColor::Green,
	//					FontColor::Gray),
	//			},
	//			{
	//				RopePart("asdf jkl;", FontColor::Brown,
	//					FontColor::White),
	//			},
	//			//{
	//			//	RopePart("Blue str!", FontColor::Blue,
	//			//		FontColor::Gray),
	//			//},
	//			//{
	//			//	RopePart("Gray str! This is a gray string!",
	//			//		FontColor::Gray, FontColor::Gray),
	//			//},
	//		},
	//		MsgLog::DEFAULT_INTERNAL_HEIGHT,
	//		log_window.size_2d(),
	//		Vec2(true, true)
	//	);
	////msg_log.set_scroll(2);
	//log_window.draw(msg_log);
	//--------
	bool quit = false;
	while (!quit) {
		auto
			& screen_window = _engine.screen_window;
		_mouse_right_button_state.back_up();

		bool tick_engine_now = false,
			ksm_perf_total_backup = true;

		SDL_Event e;

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (handle_key_events(e, _key_status_umap,
				ksm_perf_total_backup)) {
			} else if (
				(e.type == SDL_MOUSEBUTTONDOWN)
				|| (e.type == SDL_MOUSEBUTTONUP)
			) {
				if (e.button.button == SDL_BUTTON_RIGHT) {
					_mouse_right_button_state.back_up_and_update
						(e.type == SDL_MOUSEBUTTONDOWN);
				}
			} else if (e.type == SDL_USEREVENT) {
				//printout("Global Timer Interval: ",
				//	_global_timer_interval, "\n");
				_did_handle_global_timer = true;
				tick_engine_now = true;
			}
		}

		if (tick_engine_now) {
			_update_engine_key_status();
			_engine.tick();
		}

		//_update_engine_key_status();

		//if (_engine.key_status.any_key_went_down_just_now()) {
		//	_engine.tick();
		//}

		// Handle switching into or out of fullscreen.
		if (
			_mouse_right_button_state.has_changed()
			&& _mouse_right_button_state()
		) {
			if (!_fullscreen) {
				if (
					SDL_SetWindowFullscreen(_window,
					SDL_WINDOW_FULLSCREEN_DESKTOP)
				) {
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
						"Couldn't switch to fullscreen: %s",
						SDL_GetError());
					exit(1);
				}
			} else { // if (_fullscreen)
				if (SDL_SetWindowFullscreen(_window, 0)) {
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
						"Couldn't switch to windowed (non-fullscreen): %s",
						SDL_GetError());
					exit(1);
				}
			}

			_fullscreen = !_fullscreen;
		}

		// Draw a black background
		SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xff);
		SDL_RenderFillRect(_renderer, nullptr);

		// Draw tiles/graphics here.

		//yes_no_window.clear();
		//yes_no_window.draw(_engine.yes_no_menu);

		//screen_window.clear();
		//screen_window.draw(yes_no_window);
		////playfield_window.draw(msg_log);

		//// Temporary drawing into `screen_window`.
		//screen_window.draw(playfield_window, true);
		//screen_window.draw(log_window, true);
		//screen_window.draw(hud_window, true);
		//////screen_window.draw(aux_window);
		//////screen_window.draw(popup_window);
		////screen_window.draw(yes_no_window);

		for (i32 j=0; j<screen_window.w_border_size_2d().y; ++j) {
			for (i32 i=0; i<screen_window.w_border_size_2d().x; ++i) {
				const IntVec2 wb_pos(i, j);
				//const ecs::EntId id
				//	= screen_window.with_border_ent_id_at(wb_pos);
				const auto& drawable_data
					= screen_window.w_border_drawable_data_at(wb_pos);

				if (_engine.game_options.grayscale) {
					_text_handler.draw_char(drawable_data.c,
						drawable_data.gs_color_pair, wb_pos);
				} else { // if (!_engine.game_options.grayscale)
					_text_handler.draw_char(drawable_data.c,
						drawable_data.color_pair, wb_pos);
				}
			}
		}

		//draw_test_chars();

		SDL_RenderPresent(_renderer);
		//SDL_Delay(10'000);
	}
	//--------
	exit(0);
	//--------
}

Uint32 RealMainSdl::_global_timer_callback(Uint32 interval, void* self) {
	// This function creates data in an SDL user event because this
	// function will be called in a separate thread from the main one.

	auto casted_self = reinterpret_cast<RealMainSdl*>(self);

	if (casted_self->_did_handle_global_timer) {
		casted_self->_did_handle_global_timer = false;
		casted_self->_global_timer_interval = interval;

		SDL_Event event;
		SDL_UserEvent userevent;

		userevent.type = SDL_USEREVENT;
		userevent.code = 0;
		userevent.data1 = nullptr;
		userevent.data2 = nullptr;

		event.type = SDL_USEREVENT;
		event.user = userevent;

		SDL_PushEvent(&event);
	}

	// Used to prevent the timer from being cancelled.
	return interval;
}

//void RealMainSdl::_update_logical_size_2d(bool use_default_scale)
void RealMainSdl::_update_logical_size_2d() {
	//_logical_size_2d.x = game_engine::W_BRDR_SCREEN_SIZE_2D.x
	//	* TextHandlerSdl::TILE_SIZE_2D.x * zoom();
	//_logical_size_2d.y = game_engine::W_BRDR_SCREEN_SIZE_2D.y
	//	* TextHandlerSdl::TILE_SIZE_2D.y * zoom();

	//const float TEMP_SCALE
	//	= 1.0f / ((!use_default_scale) ? _scale : SCALE_DEFAULT_VAL);
	//const float TEMP_SCALE
	//	= (!use_default_scale) ? _scale : SCALE_DEFAULT_VAL;

	//_logical_size_2d.x
	//	= (game_engine::W_BRDR_SCREEN_SIZE_2D.x + 2)
	//	* TextHandlerSdl::TILE_SIZE_2D.x * TEMP_SCALE;
	//_logical_size_2d.y
	//	= (game_engine::W_BRDR_SCREEN_SIZE_2D.y + 2)
	//	* TextHandlerSdl::TILE_SIZE_2D.y * TEMP_SCALE;

	//_logical_size_2d.x
	//	= (game_engine::W_BRDR_SCREEN_SIZE_2D.x + 2)
	//	* TextHandlerSdl::TILE_SIZE_2D.x;
	//_logical_size_2d.y
	//	= (game_engine::W_BRDR_SCREEN_SIZE_2D.y + 2)
	//	* TextHandlerSdl::TILE_SIZE_2D.y;
	_logical_size_2d.x = game_engine::W_BRDR_SCREEN_SIZE_2D.x
		* TextHandlerSdl::TILE_SIZE_2D.x;
	_logical_size_2d.y = game_engine::W_BRDR_SCREEN_SIZE_2D.y
		* TextHandlerSdl::TILE_SIZE_2D.y;
}
//void RealMainSdl::_update_renderer_scale_etc(bool use_default_scale) {
//	const float TEMP_SCALE
//		= 1.0f / ((!use_default_scale) ? _scale : SCALE_DEFAULT_VAL);
//	if (SDL_RenderSetScale(_renderer, TEMP_SCALE, TEMP_SCALE)) {
//		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
//			"Couldn't scale the renderer: %s", SDL_GetError());
//		exit(1);
//	}
//
//	if (
//		SDL_RenderSetLogicalSize(_renderer, _logical_size_2d.x,
//		_logical_size_2d.y)
//	) {
//		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
//			"Couldn't set renderer logical size: %s", SDL_GetError());
//		exit(1);
//	}
//}

void RealMainSdl::_update_engine_key_status() {
	//auto& key_status = _engine.key_status;

	//auto update_key_status
	//	= [this](PrevCurrPair<bool>& key_status_down, SDL_Keycode sym)
	//	-> void {
	//	if (_key_status_umap.contains(sym)) {
	//		//key_status_down() = _key_status_umap.at(sym).down.prev();
	//		key_status_down.back_up_and_update(
	//			_key_status_umap.at(sym).down()
	//		);
	//	}
	//};
	// Hard code the keybindings for now.
	//update_key_status(key_status.at(KeyStatus::LeftL), SDLK_s);
	//update_key_status(key_status.at(KeyStatus::UpL), SDLK_e);
	//update_key_status(key_status.at(KeyStatus::RightL), SDLK_f);
	//update_key_status(key_status.at(KeyStatus::DownL), SDLK_d);

	//update_key_status(key_status.at(KeyStatus::LeftR), SDLK_j);
	//update_key_status(key_status.at(KeyStatus::UpR), SDLK_i);
	//update_key_status(key_status.at(KeyStatus::RightR), SDLK_l);
	//update_key_status(key_status.at(KeyStatus::DownR), SDLK_k);

	//update_key_status(key_status.at(KeyStatus::ShoulderL), SDLK_a);
	//update_key_status(key_status.at(KeyStatus::ShoulderR), SDLK_SEMICOLON);

	//update_key_status(key_status.at(KeyStatus::Start), SDLK_RETURN);
	//update_key_status(key_status.at(KeyStatus::Select), SDLK_ESCAPE);

	_engine.key_status.update(_key_status_umap,
		sdl::EngineKeycUmap<KeyKind>({
			{KeyKind::LeftL, SDLK_s},
			{KeyKind::UpL, SDLK_e},
			{KeyKind::RightL, SDLK_f},
			{KeyKind::DownL, SDLK_d},

			{KeyKind::LeftR, SDLK_j},
			{KeyKind::UpR, SDLK_i},
			{KeyKind::RightR, SDLK_l},
			{KeyKind::DownR, SDLK_k},

			{KeyKind::ShoulderLB, SDLK_a},
			{KeyKind::ShoulderLT, SDLK_q},
			{KeyKind::ShoulderRB, SDLK_SEMICOLON},
			{KeyKind::ShoulderRT, SDLK_p},

			{KeyKind::Start, SDLK_RETURN},
			{KeyKind::Select, SDLK_ESCAPE},
		})
	);
}
//--------
} // namespace io
} // namespace dunwich_sandgeon
