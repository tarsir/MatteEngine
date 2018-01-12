#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
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

	update(our_window, mgr);

	our_window->shutdown();
	SDL_Delay(2000);

	return 0;
}

