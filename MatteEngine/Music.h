#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include "Entity.h"
#include "Util.h"
#include "spdlog\spdlog.h"

auto music_logger = spdlog::stdout_color_mt("Music.h");

namespace SMusic {
	int current_music_volume = 32;
	Mix_Music* current_bgm;

	void load_music(std::string filename) {
		Mix_FadeOutMusic(2000);

		current_bgm = Mix_LoadMUS(filename.c_str());

		if (!current_bgm) {
			music_logger->error("Couldn't load bgm with error: {}", Mix_GetError());
			die();
		}
		Mix_FadeInMusic(current_bgm, 0, 2000);
	}

	void update(EntityManager* e_mgr, const SDL_Event& e) {
		bool is_change = false;
		switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_KP_PLUS:
						++current_music_volume;
						Mix_VolumeMusic(current_music_volume);
						is_change = true;
						break;
					case SDLK_KP_MINUS:
						--current_music_volume;
						Mix_VolumeMusic(current_music_volume);
						is_change = true;
						break;
				}
				if (is_change) {
					music_logger->info("new music volume: {}", current_music_volume);
				}
		}
	}
}