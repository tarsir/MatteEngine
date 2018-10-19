#include "MovementComponent.h"

MovementComponent::MovementComponent() {
	this->max_speed = 25;
	this->current_speed = 10;
}

MovementComponent::MovementComponent(int _max) {
	this->max_speed = _max;
	this->current_speed = 0;
}

MovementComponent::MovementComponent(int _max, int _current) {
	this->max_speed = _max;
	this->current_speed = _current;
}

int MovementComponent::get_current_speed() {
	return this->current_speed;
}

void MovementComponent::stop() {
	this->current_speed = 0;
}

void MovementComponent::set_to_max_speed() {
	this->current_speed = this->max_speed;
}

void MovementComponent::add_to_speed(int additive) {
	this->current_speed += additive;
	if (this->current_speed > this->max_speed) {
		this->current_speed = this->max_speed;
	}

	if (this->current_speed < 0) {
		this->current_speed = 0;
	}
}
