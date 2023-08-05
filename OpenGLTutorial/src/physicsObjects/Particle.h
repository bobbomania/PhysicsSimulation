#pragma once
#include "glm/glm.hpp"

// class handling the definition of particle related structures and enumerations

namespace world {

	enum SolidType {
		NO_TYPE = -1,
		SAND,
		BARRIER
	};

	struct SolidStruct {
		float Density;
		float Friction;
		float Restitution;
		float Immovable;
		glm::vec4 Color;
	};

	struct Particle {
		glm::vec2 Pos;
		glm::vec2 Vel;
		glm::vec2 Acc;

		SolidType type;
		float radius; // box shape assumed
	};

}