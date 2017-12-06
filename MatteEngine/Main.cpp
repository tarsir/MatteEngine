#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Image.h"
#include "Window.h"
#include "spdlog\spdlog.h"
#include "Logging.h"

namespace spd = spdlog;

void die() {
	SDL_Delay(5000);
	exit(1);
}

void shutdown(SDL_Window* window) {
	SDL_Delay(1000);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char * argv[])
{
	auto console = spd::stdout_color_mt("console");
	console->info("hello");

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		console->error("SDL initialization failed with error: {}", SDL_GetError());
		die();
	}
	else
	{
		console->info("SDL initialization succeeded!");
	}

	if (!image_init()) {
		console->error("SDL_image initialization failed with error: {}", IMG_GetError());
		die();
	}

	SDL_Window* newWindow = initializeWindow();

	if (newWindow == NULL) {
		sdl_error("Could not create window: %s\n");
		die();
	}

	SDL_Surface* screen = SDL_GetWindowSurface(newWindow);

	shutdown(newWindow);

	return 0;
}
