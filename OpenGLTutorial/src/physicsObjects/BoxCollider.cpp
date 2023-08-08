#include "BoxCollider.h"

bool world::BoxCollider::DetectCollision(const Particle* particle, const Particle* other)
{
	float r = particle->radius;

	glm::vec2 p2Pos = other->Pos;
	glm::vec2 corner;

	// if a corner of the collision box is within the other square, collision detected
	for (float xShift = -r; xShift <= r; xShift += r * 2) {
		for (float yShift = -r; yShift <= r; yShift += r * 2) {

			corner = particle->Pos + glm::vec2(xShift, yShift);
			if (corner.x < p2Pos.x + r &&
				corner.x > p2Pos.x - r &&
				corner.y < p2Pos.y + r &&
				corner.y > p2Pos.y - r) {
				return true;
			}
		}
	}

	return false;
}

void world::BoxCollider::FixCollisionOverlap(Particle* particle, const Particle* other, float delta)
{
	// revert them to original pre-collision position, also could move them 1/2 distance between centers
	particle->Pos += -particle->Vel * delta;
}

std::vector<int> world::BoxCollider::GetColliderPoints(const Particle* particle)
{
	glm::vec2 pos = particle->Pos;
	std::vector<int> indices;

	float r = particle->radius;

	for (float xShift = -r; xShift <= r; xShift += r * 2) {
		for (float yShift = -r; yShift <= r; yShift += r * 2) {

			// TODO: implement for particles bigger than cell
			indices.push_back(CoordToIndex(pos + glm::vec2(xShift, yShift)));
		}
	}

	return indices;
}
