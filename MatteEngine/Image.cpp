#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "spdlog\spdlog.h"
#include "Image.h"
#include "Color.h"
#include "Logging.h"

auto image_logger = spdlog::stdout_color_mt("Image.h");
SDL_PixelFormat* screen_pixel_format;


bool image_init() {
	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		return false;
	}

	return true;
}

SDL_Surface* load_image(std::string path) {
	SDL_Surface* final_surface = NULL;

	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == NULL) {
		image_logger->error("Could not load image at: {}\nDetailed error: {}", path, IMG_GetError());
	} else {
		final_surface = SDL_ConvertSurface(loaded_surface, screen_pixel_format, NULL);
		if (final_surface == NULL) {
			image_logger->error("Could not optimize image at: {}\nDetailed error: {}", path, SDL_GetError());
		}
		
		SDL_FreeSurface(loaded_surface);
	}

	return final_surface;
}

void add_transparency_to_surface(SDL_Surface* target_surface, Color& transparent_color) {
	Uint32 transparency_key = color_to_rgb_key(target_surface->format, transparent_color);
	if (SDL_SetColorKey(target_surface, SDL_TRUE, transparency_key) < 0) {
		throw std::runtime_error("Setting transparency failed");
	}
}

void set_pixel_format(SDL_PixelFormat* new_pixel_format) {
	image_logger->debug("Setting pixel format.");
	screen_pixel_format = new_pixel_format;
}