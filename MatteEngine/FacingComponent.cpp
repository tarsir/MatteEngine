#pragma once
#include "ComponentList.h"
#include "FacingConstants.h"
#include "BaseComponent.h"
#include "FacingComponent.h"


FacingComponent::FacingComponent() {
	this->direction = FacingDirection::NORTH;
}

FacingDirection FacingComponent::getDirection() {
	return this->direction;
}

void FacingComponent::setDirection(FacingDirection dir) {
	this->direction = dir;
}

void FacingComponent::rotateClockwise() {
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

void FacingComponent::rotateCounterClockwise() {
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

ComponentTypes FacingComponent::component_type() {
	return this->c_type;
}
