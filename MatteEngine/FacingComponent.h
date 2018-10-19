#pragma once
#include "ComponentList.h"
#include "FacingConstants.h"
#include "BaseComponent.h"


class FacingComponent : public Component {
	ComponentTypes c_type = FACING;
	FacingDirection direction;
public:
	FacingComponent(FacingDirection _dir) : direction { _dir } {}

	FacingComponent() {
		this->direction = FacingDirection::NORTH;
	}

	FacingDirection getDirection() {
		return this->direction;
	}

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
