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
