#include <cmath>
#include <algorithm>
#include "Collision.h"
#include "DrawableComponent.h"
#include "MovementComponent.h"
#include "PositionComponent.h"

struct DistanceComparison {
	bool operator()(const Entity* lhs, const Entity* rhs) const {
		PositionComponent *lhd = dynamic_cast<PositionComponent*>(lhs->get_component(POSITION)), 
			*rhd = dynamic_cast<PositionComponent*>(rhs->get_component(POSITION));
		return sqrt(pow((lhd->x - rhd->x), 2) + pow((lhd->y - rhd->y), 2)) > 100;
	}
} sorter;

namespace SCollision {
	void entity_is_colliding(Entity* target_entity, EntityManager *mgr, int* collision_height, int* collision_length) {
		DrawableComponent *d_comp = dynamic_cast<DrawableComponent*>(target_entity->get_component(DRAWABLE));
		MovementComponent *m_comp = dynamic_cast<MovementComponent*>(target_entity->get_component(MOVEMENT));
		// find out the range around which we want to check for collisions (size + movement speed?)


		std::vector<Entity*> collidable_entities = mgr->entities_matching_component(COLLISION);
		std::for_each(collidable_entities.begin(), collidable_entities.end(), sorter);
		// inside the lambda we want to first prune all the things outside this range and then determine if there is
		// a collision, and if so, how deep the collision is

	}
}