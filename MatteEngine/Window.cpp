#include <SDL.h>
#include "Logging.h"

SDL_Window* initializeWindow() {
	SDL_Window* newWindow;
	
	newWindow = SDL_CreateWindow(
		"Demo",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);

	return newWindow;
}