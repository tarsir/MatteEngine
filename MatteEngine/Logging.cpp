#include "spdlog\spdlog.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

namespace spd = spdlog;


// Gets or creates a console logger with name `logger_name`
auto retrieve_console_logger(std::string logger_name) {
	auto logger = spd::get(logger_name);
	if (!logger) {
		return spd::stdout_color_mt(logger_name);
	}
	return logger;
}

void info(const char* infoMsg) {
	printf(infoMsg);
}

void error(const char* errorMsg, const char* reason) {
	printf(errorMsg, reason);
}

void sdl_error(const char* errorMsg) {
	printf(errorMsg, SDL_GetError());
	SDL_Log(errorMsg, SDL_GetError());
}

void sdl_image_error(const char* errorMsg) {
	printf(errorMsg, IMG_GetError());
	SDL_Log(errorMsg, IMG_GetError());
}
