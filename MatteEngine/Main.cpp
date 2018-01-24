#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "SystemManager.h"
#include "spdlog\spdlog.h"
#include "Initialization.h"
#include "Util.h"
#include "Image.h"
#include "Color.h"
#include "Config.h"
#include "Graphics.h"
#include "Logging.h"
#include "Sprite.h"
#include "Render.h"
#include "Map.h"
#include "Tileset.h"
#include "Timing.h"

auto main_logger = spdlog::stdout_color_mt("Main.cpp");

void update(Graphics* window, EntityManager* mgr) {
	SDL_Event e;

	bool quit = false;
	int ms_of_tick = 0;
	int time_per_tick = 1000 / (window->get_fps_cap());
	int ticks_remaining = 0;
	int ticks_per_sec = 0;
	int w, h;
	int window_w, window_h;
	int current_second = Timing::get_seconds_elapsed();
	SDL_GetWindowSize(window->fetch_window(), &window_w, &window_h);
	SDL_Surface* fps_texture = build_string_texture("FPS: " + ticks_per_sec, window->get_font(), w, h);
	SDL_Rect fps_location;
	fps_location.x = window_w - (w + 50);
	fps_location.y = (h + 30);

	main_logger->info("target tick time: {}", time_per_tick);

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			SystemManager::update_with_event(mgr, e);
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		// system updates go here
		window->fill_screen();
		SRender::update(mgr, window);
		apply_surface_to_screen(fps_texture, window, fps_location);
		window->update_window();

		// fps capping
		if (Timing::get_seconds_elapsed() != current_second) {
			main_logger->info("fps: {}", ticks_per_sec);
			fps_texture = build_string_texture(std::string("FPS: ").append(std::to_string(ticks_per_sec)).c_str(), window->get_font(), w, h);
			ticks_per_sec = 0;
			current_second = Timing::get_seconds_elapsed();
		}

		++ticks_per_sec;

		ms_of_tick = Timing::get_tick_ms_elapsed();
		ticks_remaining = time_per_tick - ms_of_tick;
		if (ticks_remaining > 0) {
			//main_logger->info("holding for {} ticks", ticks_remaining);
			SDL_Delay(ticks_remaining);
		}
	}
}

int main(int argc, char *argv[])
{
	initialize_sdl();

	Config* cfg = new Config();

	Graphics* our_window = new Graphics(cfg);
	SystemManager::load_systems();

	EntityManager* mgr = new EntityManager();
	Entity* die_sprite = ESprite::makeSprite("die.png", 1);
	mgr->register_entity(die_sprite);

	// make our test map and tileset
	Tileset* test_tiles = new Tileset("blue");
	TilesetManager* ts_mgr = new TilesetManager();
	ts_mgr->register_new_tileset(test_tiles);

	Map* test_map = new Map("test_map.mmp");
	test_map->register_map_tiles(mgr);

	//SMusic::load_music("test_music.mp3");
	update(our_window, mgr);

	our_window->shutdown();
	SDL_Delay(2000);

	return 0;
}

