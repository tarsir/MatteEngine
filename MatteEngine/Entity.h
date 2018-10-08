#pragma once

#include "ComponentList.h"
#include "BaseComponent.h"
#include <vector>
#include <string>

class Entity {
	private:
		uint32_t entity_id;
		std::vector<Component*> components;
	public:	
		void register_component(Component*);
		void unregister_component(Component*);
		void set_entity_id(uint32_t);
		uint32_t get_entity_id() const;

		Component* get_component(ComponentTypes) const; 

};

class EntityManager {
private:
	std::vector<Entity*> entity_list;
	uint32_t latest_entity_id;
public:
	EntityManager();
	Entity* register_entity(Entity*);
	std::vector<Entity*> entities_matching_component(ComponentTypes type);
	Entity* get_entity_by_id(uint32_t entity_id) const;
	Entity* delete_entity_by_id(uint32_t);
};