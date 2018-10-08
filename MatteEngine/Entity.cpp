#include <algorithm>
#include <iterator>
#include <vector>
#include "AnimationComponent.h"
#include "SpriteMapComponent.h"
#include "PositionComponent.h"
#include "DrawableComponent.h"
#include "ComponentList.h"
#include "Logging.h"
#include "Entity.h"
#include <spdlog\spdlog.h>

auto entity_cpp_logger = spdlog::stdout_color_mt("Entity.cpp");

void Entity::register_component(Component* component) {
	this->components.push_back(component);
}

void Entity::unregister_component(Component* component) {
	std::vector<Component*>::const_iterator searcher = std::find(this->components.cbegin(), this->components.cend(), component);
	if (searcher != this->components.cend()) {
		info("Attempted to remove component not present on the entity");
		return;
	} else {
		this->components.erase(searcher);
		return;
	}
}

void Entity::set_entity_id(uint32_t id) {
	this->entity_id = id;
}

uint32_t Entity::get_entity_id() const {
	return this->entity_id;
}

EntityManager::EntityManager() {
	this->latest_entity_id = 0;
}

Entity* EntityManager::register_entity(Entity* new_entity) {
	new_entity->set_entity_id(this->latest_entity_id);
	this->entity_list.push_back(new_entity);
	this->latest_entity_id += 1;
	if (this->latest_entity_id % 1000 == 0) {
		entity_cpp_logger->info("Added new entity with ID {}, now have: {} entities", new_entity->get_entity_id(), this->latest_entity_id);
	}
	return new_entity;
}

Component* Entity::get_component(ComponentTypes type) const {
	auto matcher = [&type](Component* search_component)
	{
		switch (type) {
		case DRAWABLE:
			if (dynamic_cast<DrawableComponent*>(search_component)) {
				return true;
			}
			break;
		case POSITION:
			if (dynamic_cast<PositionComponent*>(search_component)) {
				return true;
			}
			break;
		case ANIMATION:
			if (dynamic_cast<AnimationComponent*>(search_component)) {
				return true;
			}
			break;
		case SPRITE_MAP:
			if (dynamic_cast<SpriteMapComponent*>(search_component)) {
				return true;
			}
			break;
		default:
			entity_cpp_logger->error("wtf this component ain't real");
			break;
		}
		return false;
	};

	std::vector<Component*>::const_iterator searcher = std::find_if(this->components.cbegin(), this->components.cend(), matcher);
	if (searcher == this->components.cend()) {
		//entity_cpp_logger->error("get_component({}) found nothing", type);
		return NULL;
	}
	else {
		return *searcher;
	}
}

Entity* EntityManager::get_entity_by_id(uint32_t entity_id) const {
	std::vector<Entity*>::const_iterator it = std::find_if(this->entity_list.cbegin(), this->entity_list.cend(), [entity_id](Entity* search_entity) {
		if (search_entity->get_entity_id() == entity_id) {
			return true;
		}
		return false;
	});
	if (it == this->entity_list.cend()) {
		entity_cpp_logger->error("get_entity_by_id({}) found nothing", entity_id);
		return NULL;
	}
	else {
		return *it;
	}
}

std::vector<Entity*> EntityManager::entities_matching_component(ComponentTypes component_type) {
	std::vector<Entity*> result_list;
	std::vector<Entity*>::const_iterator front = this->entity_list.cbegin(), back = this->entity_list.cend();

	std::copy_if(front, back, std::back_inserter(result_list), [component_type](Entity* search_entity) {
		if (search_entity->get_component(component_type)) {
			return true;
		}
		return false;
	});

	return result_list;
}