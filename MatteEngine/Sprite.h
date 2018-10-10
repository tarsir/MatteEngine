#pragma once
#include <SDL.h>
#include <string>
#include "DrawableComponent.h"
#include "PositionComponent.h"
#include "SpriteMapComponent.h"
#include "Entity.h"
#include "ComponentList.h"
#include "spdlog\spdlog.h"

auto sprite_logger = spdlog::stdout_color_mt("Sprite.h");

namespace ESprite {
	Entity* makeSprite(std::string sprite_filename, uint32_t layer = 10) {
		Entity* base = new Entity();
		DrawableComponent* drawable = new DrawableComponent(sprite_filename, layer);
		PositionComponent* position = new PositionComponent(50, 50);
		base->register_component(drawable);
		base->register_component(position);
		sprite_logger->info("made a sprite from file: {}", sprite_filename);
		return base;
	}

	void register_sprite_map_dev(Entity* target_entity) {
		std::map<std::string, std::pair< int, int > > sheet_description = {
			{"south_walk_left", {0, 0}},
			{"south_walk_neutral", {0, 1}},
			{"south_walk_right", {0, 2}},
			{"west_walk_left", {1, 0}},
			{"west_walk_left", {1, 1}},
			{"west_walk_left", {1, 2}},
			{"east_walk_left", {2, 0}},
			{"east_walk_left", {2, 1}},
			{"east_walk_left", {2, 2}},
			{"north_walk_left", {3, 0}},
			{"north_walk_left", {3, 1}},
			{"north_walk_left", {3, 2}},
		};
		SpriteMapComponent* sprite_map_c = new SpriteMapComponent(32, 32, sheet_description);
		target_entity->register_component(sprite_map_c);
	}
}