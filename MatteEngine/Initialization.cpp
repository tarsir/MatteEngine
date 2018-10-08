#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
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

	if (TTF_Init() == -1) {
		init_logger->error("SDL_TTF initialization failed with error: {}", TTF_GetError());
		die();
	}

	// Mixer init
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		init_logger->error("SDL_mixer initialization failed with error: {}", Mix_GetError());
		die();
	}


}