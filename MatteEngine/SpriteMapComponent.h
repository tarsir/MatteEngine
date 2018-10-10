#pragma once

#include <string>
#include <utility>
#include <map>
#include <SDL.h>
#include "ComponentList.h"
#include "BaseComponent.h"
#include "spdlog\spdlog.h"


class SpriteMapComponent : public Component {
	static const ComponentTypes c_type = SPRITE_MAP;
	std::map<std::string, std::pair<int, int> > sheet_mapping;
	int sprite_width, sprite_height;

public:
	// TODO: add a constructor that takes a DrawableComponent and pulls the SDL_Texture from it
	SpriteMapComponent(int width, int height, std::map<std::string, std::pair< int, int> > _sheet_mapping) : 
		sprite_width{ width }, sprite_height{ height }, sheet_mapping{ _sheet_mapping }  {}

	SDL_Rect get_clipping_rect_for_animation(std::string animation_descriptor);
	ComponentTypes component_type() {
		return this->c_type;
	}
};