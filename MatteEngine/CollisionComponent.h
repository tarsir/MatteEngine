#pragma once

#include "BaseComponent.h"
#include "ComponentList.h"

class CollisionComponent : public Component {
	ComponentTypes c_type = COLLISION;
	bool isEnabled;
public:
	CollisionComponent();
	void enableCollision();
	void disableCollision();
	ComponentTypes component_type();
};