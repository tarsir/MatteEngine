#include <SDL.h>
#include <SDL_image.h>
#include "Image.h"
#include "Logging.h"

bool image_init() {
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		return false;
	}

	return true;
}