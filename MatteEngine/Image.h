#pragma once

#include <SDL.h>

struct SurfaceContainer {
	SDL_Surface *sdl_surface;
	unsigned char *image_data;
};

SurfaceContainer* loadImageFromFilename(const char*);
SurfaceContainer* loadImageFromFilename(const char*, int requestedChannels);
void releaseSurface(SurfaceContainer* container);
