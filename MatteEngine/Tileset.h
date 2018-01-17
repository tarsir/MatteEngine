#pragma once

#include <SDL.h>
#include <string>
#include <map>
#include "Image.h"
#include "Entity.h"
#include "EnvironmentTile.h"

const static char EMPTY_TILE = 'N';


class Tileset {
private:
	std::map<char, SDL_Surface*> tile_mapping; // the entities must have a DrawableComponent
	std::string identifier;

	std::string find_tile_filename(std::string tile_name) {
		std::ostringstream tile_file_deduced;
		tile_file_deduced << "data/tilesets/" << this->identifier << "/" << tile_name << ".png";
		return tile_file_deduced.str();
	}

public:
	Tileset(std::string ident) : identifier{ ident } {
		this->tile_mapping.emplace(EMPTY_TILE, load_image(this->find_tile_filename("empty")));
	}

	Tileset() : Tileset("default") {}

	SDL_Surface* get_surface_for_tile_key(const char tile_key) {
		return this->tile_mapping.at(tile_key);
	}

	std::string get_identifier() {
		return this->identifier;
	}
};

class TilesetManager {
private:
	std::map<std::string, Tileset*> registered_tilesets;
public:
	void register_new_tileset(Tileset* new_tileset) {
		this->registered_tilesets.emplace(new_tileset->get_identifier(), new_tileset);
	}

	Tileset* get_tileset_by_identifier(std::string identifier) {
		return this->registered_tilesets.at(identifier);
	}

};