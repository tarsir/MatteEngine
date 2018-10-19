#pragma once
#include "ComponentList.h"
#include "BaseComponent.h"


class MovementComponent : public Component {
	ComponentTypes c_type = MOVEMENT;
	int max_speed, current_speed;
public:
	MovementComponent();
	MovementComponent(int _max);
	MovementComponent(int _max, int _current);

	void stop();
	void set_to_max_speed();
	void add_to_speed(int additive);
	int get_current_speed();

	ComponentTypes component_type() {
		return this->c_type;
	}
};
