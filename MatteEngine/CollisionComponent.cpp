#include "CollisionComponent.h"

CollisionComponent::CollisionComponent() {
	this->isEnabled = true;
}

void CollisionComponent::enableCollision() {
	this->isEnabled = true;
}

void CollisionComponent::disableCollision() {
	this->isEnabled = false;
}

ComponentTypes CollisionComponent::component_type() {
	return this->c_type;
}