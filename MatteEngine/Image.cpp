#include <SDL.h>
#include "stb_image.h"
#include "Image.h"
#include "Logging.h"

SurfaceContainer* loadImageFromFilename(const char* filename) {
	return loadImageFromFilename(filename, STBI_rgb_alpha);
}

SurfaceContainer* loadImageFromFilename(const char* filename, int requestedChannels) {
	int width, height, fileChannels;
	unsigned char* imageData = stbi_load(filename, &width, &height, &fileChannels, requestedChannels);
	if (imageData == NULL) {
		error("Loading image failed: %s", stbi_failure_reason());
		exit(1);
	}

	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	int shift = (requestedChannels == STBI_rgb) ? 8 : 0;
	rmask = 0xff000000 >> shift;
	gmask = 0x00ff0000 >> shift;
	bmask = 0x0000ff00 >> shift;
	amask = 0x000000ff >> shift;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = (requestedChannels == STBI_rgb) ? 0 : 0xff000000;
#endif

	int depth, pitch;
	if (requestedChannels == STBI_rgb) {
		depth = 24;
		pitch = 3 * width;
	}
	else {
		depth = 32;
		pitch = 4 * width;
	}

	SDL_Surface* sfc = SDL_CreateRGBSurfaceFrom((void*)imageData, width, height, depth, pitch, rmask, gmask, bmask, amask);
	if (sfc == NULL) {
		sdl_error("Creating surface failed: %s");
		stbi_image_free(imageData);
		exit(1);
	}

	SurfaceContainer* container = new SurfaceContainer();

	container->image_data = imageData;
	container->sdl_surface = sfc;

	return container;
}

void releaseSurface(SurfaceContainer* container) {
	SDL_FreeSurface(container->sdl_surface);
	stbi_image_free(container->image_data);
}
