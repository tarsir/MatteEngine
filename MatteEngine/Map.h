#pragma once
#include "Tileset.h"
#include "EnvironmentTile.h"
#include "Entity.h"
#include <vector>
#include <string>

class Map {
public:
	std::string identifier;
	Tileset* map_tileset;
	std::vector< std::vector<char> > map_layout;

	int register_map_tiles(EntityManager* mgr) {
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
};