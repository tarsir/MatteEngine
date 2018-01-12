#pragma once

#include <SDL.h>
#include <string>
#include "Color.h"

bool image_init();

SDL_Surface* load_image(std::string path);
void fill_surface(SDL_Surface* target_sfc);
void add_transparency_to_surface(SDL_Surface* target_surface, Color& transparency_key);
void set_pixel_format(SDL_PixelFormat* new_format);