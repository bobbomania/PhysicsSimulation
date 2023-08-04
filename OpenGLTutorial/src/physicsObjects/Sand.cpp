#include "Sand.h"

// Class implementing the Sand header file

namespace world {
	Sand::Sand() : Solid(SAND_WEIGHT, 
						SAND_FRICTION, 
						SAND_RESTITUTION,
						SAND_COLOR, 
						SAND_IMMOVABLE) {

	}
}

