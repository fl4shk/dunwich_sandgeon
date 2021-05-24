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

#include "real_main_class.hpp"

namespace dungwich_sandeon
{

const std::map<RealMain::Color, std::string> RealMain::COLOR_TO_STR_MAP
= {
	{RealMain::Color::White, "White"},
	{RealMain::Color::Red, "Red"},
	{RealMain::Color::Green, "Green"},
	{RealMain::Color::Brown, "Brown"},
	{RealMain::Color::Yellow, "Yellow"},
	{RealMain::Color::Blue, "Blue"},
	{RealMain::Color::Purple, "Purple"},
	{RealMain::Color::Cyan, "Cyan"},
	{RealMain::Color::Gray, "Gray"},
	{RealMain::Color::Lim, "Lim"},
};
int RealMain::run()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't initialize SDL: %s", SDL_GetError());
		return 1;
	}
	sdl::QuitUponDtor quit_upon_dtor;

	sdl::prevent_dpi_scaling_issues();

	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_RESIZABLE, &_window.self(), &_renderer.self()))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't create window and renderer: %s", SDL_GetError());
		return 1;
	}

	{
		sdl::Surface font_surface(SDL_LoadBMP("gfx/font.bmp"));
		if (!font_surface.self())
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Couldn't create window and renderer: %s", SDL_GetError());
			return 1;
		}

		for (auto color=Color::White;
			color!=Color::Lim;
			color=color_add(color, 1u))
		{
			_font_texture_map[color]
				= sdl::Texture(SDL_CreateTextureFromSurface(_renderer,
					font_surface));
		}
	}

	//--------
	if (SDL_SetTextureColorMod(_font_texture_map[Color::Red],
		0xcc, 0x00, 0x00) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font red: %s", SDL_GetError());
	}
	if (SDL_SetTextureColorMod(_font_texture_map[Color::Green],
		0x00, 0xcc, 0x00) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font green: %s", SDL_GetError());
	}
	if (SDL_SetTextureColorMod(_font_texture_map[Color::Brown],
		0xaa, 0x55, 0x00) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font brown: %s", SDL_GetError());
	}
	if (SDL_SetTextureColorMod(_font_texture_map[Color::Yellow],
		0xcc, 0xcc, 0x00) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font yellow: %s", SDL_GetError());
	}
	//--------
	if (SDL_SetTextureColorMod(_font_texture_map[Color::Blue],
		0x00, 0x00, 0xcc) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font blue: %s", SDL_GetError());
	}
	if (SDL_SetTextureColorMod(_font_texture_map[Color::Purple],
		0xcc, 0x00, 0xcc) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font purple: %s", SDL_GetError());
	}
	if (SDL_SetTextureColorMod(_font_texture_map[Color::Cyan],
		0x00, 0xcc, 0xcc) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font cyan: %s", SDL_GetError());
	}
	if (SDL_SetTextureColorMod(_font_texture_map[Color::Gray],
		0xaa, 0xaa, 0xaa) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"Couldn't color the font gray: %s", SDL_GetError());
	}
	//--------

	return 0;
}

} // namespace dungwich_sandeon
