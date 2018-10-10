#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <SDL.h>
#include "BaseComponent.h"
#include "ComponentList.h"
#include "spdlog\spdlog.h"


enum Facing {
	NORTH = 99000,
	EAST,
	SOUTH,
	WEST
};

/*
	What does this do?
*/
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
	AnimationInfo get_current_animation_description();
	int advance_animation();
	void stop_motion();
	void start_motion();
	bool is_moving();
	std::string get_neutral_description_for_direction(Facing direction);
};