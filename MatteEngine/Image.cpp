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

SDL_Texture* load_image_as_texture(std::string path, Graphics* gfx = Graphics::getInstance()) {
	SDL_Texture *texture = IMG_LoadTexture(gfx->getRenderer(), path.c_str());
	if (texture == nullptr) {
		image_logger->error("Error loading texture at: {} ()", path, SDL_GetError());
	}
	return texture;
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