#include <SDL.h>
#include <string>
#include "Graphics.h"
#include "Image.h"
#include "ComponentList.h"
#include "BaseComponent.h"
#include "DrawableComponent.h"

uint32_t DrawableComponent::get_layer() const {
	return this->layer;
}

SDL_Texture* DrawableComponent::get_texture() const {
	return this->texture;
}

ComponentTypes DrawableComponent::component_type() {
	return this->c_type;
}
