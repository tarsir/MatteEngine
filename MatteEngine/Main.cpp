#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "spdlog\spdlog.h"
#include "Image.h"
#include "Color.h"
#include "Window.h"
#include "Logging.h"

void die() {
	SDL_Delay(5000);
	exit(1);
}

void shutdown(SDL_Window* window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char * argv[])
{
	auto main_logger = spdlog::stdout_color_mt("Main.cpp");

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

	Color transparent_gray = { 64, 64, 64 };
	add_transparency_to_surface(die, transparent_gray);

	SDL_BlitSurface(die, NULL, screen, NULL);
	SDL_UpdateWindowSurface(window);

	SDL_Event e;
	bool quit = false;

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
