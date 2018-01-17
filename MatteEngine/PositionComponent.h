#pragma once
#include <string>
#include "ComponentList.h"
#include "BaseComponent.h"

class PositionComponent : public Component {
	static const ComponentTypes c_type = POSITION;

public:
	int x;
	int y;
	PositionComponent(int _x, int _y) : x{ _x }, y{ _y } {}

	// why are these increment functions here? :thinking:
	int increment_x() {
		return this->x++;
	}

	int increment_y() {
		return this->y++;
	}

	ComponentTypes component_type() {
		return this->c_type;
	}

	void add_positions(PositionComponent* other_pos) {
		this->x += other_pos->x;
		this->y += other_pos->y;
	}
};