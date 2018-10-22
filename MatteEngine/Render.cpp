#pragma once
#include <vector>
#include <algorithm>
#include "Entity.h"
#include "Graphics.h"
#include "spdlog\spdlog.h"

#include "ComponentList.h"
#include "AnimationComponent.h"
#include "DrawableComponent.h"
#include "FacingComponent.h"
#include "PositionComponent.h"
#include "SpriteMapComponent.h"
#include "Render.h"

auto render_logger = spdlog::stdout_color_mt("Render.h");

struct LayerComparison {
	bool operator()(const Entity* lhs, const Entity* rhs) const {
		DrawableComponent *lhd = dynamic_cast<DrawableComponent*>(lhs->get_component(DRAWABLE)), 
			*rhd = dynamic_cast<DrawableComponent*>(rhs->get_component(DRAWABLE));
		return lhd->get_layer() > rhd->get_layer();
	}
} sorter;

namespace SRender {
	void draw_single_entity(const Entity* entity, Graphics* gfx = Graphics::getInstance()) {
		DrawableComponent *drawable = dynamic_cast<DrawableComponent*>(entity->get_component(DRAWABLE));
		PositionComponent *position = dynamic_cast<PositionComponent*>(entity->get_component(POSITION));
		if (position == nullptr || drawable == nullptr) {
			render_logger->error("Drawing entity with ID {} broke", entity->get_entity_id());
		}

		apply_surface_to_screen(drawable->get_texture(), position, gfx);
	}

	void draw_entity_from_anim_description(const Entity* entity, Graphics* gfx = Graphics::getInstance()) {
		DrawableComponent *drawable = dynamic_cast<DrawableComponent*>(entity->get_component(DRAWABLE));
		FacingComponent *facing = dynamic_cast<FacingComponent*>(entity->get_component(FACING));
		PositionComponent *position = dynamic_cast<PositionComponent*>(entity->get_component(POSITION));
		SpriteMapComponent *sprite_map = dynamic_cast<SpriteMapComponent*>(entity->get_component(SPRITE_MAP));
		AnimationComponent *anim = dynamic_cast<AnimationComponent*>(entity->get_component(ANIMATION));

		if (position == nullptr ||
			drawable == nullptr ||
			sprite_map == nullptr ||
			facing == nullptr ||
			anim == nullptr) {
			render_logger->error("Drawing entity with ID {} broke", entity->get_entity_id());
		}
		std::string neutral_for_direction = anim->get_neutral_description_for_direction(facing->getDirection());

		apply_partial_texture_to_screen(
			drawable->get_texture(),
			sprite_map->get_clipping_rect_for_animation(neutral_for_direction),
			position,
			gfx
			);
	}

	void update(EntityManager* entity_mgr, Graphics* gfx = Graphics::getInstance()) {
		std::vector<Entity*> drawable_entities = entity_mgr->entities_matching_component(DRAWABLE);
		std::sort(drawable_entities.begin(), drawable_entities.end(), sorter);

		for (auto entity : drawable_entities) {
			SpriteMapComponent *sprite_map = dynamic_cast<SpriteMapComponent*>(entity->get_component(SPRITE_MAP));
			if (sprite_map == nullptr) {
				draw_single_entity(entity, gfx);
			}
			else {
				draw_entity_from_anim_description(entity, gfx);
			}
		}
	}
}
