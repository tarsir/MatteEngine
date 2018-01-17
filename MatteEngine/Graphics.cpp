#include <SDL.h>
#include "spdlog\spdlog.h"
#include "Util.h"
#include "Image.h"
#include "Graphics.h"
#include "Logging.h"
#include "PositionComponent.h"


auto graphics_logger = spdlog::stdout_color_mt("Graphics.cpp");

Graphics::Graphics() : Graphics(1440, 900, Graphics::WindowPosition::centered, Graphics::WindowPosition::centered) {}

Graphics::Graphics(int width, int height, int pos_x, int pos_y) {
	this->window = SDL_CreateWindow(
		"Demo",
		pos_x,
		pos_y,
		width,
		height,
		SDL_WINDOW_OPENGL
	);

	if (this->window == NULL) {
		sdl_error("Could not create window: %s\n");
		die();
	}

	this->main_screen = SDL_GetWindowSurface(this->window);
	if (this->main_screen == nullptr) {
		sdl_error("Could not get screen from window: %s\n");
		die();
	}
	set_pixel_format(this->main_screen->format);
	this->fps_cap = 120;
}

SDL_Surface* Graphics::fetch_screen() const {
	return this->main_screen;
}

SDL_Window* Graphics::fetch_window() const {
	return this->window;
}

void Graphics::fill_screen() {
	fill_surface(this->main_screen);
}

void Graphics::update_window() {
	SDL_UpdateWindowSurface(this->window);
}

void Graphics::shutdown() {
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void apply_surface_to_screen(SDL_Surface* new_surface, Graphics* our_window, PositionComponent* position) {
	SDL_Rect destination;

	destination.x = position->x;
	destination.y = position->y;

	if (SDL_BlitSurface(new_surface, NULL, our_window->fetch_screen(), &destination) == 0) {
		return;
	}
	else {
		graphics_logger->error("Failed applying surface to default screen: {}", SDL_GetError());
	}
}