#pragma once

#include <SDL.h>
#include <string>
#include <map>
#include "Graphics.h"
#include "Image.h"
#include "Entity.h"
#include "EnvironmentTile.h"


class Tileset {
private:
	std::map<char, SDL_Texture*> tile_mapping; // the entities must have a DrawableComponent
	std::map<char, SDL_Texture*>::iterator tile_mapping_it;
	std::string identifier;

	std::string find_tile_filename(std::string tile_name) {
		std::ostringstream tile_file_deduced;
		tile_file_deduced << "data/tilesets/" << this->identifier << "/" << tile_name << ".png";
		return tile_file_deduced.str();
	}

public:
	Tileset(std::string ident, Graphics* gfx = Graphics::getInstance());
	//Tileset(std::string ident) : Tileset(ident, Graphics::getInstance()) {}

	Tileset(Graphics* gfx) : Tileset("default", gfx) {}

	SDL_Texture* get_surface_for_tile_key(const char tile_key);

	std::string get_identifier();
};

class TilesetManager {
private:
	std::map<std::string, Tileset*> registered_tilesets;
public:
	void register_new_tileset(Tileset* new_tileset);

	Tileset* get_tileset_by_identifier(std::string identifier);

};