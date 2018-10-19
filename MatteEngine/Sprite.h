#pragma once
#include <SDL.h>
#include <string>
#include "FacingConstants.h"

#include "AnimationComponent.h"
#include "DrawableComponent.h"
#include "FacingComponent.h"
#include "PositionComponent.h"
#include "SpriteMapComponent.h"
#include "Entity.h"
#include "ComponentList.h"
#include "spdlog\spdlog.h"

auto sprite_logger = spdlog::stdout_color_mt("Sprite.h");

namespace ESprite {
	Entity* makeSprite(std::string sprite_filename, uint32_t layer = 10) {
		Entity* base = new Entity();
		SDL_Texture* texture = IMG_LoadTexture(Graphics::getInstance()->getRenderer(), sprite_filename.c_str());
		DrawableComponent* drawable = new DrawableComponent(texture, layer);
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
			{"west_walk_neutral", {1, 1}},
			{"west_walk_right", {1, 2}},
			{"east_walk_left", {2, 0}},
			{"east_walk_neutral", {2, 1}},
			{"east_walk_right", {2, 2}},
			{"north_walk_left", {3, 0}},
			{"north_walk_neutral", {3, 1}},
			{"north_walk_right", {3, 2}},
		};
		SpriteMapComponent* sprite_map_c = new SpriteMapComponent(32, 32, sheet_description);
		target_entity->register_component(sprite_map_c);
	}

	void register_animation_dev(Entity* target_entity) {
		std::vector<AnimationInfo> anim_sequence;
		AnimationInfo s_left;
		s_left.description = "south_walk_left";
		s_left.is_neutral = false;
		s_left.duration = 20;
		s_left.sequence_number = 1;
		s_left.animation_direction = FacingDirection::SOUTH;

		AnimationInfo s_neutral;
		s_neutral.description = "south_walk_neutral";
		s_neutral.is_neutral = true;
		s_neutral.duration = 20;
		s_neutral.sequence_number = 0;
		s_neutral.animation_direction = FacingDirection::SOUTH;

		AnimationInfo s_right;
		s_right.description = "south_walk_right";
		s_right.is_neutral = false;
		s_right.duration = 20;
		s_right.sequence_number = 2;
		s_right.animation_direction = FacingDirection::SOUTH;

		AnimationInfo w_left;
		w_left.description = "west_walk_left";
		w_left.is_neutral = false;
		w_left.duration = 20;
		w_left.sequence_number = 1;
		w_left.animation_direction = FacingDirection::WEST;

		AnimationInfo w_neutral;
		w_neutral.description = "west_walk_neutral";
		w_neutral.is_neutral = true;
		w_neutral.duration = 20;
		w_neutral.sequence_number = 1;
		w_neutral.animation_direction = FacingDirection::WEST;

		AnimationInfo w_right;
		w_right.description = "west_walk_right";
		w_right.is_neutral = false;
		w_right.duration = 20;
		w_right.sequence_number = 1;
		w_right.animation_direction = FacingDirection::WEST;

		AnimationInfo e_left;
		e_left.description = "east_walk_left";
		e_left.is_neutral = false;
		e_left.duration = 20;
		e_left.sequence_number = 1;
		e_left.animation_direction = FacingDirection::EAST;

		AnimationInfo e_neutral;
		e_neutral.description = "east_walk_neutral";
		e_neutral.is_neutral = true;
		e_neutral.duration = 20;
		e_neutral.sequence_number = 1;
		e_neutral.animation_direction = FacingDirection::EAST;

		AnimationInfo e_right;
		e_right.description = "east_walk_right";
		e_right.is_neutral = false;
		e_right.duration = 20;
		e_right.sequence_number = 1;
		e_right.animation_direction = FacingDirection::EAST;

		AnimationInfo n_left;
		n_left.description = "north_walk_left";
		n_left.is_neutral = false;
		n_left.duration = 20;
		n_left.sequence_number = 1;
		n_left.animation_direction = FacingDirection::NORTH;

		AnimationInfo n_neutral;
		n_neutral.description = "north_walk_neutral";
		n_neutral.is_neutral = true;
		n_neutral.duration = 20;
		n_neutral.sequence_number = 1;
		n_neutral.animation_direction = FacingDirection::NORTH;

		AnimationInfo n_right;
		n_right.description = "north_walk_right";
		n_right.is_neutral = false;
		n_right.duration = 20;
		n_right.sequence_number = 1;
		n_right.animation_direction = FacingDirection::NORTH;

		anim_sequence.push_back(s_left);
		anim_sequence.push_back(s_neutral);
		anim_sequence.push_back(s_right);
		anim_sequence.push_back(w_left);
		anim_sequence.push_back(w_neutral);
		anim_sequence.push_back(w_right);
		anim_sequence.push_back(n_left);
		anim_sequence.push_back(n_neutral);
		anim_sequence.push_back(n_right);
		anim_sequence.push_back(e_left);
		anim_sequence.push_back(e_neutral);
		anim_sequence.push_back(e_right);
		AnimationComponent* animation_c = new AnimationComponent(anim_sequence);
		FacingComponent* facing_c = new FacingComponent();
		target_entity->register_component(animation_c);
		target_entity->register_component(facing_c);
	}
}