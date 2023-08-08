#pragma once

#include "Collider.h"

namespace world {
	class BoxCollider : public Collider {
	public:
		bool DetectCollision(const Particle* particle, const Particle* other);
		void FixCollisionOverlap(Particle* particle, const Particle* other, float delta);
		std::vector<int> GetColliderPoints(const Particle* particle);
	};
}