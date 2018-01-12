#include <SDL.h>
#include <SDL_image.h>
#include "Image.h"
#include "Util.h"
#include "spdlog\spdlog.h"
#include "Initialization.h"

auto init_logger = spdlog::stdout_color_mt("Initialization.cpp");

void initialize_sdl() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		init_logger->error("SDL initialization failed with error: {}", SDL_GetError());
		die();
	}
	else
	{
		init_logger->info("SDL initialization succeeded!");
	}

	if (!image_init()) {
		init_logger->error("SDL_image initialization failed with error: {}", IMG_GetError());
		die();
	}
}