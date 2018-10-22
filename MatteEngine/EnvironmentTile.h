#pragma once
#include <SDL.h>
#include <sstream>
#include <string>
#include "DrawableComponent.h"
#include "PositionComponent.h"
#include "Entity.h"
#include "Tileset.h"

namespace EEnvironmentTile {
	int default_tile_size = 32;

	Entity* makeTile(SDL_Texture* tile_sfc, int x, int y, int layer = 5);

	Entity* makeCollidableTile(SDL_Texture* tile_sfc, int x, int y, int layer = 5);
}
