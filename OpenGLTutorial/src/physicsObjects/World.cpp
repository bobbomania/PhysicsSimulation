#include "World.h"

namespace world {

	// resets the uniform grid
	void World::ClearGrid()
	{
		memset(m_UniformGrid.data(), 0, sizeof(m_UniformGrid.data()));
	}

	// returns the indices of the cells of the grid where the four corners of the particle rest on
	std::vector<int> World::ParticleToIndices(Particle particle)
	{
		glm::vec2 pos = particle.Pos;
		std::vector<int> indices;

		float r = particle.radius;

		for (float xShift = -r; xShift < r; xShift += r * 2) {
			for (float yShift = -r; yShift < r; yShift += r * 2) {
				indices.push_back(CoordToIndex(pos + glm::vec2(xShift, yShift)));
			}
		}

		return indices;
	}

	// returns the index of the cell containing the given coordinate
	int World::CoordToIndex(glm::vec2 coord)
	{
		int col = (int) coord.x / CELL_WIDTH; 
		int row = (int) coord.y / CELL_WIDTH;

		return (col - 1) * GRID_HEIGHT + row; // top to bottom, left to right
	}

	void World::SimulateCollision(Particle p1, Particle p2)
	{
		// revert them to original pre-collision position, also could move them 1/2 distance between centers
		p1.Pos += -p1.Vel * m_Delta;
		p2.Pos += -p2.Vel * m_Delta;

		// calculate new velocity with conservation of momentum and kinetic energy

		float m1 = m_Solids.getMass(p1);
		float m2 = m_Solids.getMass(p2);

		float totMass = m1 + m2;

		glm::vec2 deltaVelocity = p1.Vel - p2.Vel;
		glm::vec2 totMomentum = m1 * p1.Vel + m2 * p2.Vel;

		p1.Vel = (m_Solids.isImmovable(p1)) ? (m_ZeroVector) : ((m_Solids.getRestitution(p1) * m2 * -1 * deltaVelocity + totMomentum) / totMass);
		p2.Vel = (m_Solids.isImmovable(p2)) ? (m_ZeroVector) : ((m_Solids.getRestitution(p2) * m1 * deltaVelocity + totMomentum) / totMass);
	}

	void World::Update()
	{
		ClearGrid();

		Particle particle;

		// update particle physical attributes
		for (int i = 0; i < m_Particles.size(); i++) {
			
			particle = m_Particles[i];

			particle.Pos += particle.Vel * m_Delta;
			particle.Vel += particle.Acc * m_Delta;
			particle.Acc += (m_Solids.isImmovable(particle) ? m_ZeroVector : GRAVITY_ACC); // temp

			// update grid cells with new particle
			for (int gridIndex : ParticleToIndices(particle)) {
				m_UniformGrid[gridIndex].push_back(i);
			}
		}

		// collision detection
		for (int i = 0; i < TOT_CELLS; i++) {
			// if there is more than two particles in cell, check collision
			if (m_UniformGrid[i].size() >= 2) {
				CheckCollisions(m_UniformGrid[i]);
			}
		}
	}

	// collision detection among a set of particles
	void World::CheckCollisions(std::vector<unsigned int> particles)
	{
		int totParticles = particles.size();
		
		for (int i = 0; i < totParticles; i++) {
			for (int j = 0; j < totParticles; j++) {
				
				if (i != j) {

					Particle p1 = m_Particles[i];
					Particle p2 = m_Particles[j];

					int r = p1.radius;

					glm::vec2 p2Pos = p2.Pos;
					glm::vec2 corner;

					// if a corner of the collision box is within the other square, collision detected
					for (float xShift = -r; xShift < r; xShift += r * 2) {
						for (float yShift = -r; yShift < r; yShift += r * 2) {
							
							corner = p1.Pos + glm::vec2(xShift, yShift);
							if (corner.x < p2Pos.x + r &&
								corner.x > p2Pos.x - r &&
								corner.y < p2Pos.y + r &&
								corner.y > p2Pos.y - r) {
								SimulateCollision(p1, p2);
							}							
						}
					}

				}

			}
		}
	}

	// draws all objects in the world
	void World::Draw(const Renderer& renderer)
	{

	}
}
