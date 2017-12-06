#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

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
