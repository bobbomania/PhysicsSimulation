#pragma once

#include "glm/glm.hpp"
#include <unordered_map>

#define SAND_INFO { 0.5f, 0.5f, 0.5f, false, {1.0f, 1.0f, 0.0f, 1.0f} }
#define BARRIER_INFO { 1.0f, 0.5f, 1.0f, true, {1.0f, 0.0f, 0.0f, 1.0f} }

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

	class Solid {
	private:
		std::unordered_map< SolidType, SolidStruct > m_AllSolids;

	public:
		float getMass(Particle particle);
		float getRestitution(Particle particle);
		float getFriction(Particle particle);
		bool isImmovable(Particle particle);
		glm::vec4 getColor(Particle particle);
	};
}
