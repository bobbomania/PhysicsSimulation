#pragma once

#include "glm/glm.hpp"
#include "Collider.h"

namespace world {

	struct SolidStruct {
		float Density;
		float Friction;
		float Restitution;
		float Immovable;

		glm::vec4 Color;
		Collider *Collider;
	};
}
