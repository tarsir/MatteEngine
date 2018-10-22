#pragma once
#include "ComponentList.h"
#include "FacingConstants.h"
#include "BaseComponent.h"


class FacingComponent : public Component {
	ComponentTypes c_type = FACING;
	FacingDirection direction;
public:
	FacingComponent(FacingDirection _dir) : direction { _dir } {}

	FacingComponent();

	FacingDirection getDirection();

	void setDirection(FacingDirection dir);

	void rotateClockwise();

	void rotateCounterClockwise();

	ComponentTypes component_type();
};
