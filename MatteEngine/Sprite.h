#pragma once
#include <SDL.h>
#include <string>
#include "DrawableComponent.h"
#include "PositionComponent.h"
#include "Entity.h"
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
}