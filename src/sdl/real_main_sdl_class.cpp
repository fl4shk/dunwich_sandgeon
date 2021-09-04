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
			else if ((e.type == SDL_MOUSEBUTTONDOWN)
				|| (e.type = SDL_MOUSEBUTTONUP))
			{
				if (e.button.button == SDL_BUTTON_RIGHT)
				{
					_mouse_right_button_state()
						= (e.type == SDL_MOUSEBUTTONDOWN);
				}
			}
			else if (e.type == SDL_MOUSEWHEEL)
			{
				_scale = fabsf(_scale
					+ ((-static_cast<float>(e.wheel.y))
						* SCALE_MUL_AMOUNT));
				//fprintf(stdout, "Change _scale: %f\n", _scale);
				_update_logical_size_2d();
				_update_renderer_scale_etc();
			}
			else if (e.type == SDL_WINDOWEVENT)
			{
				_update_renderer_scale_etc();
			}
		}

		_update_engine_key_status();
		if (_mouse_right_button_state.has_changed()
			&& _mouse_right_button_state())
		{
			if (!_fullscreen)
			{
				if (SDL_SetWindowFullscreen(_window,
					SDL_WINDOW_FULLSCREEN))
				{
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
						"Couldn't switch to fullscreen: %s",
						SDL_GetError());
					exit(1);
				}
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
			}

			_fullscreen = !_fullscreen;
		}

		// Draw a black background
		SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xff);
		SDL_RenderFillRect(_renderer, nullptr);

		//for (size_t j=0; j<Window::SCREEN_SIZE_2D.y; ++j)
		//{
		//	for (size_t i=0; i<Window::SCREEN_SIZE_2D.x; ++i)
		//	{
		//		_text_handler.draw_char
		//	}
		//}

		_text_handler.draw_char('@', 
			game_engine::FgBgColorPair(FontColor::White, FontColor::Blue),
			PosVec2(0, 0));

		_text_handler.draw_char('@', FontColor::Red, PosVec2(1, 0));
		_text_handler.draw_char('@', FontColor::Green, PosVec2(2, 0));
		_text_handler.draw_char('@', FontColor::Brown, PosVec2(3, 0));
		_text_handler.draw_char('@', FontColor::Yellow, PosVec2(4, 0));

		_text_handler.draw_char('@', FontColor::Blue, PosVec2(5, 0));
		_text_handler.draw_char('@', FontColor::Purple, PosVec2(6, 0));
		_text_handler.draw_char('@', FontColor::Cyan, PosVec2(7, 0));
		_text_handler.draw_char('@', FontColor::Gray, PosVec2(8, 0));

		SDL_RenderPresent(_renderer);
		//SDL_Delay(10'000);
	}
	//--------
	exit(0);
	//--------
}

void RealMainSdl::_update_renderer_scale_etc()
{
	if (SDL_RenderSetScale(_renderer, _scale, _scale))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't scale the renderer: %s", SDL_GetError());
		exit(1);
	}
	if (SDL_RenderSetLogicalSize(_renderer, _logical_size_2d.x,
		_logical_size_2d.y))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't set renderer logical size: %s", SDL_GetError());
		exit(1);
	}
}
void RealMainSdl::_update_logical_size_2d()
{
	//_logical_size_2d.x = game_engine::Window::SCREEN_SIZE_2D.x
	//	* TextHandlerSdl::TILE_SIZE_2D.x * zoom();
	//_logical_size_2d.y = game_engine::Window::SCREEN_SIZE_2D.y
	//	* TextHandlerSdl::TILE_SIZE_2D.y * zoom();

	_logical_size_2d.x = game_engine::Window::SCREEN_SIZE_2D.x
		* TextHandlerSdl::TILE_SIZE_2D.x * _scale;
	_logical_size_2d.y = game_engine::Window::SCREEN_SIZE_2D.y
		* TextHandlerSdl::TILE_SIZE_2D.y * _scale;
}

void RealMainSdl::_update_engine_key_status() const
{
	auto& key_status = game_engine::engine.key_status;

	auto update_key_status
		= [this](PrevCurrPair<bool>& key_status_down,
		SDL_Keycode sym) -> void
	{
		if (_key_status_map.contains(sym))
		{
			key_status_down.back_up_and_update
				(_key_status_map.at(sym).down.prev());
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

	update_key_status(key_status.mod_1_l, SDLK_LSHIFT);
	update_key_status(key_status.mod_2_l, SDLK_LCTRL);

	update_key_status(key_status.mod_1_r, SDLK_RSHIFT);
	update_key_status(key_status.mod_2_r, SDLK_RCTRL);

	update_key_status(key_status.start, SDLK_RETURN);
	update_key_status(key_status.select, SDLK_ESCAPE);
}

} // namespace io
} // namespace dungwich_sandeon
