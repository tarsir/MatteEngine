#pragma once

#include <SDL.h>
#include <string>
#include "Graphics.h"
#include "Color.h"

bool image_init();

SDL_Texture* load_image_as_texture(std::string path, Graphics*);
void set_pixel_format(SDL_PixelFormat* new_format);