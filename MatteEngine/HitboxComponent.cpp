#include "ComponentList.h"
#include "DrawableComponent.h"
#include "HitboxComponent.h"

void HitboxComponent::init_by_drawable_component(Entity* target_entity) {
	DrawableComponent *d_comp = dynamic_cast<DrawableComponent*>(target_entity->get_component(DRAWABLE));

	if (d_comp == nullptr) {
		this->w = 0;
		this->h = 0;
		return;
	}

	int w, h;
	SDL_QueryTexture(d_comp->get_texture(), NULL, NULL, &w, &h);
	this->w = w; this->h = h;
	return;
}
