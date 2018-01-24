#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Config.h"
#include "PositionComponent.h"


struct Graphics {
private:
	SDL_Window* window;
	SDL_Surface* main_screen;
	TTF_Font* writing_font;
	SDL_Surface* debug_draw_string;
	int fps_cap;
public:
	Graphics();
	Graphics(Config* cfg);
	Graphics(int width, int height, int pos_x, int pos_y);
	SDL_Window* fetch_window() const;
	SDL_Surface* fetch_screen() const;
	void fill_screen();
	void update_window();
	void shutdown();
	int get_fps_cap();
	TTF_Font* get_font();

	enum WindowPosition {
		undefined = SDL_WINDOWPOS_UNDEFINED,
		centered = SDL_WINDOWPOS_CENTERED
		// Other
	};
};

SDL_Surface* build_string_texture(const char* message, TTF_Font* font, int& width, int& height);
void apply_surface_to_screen(SDL_Surface* sfc, Graphics* our_window, SDL_Rect);
void apply_surface_to_screen(SDL_Surface* sfc, Graphics* our_window, PositionComponent*);