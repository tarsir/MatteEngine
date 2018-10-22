#pragma once
#include <SDL.h>
#include <list>
#include "Entity.h"

namespace SystemManager {
	void update_with_event(EntityManager* e_mgr, const SDL_Event &e);
	void load_systems();
}