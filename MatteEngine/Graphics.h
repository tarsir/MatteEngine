#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Config.h"
#include "PositionComponent.h"


struct Graphics {
private:
	static Graphics* singleton;
	static bool is_initialized;
	SDL_Window* window;
	SDL_Surface* main_screen;
	TTF_Font* writing_font;
	SDL_Renderer* renderer;
	int fps_cap;
	int width, height;
	Graphics();
	Graphics(Config* cfg);
	Graphics(int width, int height, int pos_x, int pos_y);
public:
	static Graphics* getInstance();
	static Graphics* getInstance(Config*);
	SDL_Window* fetch_window() const;
	SDL_Surface* fetch_screen() const;
	void fill_screen();
	void update_window();
	void shutdown();
	int get_fps_cap();
	TTF_Font* get_font();
	int getWidth();
	int getHeight();
	SDL_Renderer* getRenderer();

	enum WindowPosition {
		undefined = SDL_WINDOWPOS_UNDEFINED,
		centered = SDL_WINDOWPOS_CENTERED
		// Other
	};
};

SDL_Texture* build_string_texture(const char* message, TTF_Font* font, int& width, int& height);
void apply_surface_to_screen(SDL_Texture* sfc, SDL_Rect, Graphics* our_window);
void apply_surface_to_screen(SDL_Texture* sfc,  PositionComponent*, Graphics* our_window);
void apply_partial_texture_to_screen(SDL_Texture*, const SDL_Rect, PositionComponent*, Graphics*);
SDL_Texture* convert_surface_to_texture(SDL_Surface* sfc, Graphics* gfx);
