#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "Entity.h"

namespace SMusic {
	int current_music_volume = 32;
	Mix_Music* current_bgm;

	void load_music(std::string filename);

	void update(EntityManager* e_mgr, const SDL_Event& e);
}