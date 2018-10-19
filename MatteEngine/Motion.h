#pragma once
#include <SDL.h>
#include "Entity.h"
#include "FacingConstants.h"

namespace SMotion {
	void move_entity(uint32_t entity_id, EntityManager* entity_mgr, FacingDirection dir);
	void update(EntityManager *e_mgr, const SDL_Event& e);
}