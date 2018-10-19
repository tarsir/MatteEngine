#pragma once
#include <SDL.h>
#include <string>
#include "Graphics.h"
#include "Image.h"
#include "ComponentList.h"
#include "FacingConstants.h"
#include "BaseComponent.h"


class FacingComponent : public Component {
	ComponentTypes c_type = FACING;
	FacingDirection direction;
public:
	/*
		Constructor that takes a filename for a texture and a layer number.

		This will apply transparency with the default color of {64, 64, 64}, but
		any other processing is left to the caller.
	*/
	FacingComponent(FacingDirection _dir) : direction { _dir } {}

	void setDirection(FacingDirection dir) {
		this->direction = dir;
	}

	void rotateClockwise() {
		switch (this->direction) {
		case NORTH:
			this->direction = EAST;
			break;
		case EAST:
			this->direction = SOUTH;
			break;
		case SOUTH:
			this->direction = WEST;
			break;
		case WEST:
			this->direction = NORTH;
			break;
		}
	}

	void rotateCounterClockwise() {
		switch (this->direction) {
		case NORTH:
			this->direction = WEST;
			break;
		case EAST:
			this->direction = NORTH;
			break;
		case SOUTH:
			this->direction = EAST;
			break;
		case WEST:
			this->direction = SOUTH;
			break;
		}
	}

	ComponentTypes component_type() {
		return this->c_type;
	}
};
