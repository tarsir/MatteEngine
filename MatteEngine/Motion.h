#pragma once
#include <SDL.h>
#include "Entity.h"
#include "ComponentList.h"
#include "PositionComponent.h"
#include "spdlog\spdlog.h"

auto motion_logger = spdlog::stdout_color_mt("Motion.h");

namespace SMotion {
	void move_entity(uint32_t entity_id, EntityManager* entity_mgr, int x_del, int y_del) {
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
		position->x += x_del;
		position->y += y_del;
	}

	void update(EntityManager *e_mgr, const SDL_Event& e) {
		switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
					case SDLK_UP:
					case SDLK_w:
						SMotion::move_entity(0, e_mgr, 0, -25);
						break;
					case SDLK_DOWN:
					case SDLK_s:
						SMotion::move_entity(0, e_mgr, 0, 25);
						break;
					case SDLK_RIGHT:
					case SDLK_d:
						SMotion::move_entity(0, e_mgr, 25, 0);
						break;
					case SDLK_LEFT:
					case SDLK_a:
						SMotion::move_entity(0, e_mgr, -25, 0);
						break;
				}
				break;
		}
	}
}