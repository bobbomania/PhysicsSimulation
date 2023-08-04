#pragma once
#include "Solid.h"

// Physical properties of Sand
#define SAND_WEIGHT 1.0f
#define SAND_FRICTION 0.5f
#define SAND_RESTITUTION 0.5f
#define SAND_IMMOVABLE false
#define SAND_COLOR {1.0f, 1.0f, 0.0f, 0.0f}

// Class implementing a Sand physics object

namespace world {
	class Sand : public Solid{
	public:
		Sand();
	};
}