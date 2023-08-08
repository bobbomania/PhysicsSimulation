#pragma once
#include "Solid.h"

namespace world {

	float Solid::getMass(Particle *particle) {

		if (particle->type == BARRIER) return std::numeric_limits<float>::max();

		float area = particle->radius;
		area *= area; // simply square it

		return m_AllSolids[particle->type].Density * area;
	}

	float Solid::getRestitution(Particle *particle) {
		return m_AllSolids[particle->type].Restitution;
	}

	float Solid::getFriction(Particle *particle) {
		return m_AllSolids[particle->type].Friction;
	}

	bool Solid::isImmovable(Particle *particle) {
		return m_AllSolids[particle->type].Immovable;
	}

	glm::vec4 Solid::getColor(Particle *particle) {
		return m_AllSolids[particle->type].Color;
	}
}