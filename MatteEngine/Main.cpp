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


Graphics *Graphics::singleton = 0;
auto main_logger = spdlog::stdout_color_mt("Main.cpp");

void update(EntityManager* mgr, Graphics* window = Graphics::getInstance()) {
	SDL_Event e;

	bool quit = false;
	int ms_of_tick = 0;
	int time_per_tick = 1000 / (window->get_fps_cap());
	int ticks_remaining = 0;
	int ticks_per_sec = 0;
	int w, h;
	int window_w, window_h;
	int current_second = Timing::get_seconds_elapsed();
	double missedTicks = 0;
	SDL_GetWindowSize(window->fetch_window(), &window_w, &window_h);
	SDL_Texture* fps_texture = build_string_texture("FPS: %i" + ticks_per_sec, window->get_font(), w, h);
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
		apply_surface_to_screen(fps_texture, fps_location, window);
		window->update_window();

		// fps capping
		int s_elapsed = Timing::get_seconds_elapsed();
		if (s_elapsed != current_second) {
			main_logger->info("target tick time: {}", time_per_tick);
			main_logger->info("ms of tick: {}", ms_of_tick);
			main_logger->info("fps: {}", ticks_per_sec);
			main_logger->info("missed ticks: {}", missedTicks);
			fps_texture = build_string_texture(
				std::string("FPS: ").append(std::to_string(ticks_per_sec)).c_str(),
				window->get_font(),
				w,
				h
			);
			ticks_per_sec = 0;
			missedTicks = 0;
			current_second = s_elapsed;
		}

		++ticks_per_sec;

		ms_of_tick = Timing::get_tick_ms_elapsed();
		ticks_remaining = time_per_tick - ms_of_tick;
		if (ticks_remaining > 0) {
			missedTicks += (time_per_tick - ticks_remaining);
			//main_logger->info("holding for {} ticks", ticks_remaining);
			SDL_Delay(ticks_remaining);
			Timing::get_tick_ms_elapsed();
		}
	}
}

int main(int argc, char *argv[])
{
	initialize_sdl();

	Config* cfg = new Config();

	Graphics* our_window = Graphics::getInstance(cfg);
	SystemManager::load_systems();

	EntityManager* mgr = new EntityManager();
	Entity* test_sprite = ESprite::makeSprite("data/sprites/dwarf_1.png", 1);
	mgr->register_entity(test_sprite);

	// make sprite_map_component for our basic entity
	ESprite::register_sprite_map_dev(test_sprite);
	ESprite::register_animation_dev(test_sprite);
	ESprite::register_motion_dev(test_sprite);

	// make our test map and tileset
	Tileset* test_tiles = new Tileset("blue");
	TilesetManager* ts_mgr = new TilesetManager();
	ts_mgr->register_new_tileset(test_tiles);

	Map* test_map = new Map("test_map.mmp");
	test_map->register_map_tiles(mgr);

	//SMusic::load_music("test_music.mp3");
	update(mgr, our_window);

	our_window->shutdown();
	SDL_Delay(2000);

	return 0;
}

