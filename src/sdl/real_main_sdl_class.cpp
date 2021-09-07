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

#include "real_main_sdl_class.hpp"

namespace dungwich_sandeon
{
namespace io
{

RealMainSdl::RealMainSdl()
{
	game_engine::engine = &_engine;
	//_engine.dbg_check_ecs_engine();

	//_temp_engine.dbg_check_ecs_engine();
	//_temp_engine_1.dbg_check_ecs_engine();
}

int RealMainSdl::run()
{
	//--------
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't initialize SDL: %s", SDL_GetError());
		exit(1);
	}
	sdl::QuitUponDtor quit_upon_dtor;

	sdl::prevent_dpi_scaling_issues();

	//_zoom = DEF_ZOOM;

	_update_logical_size_2d();

	_window = SDL_CreateWindow("Dungwich Sandeon",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_logical_size_2d.x, _logical_size_2d.y, SDL_WINDOW_RESIZABLE);
	if (!_window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't create window: %s", SDL_GetError());
		exit(1);
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	//_renderer = SDL_CreateRenderer(_window, -1, 0);
	if (!_renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't create renderer: %s", SDL_GetError());
		exit(1);
	}
	if (SDL_RenderSetIntegerScale(_renderer, SDL_FALSE))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't set renderer integer size: %s", SDL_GetError());
		exit(1);
	}
	//_set_scale_etc(SCALE_DEFAULT_VAL);
	//SDL_SetWindowSize(_window, _logical_size_2d.x, _logical_size_2d.y);
	if (SDL_RenderSetLogicalSize(_renderer, _logical_size_2d.x,
		_logical_size_2d.y))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't set renderer logical size: %s", SDL_GetError());
		exit(1);
	}

	_mouse_right_button_state() = false;
	_mouse_right_button_state.back_up();

	//if (!_text_handler.init(_renderer, _zoom))
	if (!_text_handler.init(_renderer))
	{
		exit(1);
	}

	//--------
	bool quit = false;
	while (!quit)
	{
		_mouse_right_button_state.back_up();

		SDL_Event e;

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (handle_key_events(e, _key_status_map));
			//else if (e.type == SDL_MOUSEWHEEL)
			//{
			//	if (!_fullscreen)
			//	{
			//		_set_scale_etc(fabsf(_scale
			//			+ ((-static_cast<float>(e.wheel.y))
			//				* SCALE_MUL_VAL)));
			//	}
			//}
			else if ((e.type == SDL_MOUSEBUTTONDOWN)
				|| (e.type = SDL_MOUSEBUTTONUP))
			{
				//if (e.button.button == SDL_BUTTON_MIDDLE)
				//{
				//	if (e.type == SDL_MOUSEBUTTONDOWN)
				//	{
				//		_set_scale_etc(SCALE_DEFAULT_VAL);
				//	}
				//}
				//else
				if (e.button.button == SDL_BUTTON_RIGHT)
				{
					_mouse_right_button_state.back_up_and_update
						(e.type == SDL_MOUSEBUTTONDOWN);
				}
			}
			//else if (e.type == SDL_WINDOWEVENT)
			//{
			//	_update_renderer_scale_etc();
			//}
		}

		_update_engine_key_status();

		// Handle switching into or out of fullscreen.
		if (_mouse_right_button_state.has_changed()
			&& _mouse_right_button_state())
		{
			if (!_fullscreen)
			{
				if (SDL_SetWindowFullscreen(_window,
					SDL_WINDOW_FULLSCREEN_DESKTOP))
				{
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
						"Couldn't switch to fullscreen: %s",
						SDL_GetError());
					exit(1);
				}

				//_update_logical_size_2d(true);
				//_update_renderer_scale_etc(true);
			}
			else // if (_fullscreen)
			{
				if (SDL_SetWindowFullscreen(_window, 0))
				{
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
						"Couldn't switch to windowed (non-fullscreen): %s",
						SDL_GetError());
					exit(1);
				}

				//_update_logical_size_2d();
				//_update_renderer_scale_etc();
			}

			_fullscreen = !_fullscreen;
		}

		// Draw a black background
		SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xff);
		SDL_RenderFillRect(_renderer, nullptr);

		// Draw tiles/graphics here.
		auto& screen_window = _engine.screen_window;

		for (size_t j=0; j<screen_window.with_border_size_2d().y; ++j)
		{
			for (size_t i=0; i<screen_window.with_border_size_2d().x; ++i)
			{
				auto& ecs_engine = _engine.ecs_engine;
				const PosVec2 wb_pos(i, j);
				const ecs::EntId id
					= screen_window.with_border_ent_id_at(wb_pos);

				if (ecs_engine.has_ent_with_comp(id,
					game_engine::comp::Drawable::KIND_STR))
				{
					//auto& drawable = static_cast<comp::Drawable*>
					//	(ecs_engine.comp_map(id).at
					//		(comp::Drawable::KIND_STR).get());
					auto drawable = ecs_engine
						.casted_comp_at<game_engine::comp::Drawable>(id,
							game_engine::comp::Drawable::KIND_STR);
					_text_handler.draw_char(drawable->data.c,
						drawable->data.color_pair, wb_pos);
				}
			}
		}

		//_text_handler.draw_char('@', 
		//	FgBgColorPair(FontColor::White, FontColor::Blue),
		//	PosVec2(0, 0));

		//_text_handler.draw_char('@', FontColor::Red, PosVec2(1, 0));
		//_text_handler.draw_char('@', FontColor::Green, PosVec2(2, 0));
		//_text_handler.draw_char('@', FontColor::Brown, PosVec2(3, 0));
		//_text_handler.draw_char('@', FontColor::Yellow, PosVec2(4, 0));

		//_text_handler.draw_char('@', FontColor::Blue, PosVec2(5, 0));
		//_text_handler.draw_char('@', FontColor::Purple, PosVec2(6, 0));
		//_text_handler.draw_char('@', FontColor::Cyan, PosVec2(7, 0));
		//_text_handler.draw_char('@', FontColor::Gray, PosVec2(8, 0));

		SDL_RenderPresent(_renderer);
		//SDL_Delay(10'000);
	}
	//--------
	exit(0);
	//--------
}

//void RealMainSdl::_update_logical_size_2d(bool use_default_scale)
void RealMainSdl::_update_logical_size_2d()
{
	//_logical_size_2d.x = game_engine::Window::WITH_BORDER_SCREEN_SIZE_2D.x
	//	* TextHandlerSdl::TILE_SIZE_2D.x * zoom();
	//_logical_size_2d.y = game_engine::Window::WITH_BORDER_SCREEN_SIZE_2D.y
	//	* TextHandlerSdl::TILE_SIZE_2D.y * zoom();

	//const float TEMP_SCALE
	//	= 1.0f / ((!use_default_scale) ? _scale : SCALE_DEFAULT_VAL);
	//const float TEMP_SCALE
	//	= (!use_default_scale) ? _scale : SCALE_DEFAULT_VAL;

	//_logical_size_2d.x
	//	= (game_engine::Window::WITH_BORDER_SCREEN_SIZE_2D.x + 2)
	//	* TextHandlerSdl::TILE_SIZE_2D.x * TEMP_SCALE;
	//_logical_size_2d.y
	//	= (game_engine::Window::WITH_BORDER_SCREEN_SIZE_2D.y + 2)
	//	* TextHandlerSdl::TILE_SIZE_2D.y * TEMP_SCALE;

	//_logical_size_2d.x
	//	= (game_engine::Window::WITH_BORDER_SCREEN_SIZE_2D.x + 2)
	//	* TextHandlerSdl::TILE_SIZE_2D.x;
	//_logical_size_2d.y
	//	= (game_engine::Window::WITH_BORDER_SCREEN_SIZE_2D.y + 2)
	//	* TextHandlerSdl::TILE_SIZE_2D.y;
	_logical_size_2d.x = game_engine::Window::WITH_BORDER_SCREEN_SIZE_2D.x
		* TextHandlerSdl::TILE_SIZE_2D.x;
	_logical_size_2d.y = game_engine::Window::WITH_BORDER_SCREEN_SIZE_2D.y
		* TextHandlerSdl::TILE_SIZE_2D.y;
}
//void RealMainSdl::_update_renderer_scale_etc(bool use_default_scale)
//{
//	const float TEMP_SCALE
//		= 1.0f / ((!use_default_scale) ? _scale : SCALE_DEFAULT_VAL);
//	if (SDL_RenderSetScale(_renderer, TEMP_SCALE, TEMP_SCALE))
//	{
//		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
//			"Couldn't scale the renderer: %s", SDL_GetError());
//		exit(1);
//	}
//
//	if (SDL_RenderSetLogicalSize(_renderer, _logical_size_2d.x,
//		_logical_size_2d.y))
//	{
//		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
//			"Couldn't set renderer logical size: %s", SDL_GetError());
//		exit(1);
//	}
//}

void RealMainSdl::_update_engine_key_status()
{
	auto& key_status = _engine.key_status;

	auto update_key_status
		= [this](PrevCurrPair<bool>& key_status_down,
		SDL_Keycode sym) -> void
	{
		if (_key_status_map.contains(sym))
		{
			key_status_down() = _key_status_map.at(sym).down.prev();
			key_status_down.back_up_and_update
				(_key_status_map.at(sym).down.curr());
		}
	};

	// Hard code the keybindings for now.
	update_key_status(key_status.left_l, SDLK_s);
	update_key_status(key_status.up_l, SDLK_e);
	update_key_status(key_status.right_l, SDLK_f);
	update_key_status(key_status.down_l, SDLK_d);

	update_key_status(key_status.left_r, SDLK_j);
	update_key_status(key_status.up_r, SDLK_i);
	update_key_status(key_status.right_r, SDLK_l);
	update_key_status(key_status.down_r, SDLK_k);

	update_key_status(key_status.shoulder_1_l, SDLK_LSHIFT);
	update_key_status(key_status.shoulder_2_l, SDLK_LCTRL);

	update_key_status(key_status.shoulder_1_r, SDLK_RSHIFT);
	update_key_status(key_status.shoulder_2_r, SDLK_RCTRL);

	update_key_status(key_status.start, SDLK_RETURN);
	update_key_status(key_status.select, SDLK_ESCAPE);
}

} // namespace io
} // namespace dungwich_sandeon
