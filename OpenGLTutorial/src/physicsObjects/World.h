#pragma once
#include <vector>
#include <memory>

struct Particle {
	glm::vec3 Pos;
	glm::vec3 Vel;
	glm::vec3 Acc;
	float width; // box shape assumed
	// float mass; // to add maybe
};

namespace world {
	class Solid;

	class World {
	public:

		std::vector<std::unique_ptr<world::Solid>> m_Solids;
		float delta;
	};
}