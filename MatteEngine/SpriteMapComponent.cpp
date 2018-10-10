#include "ComponentList.h"
#include "SpriteMapComponent.h"

auto sprite_map_c_logger = spdlog::stdout_color_mt("SpriteMapComponent.h");

SDL_Rect SpriteMapComponent::get_clipping_rect_for_animation(std::string animation_descriptor) {
	SDL_Rect dest_rect;
	std::map<std::string, std::pair<int, int> >::iterator it;
	it = this->sheet_mapping.find(animation_descriptor);
	if (it == this->sheet_mapping.end()) {
		sprite_map_c_logger->error("Tried to load animation: {}, but failed", animation_descriptor);
		return dest_rect; // TODO: change this when function gets used
	}

	std::pair<int, int> coords = it->second; 
	dest_rect.h = this->sprite_height;
	dest_rect.w = this->sprite_width;
	dest_rect.x = coords.first * this->sprite_width;
	dest_rect.y = coords.second * this->sprite_height;

	return dest_rect;
}