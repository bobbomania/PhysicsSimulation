#pragma once

#include <vector>
#include "glm/glm.hpp"

#include "World.h"

namespace world {
	class Solid {
	private:
		// physics attributes
		float m_Weight;
		float m_Friction;
		float m_Restitution;
		bool m_Immovable;

		glm::vec4 m_Color;
		std::vector<Particle> m_Particles;

	public:
		Solid(float weight, float friction, float restitution, glm::vec4 color, bool immovable = false) :
			m_Weight(weight), m_Friction(friction),
			m_Restitution(restitution), m_Immovable(immovable), m_Color(color) {};

		void Update(World* world);
		void AddParticles(std::vector<Particle> particles);
	};
}