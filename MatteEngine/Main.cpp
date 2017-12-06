#include <iostream>
#include <SDL.h>
#include "Window.h"
#include "Logging.h"

int main(int argc, char * argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		std::cout << "SDL initialization succeeded!";
	}

	SDL_Window* newWindow = initializeWindow();

	if (newWindow == NULL) {
		sdl_error("Could not create window: %s\n");
		return NULL;
	}

	SDL_Surface* screen = SDL_GetWindowSurface(newWindow);

	SDL_Delay(1000);

	SDL_DestroyWindow(newWindow);

	SDL_Quit();

	return 0;
}