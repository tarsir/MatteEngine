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
}