#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "Entity.h"

namespace SMusic {
	void load_music(std::string filename);

	void update(EntityManager* e_mgr, const SDL_Event& e);
}