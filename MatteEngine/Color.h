#pragma once
#include <SDL.h>

struct Color {
	uint8_t red, green, blue;
};

Uint32 color_to_rgb_key(SDL_PixelFormat*, Color&);