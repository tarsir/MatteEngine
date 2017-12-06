#include <SDL.h>
#include <stdio.h>

void error(const char* errorMsg, const char* reason) {
	printf(errorMsg, reason);
}

void sdl_error(const char* errorMsg) {
	printf(errorMsg, SDL_GetError());
	SDL_Log(errorMsg, SDL_GetError());
}
