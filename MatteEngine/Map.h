#pragma once
#include "Tileset.h"
#include <vector>
#include <string>

class MapInfo {
	std::string identifier;
	Tileset* mapTileset;
	std::vector< std::vector<char> > mapLayout;
};