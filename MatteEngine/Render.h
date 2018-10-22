#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Graphics.h"

namespace SRender {
	void draw_single_entity(const Entity* entity, Graphics* gfx);
	void draw_entity_from_anim_description(const Entity* entity, Graphics* gfx);
	void update(EntityManager* entity_mgr, Graphics* gfx);
} 

