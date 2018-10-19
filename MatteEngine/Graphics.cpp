#include <SDL.h>
#include <SDL_ttf.h>
#include "spdlog\spdlog.h"
#include "Util.h"
#include "Image.h"
#include "Graphics.h"
#include "Logging.h"
#include "PositionComponent.h"


auto graphics_logger = spdlog::stdout_color_mt("Graphics.cpp");

Graphics* Graphics::getInstance() { 
	if (!Graphics::singleton) {
		Graphics::singleton = new Graphics();
	}
	return Graphics::singleton; 
}

Graphics* Graphics::getInstance(Config* cfg) { 
	if (!Graphics::singleton) {
		Graphics::singleton = new Graphics(cfg);
	}
	return Graphics::singleton; 
}

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
	this->width = width;
	this->height = height;

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

	this->writing_font = TTF_OpenFont("DroidSans.ttf", 18);

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
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

SDL_Texture* build_string_texture(const char* message, TTF_Font* font, int &width, int &height) {
	SDL_Color font_color = { 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, message, font_color);
	if (TTF_SizeText(font, message, &width, &height)) {
		graphics_logger->error("Error getting message dimensions: {}", TTF_GetError());
	}
	return convert_surface_to_texture(surface, Graphics::getInstance());
}

int Graphics::getHeight() { return this->height;  }
int Graphics::getWidth() { return this->width;  }
SDL_Renderer* Graphics::getRenderer() { return this->renderer;  }

void Graphics::fill_screen() {
	SDL_RenderClear(this->renderer);
}

void Graphics::update_window() {
	//SDL_UpdateWindowSurface(this->window);
	SDL_RenderPresent(this->renderer);
}

void Graphics::shutdown() {
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void apply_surface_to_screen(SDL_Surface* surface, SDL_Rect position, Graphics* window = Graphics::getInstance()) {
	if (SDL_BlitSurface(surface, NULL, window->fetch_screen(), &position) == 0) {
		return;
	}
	else {
		graphics_logger->error("Failed applying surface to default screen: {}", SDL_GetError());
	}
}

void apply_surface_to_screen(SDL_Texture* surface, SDL_Rect position, Graphics* gfx = Graphics::getInstance()) {
	if (SDL_RenderCopy(gfx->getRenderer(), surface, NULL, &position) == 0) {
		return;
	}
	else {
		graphics_logger->error("Failed applying surface to default screen: {}", SDL_GetError());
	}
}

void apply_surface_to_screen(SDL_Surface* new_surface, PositionComponent* position, Graphics* gfx = Graphics::getInstance()) {
	SDL_Rect destination;

	destination.x = position->x;
	destination.y = position->y;

	apply_surface_to_screen(new_surface, destination, gfx);
}

void apply_surface_to_screen(SDL_Texture* texture, PositionComponent* pos, Graphics* gfx = Graphics::getInstance() ) {
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_Rect destination = { pos->x, pos->y, w, h };

	if (SDL_RenderCopy(gfx->getRenderer(), texture, NULL, &destination) != 0) {
		graphics_logger->error("Error occurred rendering texture to screen: {}", SDL_GetError());
	}
}

SDL_Texture* convert_surface_to_texture(SDL_Surface* sfc, Graphics* gfx = Graphics::getInstance()) {
	SDL_Texture* new_texture = SDL_CreateTextureFromSurface(gfx->getRenderer(), sfc);
	if (new_texture == NULL) {
		graphics_logger->error("Failed converting SDL_Surface to SDL_Texture: {}", SDL_GetError());
		return NULL;
	}

	SDL_FreeSurface(sfc);
	return new_texture;
}

void apply_partial_texture_to_screen(
	SDL_Texture* full_texture,
	const SDL_Rect bounding_rectangle,
	PositionComponent* pos,
	Graphics* gfx = Graphics::getInstance()
) {
	SDL_Rect destination = { pos->x, pos->y, bounding_rectangle.w, bounding_rectangle.h};
	SDL_SetTextureBlendMode(full_texture, SDL_BLENDMODE_BLEND);

	SDL_RenderCopy(gfx->getRenderer(), full_texture, &bounding_rectangle, &destination);
}