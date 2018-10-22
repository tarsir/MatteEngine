#include "FacingConstants.h"

namespace CFacing {
	bool is_opposite_directions(FacingDirection a, FacingDirection b) {
		switch (a) {
		case NORTH:
			return b == SOUTH;
		case EAST:
			return b == WEST;
		case WEST:
			return b == EAST;
		case SOUTH:
			return b == NORTH;
		}
	}

	FacingDirection get_opposite_direction(FacingDirection a) {
		if (a == NORTH) return SOUTH;
		else if (a == SOUTH) return NORTH;
		else if (a == EAST) return WEST;
		else if (a == WEST) return EAST;
	}
}