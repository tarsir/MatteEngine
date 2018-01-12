#pragma once
#include <SDL.h>
#include <vector>
#include <algorithm>
#include "ComponentList.h"
#include "DrawableComponent.h"
#include "PositionComponent.h"
#include "Entity.h"
#include "Graphics.h"
#include "spdlog\spdlog.h"

auto render_logger = spdlog::stdout_color_mt("Render.h");

struct LayerComparison {
	bool operator()(const Entity* lhs, const Entity* rhs) const {
		DrawableComponent *lhd = dynamic_cast<DrawableComponent*>(lhs->get_component(DRAWABLE)), *rhd = dynamic_cast<DrawableComponent*>(rhs->get_component(DRAWABLE));
		return lhd->get_layer() < rhd->get_layer();
	}
} sorter;

namespace SRender {
	void draw_single_entity(const Entity* entity, Graphics* gfx) {
		DrawableComponent *drawable = dynamic_cast<DrawableComponent*>(entity->get_component(DRAWABLE));
		PositionComponent *position = dynamic_cast<PositionComponent*>(entity->get_component(POSITION));
		if (position == nullptr || drawable == nullptr) {
			render_logger->error("Drawing entity with ID {} broke", entity->get_entity_id());
		}

		apply_surface_to_screen(drawable->get_texture(), gfx, position);
	}

	void draw_entities(EntityManager* entity_mgr, Graphics* gfx) {
		std::vector<Entity*> drawable_entities = entity_mgr->entities_matching_component(DRAWABLE);
		std::sort(drawable_entities.begin(), drawable_entities.end(), sorter);

		for (auto entity : drawable_entities) {
			draw_single_entity(entity, gfx);
		}
	}
} 

