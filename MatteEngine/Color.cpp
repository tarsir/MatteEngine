#include <SDL.h>
#include "Color.h"

Uint32 color_to_rgb_key(SDL_PixelFormat* format, Color& input_color) {
	return SDL_MapRGB(format, input_color.red, input_color.green, input_color.blue);
}