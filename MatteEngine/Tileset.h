#pragma once

#include <string>
#include <map>

class Tileset {
	std::map<char, Sprite> tileMapping;
	std::string identifier;
};