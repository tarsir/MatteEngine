#include <SDL.h>
#include <SDL_ttf.h>
#include "spdlog\spdlog.h"
#include "Util.h"
#include "Image.h"
#include "Graphics.h"
#include "Logging.h"
#include "PositionComponent.h"


auto graphics_logger = spdlog::stdout_color_mt("Graphics.cpp");

Graphics::Graphics(Config* cfg) : Graphics(cfg->get_value("width"), cfg->get_value("height"), Graphics::WindowPosition::centered, Graphics::WindowPosition::centered) {}

Graphics::Graphics() : Graphics(1440, 900, Graphics::WindowPosition::centered, Graphics::WindowPosition::centered) {}

Graphics::Graphics(int width, int height, int pos_x, int pos_y) {
	graphics_logger->info("Creating window with (w, h) = ({}, {})", width, height);
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
	this->fps_cap = 80;

	this->writing_font = TTF_OpenFont("DroidSans.ttf", 18);
}

SDL_Surface* Graphics::fetch_screen() const {
	return this->main_screen;
}

SDL_Window* Graphics::fetch_window() const {
	return this->window;
}

TTF_Font* Graphics::get_font() {
	return this->writing_font;
}

int Graphics::get_fps_cap() {
	return this->fps_cap;
}

SDL_Surface* build_string_texture(const char* message, TTF_Font* font, int &width, int &height) {
	SDL_Color font_color = { 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, message, font_color);
	if (TTF_SizeText(font, message, &width, &height)) {
		graphics_logger->error("Error getting message dimensions: {}", TTF_GetError());
	}
	return surface;
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

void apply_surface_to_screen(SDL_Surface* surface, Graphics* window, SDL_Rect position) {
	if (SDL_BlitSurface(surface, NULL, window->fetch_screen(), &position) == 0) {
		return;
	}
	else {
		graphics_logger->error("Failed applying surface to default screen: {}", SDL_GetError());
	}
}

void apply_surface_to_screen(SDL_Surface* new_surface, Graphics* our_window, PositionComponent* position) {
	SDL_Rect destination;

	destination.x = position->x;
	destination.y = position->y;

	apply_surface_to_screen(new_surface, our_window, destination);
}