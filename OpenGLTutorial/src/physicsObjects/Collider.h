#pragma once
#include "Particle.h"
#include <vector>

namespace world {
	class Collider {
	public:
		virtual bool DetectCollision(const Particle* particle, const Particle* other) = 0;
		virtual void FixCollisionOverlap(Particle* particle, const Particle* other, float delta) = 0;
		virtual std::vector<int> GetColliderPoints(const Particle* particle) = 0;
	};
}