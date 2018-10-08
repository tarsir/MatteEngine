#pragma once

#include <SDL.h>
#include <string>
#include <map>
#include "Graphics.h"
#include "Image.h"
#include "Entity.h"
#include "EnvironmentTile.h"
#include "spdlog\spdlog.h"

const static char EMPTY_TILE = 'N';
auto tileset_logger = spdlog::stdout_color_mt("Tileset.h");


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
	Tileset(std::string ident, Graphics* gfx = Graphics::getInstance()) : identifier{ ident } {
		this->tile_mapping.emplace(EMPTY_TILE, load_image_as_texture(this->find_tile_filename("empty"), gfx));
	}

	//Tileset(std::string ident) : Tileset(ident, Graphics::getInstance()) {}

	Tileset(Graphics* gfx) : Tileset("default", gfx) {}

	SDL_Texture* get_surface_for_tile_key(const char tile_key) {
		this->tile_mapping_it = this->tile_mapping.find(tile_key);
		if (this->tile_mapping_it != this->tile_mapping.end()) 
			return this->tile_mapping.at(tile_key);
		tileset_logger->error("could not find tile for: {} in tileset {}", tile_key, this->identifier);
		return this->tile_mapping.at(EMPTY_TILE);
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