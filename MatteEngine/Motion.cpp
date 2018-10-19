#include <SDL.h>
#include "Entity.h"
#include "Motion.h"
#include "FacingConstants.h"
#include "spdlog\spdlog.h"

#include "MovementComponent.h"
#include "ComponentList.h"
#include "FacingComponent.h"
#include "PositionComponent.h"

auto motion_logger = spdlog::stdout_color_mt("Motion.h");


namespace SMotion {
	void move_entity(uint32_t entity_id, EntityManager* entity_mgr, FacingDirection dir) {
		Entity* target_entity = entity_mgr->get_entity_by_id(entity_id);
		if (target_entity == nullptr) {
			motion_logger->error("Failed moving entity with ID {}", entity_id);
			return;
		}

		PositionComponent *position = dynamic_cast<PositionComponent*>(target_entity->get_component(POSITION));
		if (position == nullptr) {
			motion_logger->error("Failed moving entity with ID {}", entity_id);
			return;
		}

		FacingComponent *facing = dynamic_cast<FacingComponent*>(target_entity->get_component(FACING));
		MovementComponent *movement = dynamic_cast<MovementComponent*>(target_entity->get_component(MOVEMENT));
		if (facing == nullptr || movement == nullptr) {
			motion_logger->error("Failed moving entity with ID {}", entity_id);
			return;
		}

		facing->setDirection(dir);

		if (CFacing::is_opposite_directions(facing->getDirection(), dir)) {
			movement->stop();
		}
		else {
			switch (dir) {
			case NORTH:
				position->y -= movement->get_current_speed();
				break;
			case SOUTH:
				position->y += movement->get_current_speed();
				break;
			case WEST:
				position->x -= movement->get_current_speed();
				break;
			case EAST:
				position->x += movement->get_current_speed();
				break;
			}
		}
	}

	void update(EntityManager *e_mgr, const SDL_Event& e) {
		switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_UP:
			case SDLK_w:
				SMotion::move_entity(0, e_mgr, FacingDirection::NORTH);
				break;
			case SDLK_DOWN:
			case SDLK_s:
				SMotion::move_entity(0, e_mgr, FacingDirection::SOUTH);
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				SMotion::move_entity(0, e_mgr, FacingDirection::EAST);
				break;
			case SDLK_LEFT:
			case SDLK_a:
				SMotion::move_entity(0, e_mgr, FacingDirection::WEST);
				break;
			}
			break;
		}
	}
}