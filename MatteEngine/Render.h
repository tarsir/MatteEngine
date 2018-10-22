#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Graphics.h"

namespace SRender {
	void draw_single_entity(const Entity* entity, Graphics* gfx = Graphics::getInstance());
	void draw_entity_from_anim_description(const Entity* entity, Graphics* gfx = Graphics::getInstance());
	void update(EntityManager* entity_mgr, Graphics* gfx = Graphics::getInstance());
} 

