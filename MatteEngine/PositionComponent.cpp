#include "PositionComponent.h"

int PositionComponent::increment_x() {
	return this->x++;
}

int PositionComponent::increment_y() {
	return this->y++;
}

ComponentTypes PositionComponent::component_type() {
	return this->c_type;
}

void PositionComponent::add_positions(PositionComponent* other_pos) {
	this->x += other_pos->x;
	this->y += other_pos->y;
}

void PositionComponent::move_in_direction(FacingDirection dir, int amount) {
	switch (dir) {
	case NORTH:
		this->y -= amount;
		break;
	case SOUTH:
		this->y += amount;
		break;
	case WEST:
		this->x -= amount;
		break;
	case EAST:
		this->x += amount;
		break;
	}
}
