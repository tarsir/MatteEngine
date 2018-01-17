#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include "Entity.h"
#include "spdlog\spdlog.h"

auto music_logger = spdlog::stdout_color_mt("Music.h");

namespace SMusic {
	int current_music_volume = 32;

	void update(EntityManager* e_mgr, const SDL_Event& e) {
		switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_KP_PLUS:
						++current_music_volume;
						Mix_VolumeMusic(current_music_volume);
						break;
					case SDLK_KP_MINUS:
						--current_music_volume;
						Mix_VolumeMusic(current_music_volume);
						break;
				}
		}
		music_logger->info("new music volume: {}", current_music_volume);
	}
}