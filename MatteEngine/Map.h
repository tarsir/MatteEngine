#pragma once
#include "Tileset.h"
#include "Entity.h"
#include "Util.h"
#include <vector>
#include <string>

class Map {
private:
	std::string identifier;
	Tileset* map_tileset;
	std::vector< std::string > map_layout;

public:
	Map(const char* filename);
	int register_map_tiles(EntityManager* mgr);
};