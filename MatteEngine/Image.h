#pragma once

#include <SDL.h>
#include <string>

bool image_init();

SDL_Surface* load_image(std::string path);
void set_pixel_format(SDL_PixelFormat* new_format);