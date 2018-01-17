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
#include "Graphics.h"
#include "Logging.h"
#include "Sprite.h"
#include "Render.h"
#include "Map.h"
#include "Tileset.h"

auto main_logger = spdlog::stdout_color_mt("Main.cpp");

void update(Graphics* window, EntityManager* mgr) {
	SDL_Event e;

	bool quit = false;
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
		window->update_window();
	}
}

int main(int argc, char *argv[])
{
	initialize_sdl();

	Graphics* our_window = new Graphics();
	SystemManager::load_systems();

	EntityManager* mgr = new EntityManager();
	Entity* die_sprite = ESprite::makeSprite("die.png", 1);
	mgr->register_entity(die_sprite);

	// make our test map and tileset
	Tileset* test_tiles = new Tileset("blue");
	TilesetManager* ts_mgr = new TilesetManager();
	ts_mgr->register_new_tileset(test_tiles);

	Map* test_map = new Map();
	test_map->identifier = "test";
	std::vector<char> test_row(100, 'N');
	std::vector< std::vector<char> > test_map_full(40, test_row);
	test_map->map_layout = test_map_full;
	test_map->map_tileset = test_tiles;
	test_map->register_map_tiles(mgr);

	Mix_Music* test_bgm = Mix_LoadMUS("test_music.mp3");
	if (!test_bgm) {
		main_logger->error("Couldn't load bgm with error: {}", Mix_GetError());
		die();
	}
	//Mix_PlayMusic(test_bgm, 0);

	update(our_window, mgr);

	our_window->shutdown();
	SDL_Delay(2000);

	return 0;
}

