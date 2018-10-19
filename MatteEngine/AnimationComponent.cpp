#include "AnimationComponent.h"
#include "FacingConstants.h"

auto animation_c_logger = spdlog::stdout_color_mt("AnimationComponent.h");

AnimationInfo AnimationComponent::get_current_animation_description() {
	return this->animation_sequence[this->current_animation];
}

int AnimationComponent::advance_animation() {
	if (this->is_in_motion) {
		this->current_animation = (this->current_animation == this->animation_sequence.size() - 1)
			? 0
			: this->current_animation + 1;
	}
	return this->current_animation;
}

void AnimationComponent::stop_motion() {
	this->is_in_motion = false;
}

void AnimationComponent::start_motion() {
	this->is_in_motion = true;
}

bool AnimationComponent::is_moving() {
	return this->is_in_motion;
}

std::string AnimationComponent::get_neutral_description_for_direction(FacingDirection direction) {
	auto is_neutral_for_direction = [direction](AnimationInfo anim_info) {
		return anim_info.is_neutral && anim_info.animation_direction == direction;
	};
	auto it = std::find_if(this->animation_sequence.begin(), this->animation_sequence.end(), is_neutral_for_direction);
	if (it != this->animation_sequence.end()) {
		return it->description;
	}

	animation_c_logger->error("Could not find matching neutral for direction: {}", direction);
	return NULL;
}
