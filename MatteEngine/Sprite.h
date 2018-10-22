#pragma once
#include <SDL.h>
#include <string>
#include "FacingConstants.h"

#include "AnimationComponent.h"
#include "DrawableComponent.h"
#include "FacingComponent.h"
#include "MovementComponent.h"
#include "PositionComponent.h"
#include "SpriteMapComponent.h"
#include "Entity.h"
#include "ComponentList.h"

namespace ESprite {
	Entity* makeSprite(std::string sprite_filename, uint32_t layer);

	// development functions to make adding shit to our test sprite easier
	void register_motion_dev(Entity* target_entity);
	void register_sprite_map_dev(Entity* target_entity);
	void register_animation_dev(Entity* target_entity);
}