#pragma once

#include <SDL.h>
#include "PositionComponent.h"


struct Graphics {
private:
	SDL_Window* window;
	SDL_Surface* main_screen;
	int fps_cap;
public:
	Graphics();
	Graphics(int width, int height, int pos_x, int pos_y);
	SDL_Window* fetch_window() const;
	SDL_Surface* fetch_screen() const;
	void fill_screen();
	void update_window();
	void shutdown();

	enum WindowPosition {
		undefined = SDL_WINDOWPOS_UNDEFINED,
		centered = SDL_WINDOWPOS_CENTERED
		// Other
	};
};


void apply_surface_to_screen(SDL_Surface* sfc, Graphics* our_window, PositionComponent*);