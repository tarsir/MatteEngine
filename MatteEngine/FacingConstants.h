#pragma once

enum FacingDirection {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

namespace CFacing {
	bool is_opposite_directions(FacingDirection a, FacingDirection b);
	FacingDirection get_opposite_direction(FacingDirection);
}