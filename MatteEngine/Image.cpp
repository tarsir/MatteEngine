#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"
#include "Image.h"
#include "Color.h"
#include "Logging.h"
#include "spdlog\spdlog.h"

auto image_logger = spdlog::stdout_color_mt("Image.h");
SDL_PixelFormat* screen_pixel_format;


bool image_init() {
	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		return false;
	}

	return true;
}

SDL_Surface* load_image_as_surface(std::string path) {
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
	image_logger->info("made a dude");

	return final_surface;
}

SDL_Texture* load_image_as_texture(std::string path, Graphics* gfx = Graphics::getInstance()) {
	return SDL_CreateTextureFromSurface(gfx->getRenderer(), load_image_as_surface(path));
}

void fill_surface(SDL_Surface* target_sfc) {
	if (SDL_FillRect(target_sfc, NULL, SDL_MapRGB(screen_pixel_format, 24, 24, 24)) != 0) {
		image_logger->error("Could not fill surface with color");
	}
}

void add_transparency_to_surface(SDL_Surface* target_surface, Color& transparent_color) {
	Uint32 transparency_key = color_to_rgb_key(target_surface->format, transparent_color);
	if (SDL_SetColorKey(target_surface, SDL_TRUE, transparency_key) < 0) {
		image_logger->error("Setting transparency failed");
	}
}

/*
	Set the global pixel format.

	Without a call to this function, the pixel format will not be set, and 
	things are liable to explode.
 */
void set_pixel_format(SDL_PixelFormat* new_pixel_format) {
	image_logger->debug("Setting pixel format.");
	screen_pixel_format = new_pixel_format;
}