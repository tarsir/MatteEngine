#pragma once

#include <SDL.h>
#include <string>
#include "Graphics.h"
#include "Color.h"

bool image_init();

SDL_Surface* load_image_as_surface(std::string path);
SDL_Texture* load_image_as_texture(std::string path, Graphics*);
void fill_surface(SDL_Surface* target_sfc);
void add_transparency_to_surface(SDL_Surface* target_surface, Color& transparency_key);
void set_pixel_format(SDL_PixelFormat* new_format);