#include "EnvironmentTile.h"
#include "Map.h"
#include "spdlog\spdlog.h"

auto map_logger = spdlog::stdout_color_mt("Map.cpp");

Map::Map(const char* filename) {
	validate_file_extension(filename, "mmp");
	map_logger->info("reading map file: {}", filename);
	std::vector< std::string > map_file = read_file(filename);
	this->identifier = map_file[0];
	this->map_tileset = new Tileset(map_file[1]);
	map_file.erase(map_file.begin(), map_file.begin() + 2);
	this->map_layout = map_file;
}

int Map::register_map_tiles(EntityManager* mgr) {
	int added_tiles = 0;
	for (int i = 0; i < this->map_layout.size(); i++) {
		auto map_row = this->map_layout[i];
		for (int j = 0; j < map_row.size(); j++) {
			char tile = map_row[j];
			Entity* map_tile_entity = EEnvironmentTile::makeTile(this->map_tileset->get_surface_for_tile_key(tile), j, i);
			mgr->register_entity(map_tile_entity);
			added_tiles++;
		}
	}
	return added_tiles;
}
