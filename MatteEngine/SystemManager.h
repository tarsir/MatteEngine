#pragma once
#include <SDL.h>
#include <list>
#include "Entity.h"

namespace SystemManager {
	typedef void(*event_based_update)(EntityManager* e_mgr, const SDL_Event &e);
	std::list<event_based_update> event_updates;

	void update_with_event(EntityManager* e_mgr, const SDL_Event &e);
	void load_systems();
}