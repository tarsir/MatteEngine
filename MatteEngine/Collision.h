#pragma once
#include "Entity.h"

namespace SCollision {
	void entity_is_colliding(Entity* target_entity, EntityManager* mgr, int* c_height, int* c_length);
}