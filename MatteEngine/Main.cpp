#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "spdlog\spdlog.h"
#include "Image.h"
#include "Window.h"
#include "Logging.h"

void die() {
	SDL_Delay(5000);
	exit(1);
}

void shutdown(SDL_Window* window) {
	SDL_DestroyWindow(window);
	//SDL_Quit();
}

int main(int argc, char * argv[])
{
	auto main_logger = spdlog::stdout_color_mt("Main.cpp");
	SDL_Event e;
	bool quit = false;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		main_logger->error("SDL initialization failed with error: {}", SDL_GetError());
		die();
	}
	else
	{
		main_logger->info("SDL initialization succeeded!");
	}

	if (!image_init()) {
		main_logger->error("SDL_image initialization failed with error: {}", IMG_GetError());
		die();
	}

	SDL_Window* window = initializeWindow();

	if (window == NULL) {
		sdl_error("Could not create window: %s\n");
		die();
	}

	SDL_Surface* screen = SDL_GetWindowSurface(window);

	set_pixel_format(screen->format);
	SDL_Surface* die = load_image("die.png");

	//transparency 
	Uint32 transparency_key = SDL_MapRGB(die->format, 64, 64, 64);
	SDL_SetColorKey(die, SDL_TRUE, transparency_key);
	SDL_BlitSurface(die, NULL, screen, NULL);
	SDL_UpdateWindowSurface(window);

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	shutdown(window);

	return 0;
}
