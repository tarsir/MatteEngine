#include "EnvironmentTile.h"
#include "spdlog\spdlog.h"

auto tile_logger = spdlog::stdout_color_mt("EnvironmentTile.cpp");

namespace EEnvironmentTile {
	int default_tile_size = 32;

	Entity* makeTile(SDL_Texture* tile_sfc, int x, int y, int layer) {
		Entity* base = new Entity();

		DrawableComponent* drawable = new DrawableComponent(tile_sfc, layer);
		PositionComponent* pos = new PositionComponent(x * default_tile_size, y * default_tile_size);
		base->register_component(drawable);
		base->register_component(pos);
		return base;
	}

	Entity* makeCollidableTile(SDL_Texture* tile_sfc, int x, int y, int layer) {
		Entity* base = makeTile(tile_sfc, x, y, layer);

		// TODO: need CollidableComponent
		return base;
	}
}