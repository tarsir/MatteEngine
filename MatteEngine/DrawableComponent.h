#pragma once
#include <SDL.h>
#include <string>
#include "Graphics.h"
#include "Image.h"
#include "ComponentList.h"
#include "BaseComponent.h"

class DrawableComponent : public Component {
	ComponentTypes c_type = DRAWABLE;
	SDL_Texture* texture;
	uint32_t layer; // use 0 as the "base" eg. map tiles
public:
	/*
		Constructor that takes a filename for a texture and a layer number.

		This will apply transparency with the default color of {64, 64, 64}, but
		any other processing is left to the caller.
	*/
	DrawableComponent(std::string texture_location, uint32_t _layer, Graphics* gfx = Graphics::getInstance()) : layer{ _layer } {
		SDL_Surface* temp = load_image_as_surface(texture_location);

		Color transparent_gray = { 0, 0, 0};
		//add_transparency_to_surface(temp, transparent_gray);
		this->texture = SDL_CreateTextureFromSurface(gfx->getRenderer(), temp);
	}

	/*
		Constructor that takes a layer number and a fully processed SDL_Texture.

		This does NOT apply transparency or anything else to the texture. It is expected
		the caller of this constructor will have done anything like that.
	*/
	DrawableComponent(SDL_Surface* _texture, uint32_t _layer, Graphics* gfx = Graphics::getInstance()) : layer{ _layer } {
		this->texture = SDL_CreateTextureFromSurface(gfx->getRenderer(), _texture);
	}

	/*
		Constructor that takes a layer number and a fully processed SDL_Texture.

		This does NOT apply transparency or anything else to the texture. It is expected
		the caller of this constructor will have done anything like that.
	*/
	DrawableComponent(SDL_Texture* _texture, uint32_t _layer) : layer{ _layer } {
		this->texture = _texture;
	}

	uint32_t get_layer() const {
		return this->layer;
	}

	SDL_Texture* get_texture() const {
		return this->texture;
	}

	ComponentTypes component_type() {
		return this->c_type;
	}
};