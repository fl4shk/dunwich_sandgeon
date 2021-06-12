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
		return 1;
	}
	sdl::QuitUponDtor quit_upon_dtor;

	sdl::prevent_dpi_scaling_issues();

	_zoom = DEF_ZOOM;
	_update_window_size_2d();

	_window = SDL_CreateWindow("Dungwich Sandeon",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_window_size_2d.x, _window_size_2d.y, SDL_WINDOW_RESIZABLE);
	if (!_window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't create window: %s", SDL_GetError());
		return 1;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (!_renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't create renderer: %s", SDL_GetError());
		return 1;
	}

	if (!_text_handler.init(_renderer, _zoom))
	{
		return 1;
	}

	//--------
	bool quit = false;
	while (!quit)
	{
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (handle_key_events(e, _key_status_map));
		}

		// Draw a black background
		SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xff);
		SDL_RenderFillRect(_renderer, nullptr);
		//_text_handler.draw_char('@', FontColor::White, PosVec2(0, 0));

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
	return 0;
	//--------
}

void RealMainSdl::_update_window_size_2d()
{
	_window_size_2d.x = game_engine::Screen::SIZE_2D.x
		* TextHandlerSdl::TILE_SIZE_2D.x * zoom();
	_window_size_2d.y = game_engine::Screen::SIZE_2D.y
		* TextHandlerSdl::TILE_SIZE_2D.y * zoom();
}

} // namespace io

} // namespace dungwich_sandeon
