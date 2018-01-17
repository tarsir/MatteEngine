#pragma once

#include <SDL.h>
#include <list>
#include "Graphics.h"
#include "Entity.h"
#include "Motion.h"
#include "Music.h"
#include "Render.h"

namespace SystemManager {
	typedef void(*event_based_update)(EntityManager* e_mgr, const SDL_Event &e);
	std::list<event_based_update> event_updates;

	void update_with_event(EntityManager* e_mgr, const SDL_Event &e) {
		for (auto &update_fn : event_updates) {
			update_fn(e_mgr, e);
		}
	}

	void load_systems() {
		event_updates.push_back(&SMotion::update);
		event_updates.push_back(&SMusic::update);
	}
}