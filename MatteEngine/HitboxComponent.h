#pragma once
#include "BaseComponent.h"
#include "Entity.h"
#include "ComponentList.h"

class HitboxComponent : public Component {
	ComponentTypes c_type = HITBOX;
	int w, h;
public:
	HitboxComponent(int _w, int _h) : w { _w }, h{ _h } {};

	HitboxComponent() {}
	void init_by_drawable_component(Entity* target_entity);

	ComponentTypes component_type() {
		return this->c_type;
	}
};