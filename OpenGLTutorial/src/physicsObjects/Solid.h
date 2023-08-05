#pragma once

// class used to access properties of various solids in a more memory efficient way

#include "Particle.h"
#include <unordered_map>

#define SAND_INFO { 0.5f, 0.5f, 0.5f, false, {1.0f, 1.0f, 0.0f, 1.0f} }
#define BARRIER_INFO { 1.0f, 0.5f, 1.0f, true, {1.0f, 0.0f, 0.0f, 1.0f} }

namespace world {
	class Solid {
	private:
		std::unordered_map< SolidType, SolidStruct > m_AllSolids;

	public:

		Solid() {
			m_AllSolids[SAND] = SAND_INFO;
			m_AllSolids[BARRIER] = BARRIER_INFO;
		}

		float getMass(Particle particle);
		float getRestitution(Particle particle);
		float getFriction(Particle particle);
		bool isImmovable(Particle particle);
		glm::vec4 getColor(Particle particle);
	};
}
