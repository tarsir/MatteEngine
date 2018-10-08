#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <SDL.h>
#include "BaseComponent.h"
#include "ComponentList.h"
#include "spdlog\spdlog.h"

//auto animation_c_logger = spdlog::stdout_color_mt("AnimationComponent.h");

enum Facing {
	NORTH = 99000,
	EAST,
	SOUTH,
	WEST
};

struct AnimationFrame {

};

struct AnimationInfo {
	std::string description;
	bool is_neutral;
	Facing animation_direction;
	int duration; //how long to stay on this frame in ms
	int sequence_number;
};

class AnimationComponent : public Component {
	static const ComponentTypes c_type = ANIMATION;
	std::vector<AnimationInfo> animation_sequence;
	int current_animation;
	bool is_in_motion;

public:
	AnimationComponent(std::vector<AnimationInfo> sequence) : animation_sequence{ sequence } {
		this->current_animation = 0;
		this->is_in_motion = false;
	}

	AnimationInfo get_current_animation_description() {
		return this->animation_sequence[this->current_animation];
	}

	int advance_animation() {
		this->current_animation = this->current_animation == this->animation_sequence.size() ? 0 : this->current_animation + 1;
		return this->current_animation;
	}

	void stop_motion() {
		this->is_in_motion = false;
	}

	void start_motion() {
		this->is_in_motion = true;
	}

	bool is_moving() {
		return this->is_in_motion;
	}

	std::string get_neutral_description_for_direction(Facing direction) {
		auto is_neutral_for_direction = [direction](AnimationInfo anim_info) {
			return anim_info.is_neutral && anim_info.animation_direction == direction;
		};
		auto it = std::find_if(this->animation_sequence.begin(), this->animation_sequence.end(), is_neutral_for_direction);
		if (it != this->animation_sequence.end()) {
			return it->description;
		}

		//TODO: move this to .cpp file
		//animation_c_logger->error("Could not find matching neutral for direction: {}", direction);
		return NULL;
	}
};