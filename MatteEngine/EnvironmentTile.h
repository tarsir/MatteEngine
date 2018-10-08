#pragma once
#include <SDL.h>
#include <sstream>
#include <string>
#include "DrawableComponent.h"
#include "PositionComponent.h"
#include "Entity.h"
#include "Tileset.h"
#include "spdlog\spdlog.h"

auto tile_logger = spdlog::stdout_color_mt("EnvironmentTile.h");

namespace EEnvironmentTile {
	int default_tile_size = 32;

	Entity* makeTile(SDL_Texture* tile_sfc, int x, int y, int layer = 5) {
		Entity* base = new Entity();

		DrawableComponent* drawable = new DrawableComponent(tile_sfc, layer);
		PositionComponent* pos = new PositionComponent(x * default_tile_size, y * default_tile_size);
		base->register_component(drawable);
		base->register_component(pos);
		return base;
	}

	Entity* makeCollidableTile(SDL_Surface* tile_sfc, int x, int y, int layer = 5);
}
