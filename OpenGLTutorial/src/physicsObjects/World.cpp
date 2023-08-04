#include "World.h"

namespace world {

	void World::ClearGrid()
	{
		memset(m_UniformGrid.data(), 0, sizeof(m_UniformGrid.data()));
	}

	// returns the indices of the cells of the grid where the four corners of the particle rest on
	std::vector<int> World::ParticleToIndices(Particle particle)
	{
		glm::vec2 pos = particle.Pos;
		std::vector<int> indices;

		for (int xShift = -particle.radius; xShift < particle.radius; xShift += particle.radius * 2) {
			for (int yShift = -particle.radius; yShift < particle.radius; yShift += particle.radius * 2) {
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

	void World::Update()
	{
		ClearGrid();

		Particle particle;

		// update particle physical attributes
		for (int i = 0; i < m_Particles.size(); i++) {
			
			particle = m_Particles[i];

			particle.Pos += m_Delta * particle.Vel;
			particle.Vel += m_Delta * particle.Acc;
			particle.Acc += GRAVITY_ACC; // temp

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

					

				}

			}
		}
	}
}
