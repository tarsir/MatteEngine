#include <SDL.h>
#include <string>
#include <map>
#include "Graphics.h"
#include "Image.h"
#include "Entity.h"
#include "EnvironmentTile.h"
#include "spdlog\spdlog.h"

// Tileset

const static char EMPTY_TILE = 'N';
auto tileset_logger = spdlog::stdout_color_mt("Tileset.cpp");

Tileset::Tileset(std::string ident, Graphics* gfx) : identifier{ ident } {
	this->tile_mapping.emplace(EMPTY_TILE, load_image_as_texture(this->find_tile_filename("empty"), gfx));
}

SDL_Texture* Tileset::get_surface_for_tile_key(const char tile_key) {
	this->tile_mapping_it = this->tile_mapping.find(tile_key);
	if (this->tile_mapping_it != this->tile_mapping.end())
		return this->tile_mapping.at(tile_key);
	tileset_logger->error("could not find tile for: {} in tileset {}", tile_key, this->identifier);
	return this->tile_mapping.at(EMPTY_TILE);
}

std::string Tileset::get_identifier() {
	return this->identifier;
}

// TilesetManager

void TilesetManager::register_new_tileset(Tileset* new_tileset) {
	this->registered_tilesets.emplace(new_tileset->get_identifier(), new_tileset);
}

Tileset* TilesetManager::get_tileset_by_identifier(std::string identifier) {
	return this->registered_tilesets.at(identifier);
}

