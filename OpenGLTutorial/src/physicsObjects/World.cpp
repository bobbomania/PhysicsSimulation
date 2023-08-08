#include "World.h"

#include "BoundaryShapeMaker.h"

namespace world {

	World::World(BoundaryType type) : 
		m_ZeroVector(0.0f, 0.0f), m_Delta(0.0f) {

		float boundaryRadius = 10.0f;
		BoundaryShapeMaker boundaryShapeMaker(type, boundaryRadius);

		boundaryShapeMaker.AddWorldBoundary(*this);

	};


	// resets the uniform grid
	void World::ClearGrid()
	{
		for (int i = 0; i < TOT_CELLS; i++) {
			m_UniformGrid[i] = CellType();
		}

		// add all immovable particles to grid
		for (unsigned int i = 0; i < m_ImmovableParticles.size(); i++) {
			Particle *particle = &m_ImmovableParticles[i];

			for (int gridIndex : ParticleToIndices(particle)) {

				// temp
				if (gridIndex >= TOT_CELLS || gridIndex < 0) continue;
				
				m_UniformGrid[gridIndex].push_back(particle);
			}
		}
	}

	// returns the indices of the cells of the grid where the four corners of the particle rest on
	std::vector<int> World::ParticleToIndices(Particle *particle)
	{
		glm::vec2 pos = particle->Pos;
		std::vector<int> indices;

		float r = particle->radius;

		for (float xShift = -r; xShift < r; xShift += r * 2) {
			for (float yShift = -r; yShift < r; yShift += r * 2) {

				// TODO: implement for particles bigger than cell

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

	void World::SimulateCollision(Particle *p1, Particle *p2)
	{
		// revert them to original pre-collision position, also could move them 1/2 distance between centers
		p1->Pos += -p1->Vel * m_Delta;
		p2->Pos += -p2->Vel * m_Delta;

		// calculate new velocity with conservation of momentum and kinetic energy

		float m1 = m_Solids.getMass(p1);
		float m2 = m_Solids.getMass(p2);

		float totMass = m1 + m2;

		glm::vec2 deltaVelocity = p1->Vel - p2->Vel;
		glm::vec2 totMomentum = m1 * p1->Vel + m2 * p2->Vel;

		p1->Vel = (m_Solids.isImmovable(p1)) ? (m_ZeroVector) : ((m_Solids.getRestitution(p1) * m2 * -1 * deltaVelocity + totMomentum) / totMass);
		p2->Vel = (m_Solids.isImmovable(p2)) ? (m_ZeroVector) : ((m_Solids.getRestitution(p2) * m1 * deltaVelocity + totMomentum) / totMass);
	}

	void World::IterateMovableParticles(void(*iter)(Particle *particle, World& world))
	{
		for (SolidType type = NO_TYPE; type < LAST_SOLID_TYPE; type = (SolidType)(type + 1)) {
			std::vector<Particle> *currTypeParticles = &m_MovableParticles[type];

			// update particle physical attributes
			for (unsigned int i = 0; i < currTypeParticles->size(); i++) {
				(*iter)(&(*currTypeParticles)[i], *this);
			}
		}
	}

	void World::IterateImmovableParticles(void (*iter)(Particle* particle, World& world)) {
		for (unsigned int i = 0; i < m_ImmovableParticles.size(); i++) {
			(*iter)(&m_ImmovableParticles[i], *this);
		}
	}


	void UpdateParticlePhysics(Particle *particle, World& world)
	{
		particle->Pos += particle->Vel * world.m_Delta;
		particle->Vel += particle->Acc * world.m_Delta;
		particle->Acc  = GRAVITY_ACC; // temp

		// update grid cells with new particle
		for (int gridIndex : world.ParticleToIndices(particle)) {
			world.m_UniformGrid[gridIndex].push_back(particle);
		}
	}

	void World::Update(float delta)
	{
		m_Delta = delta;
		
		ClearGrid();
		IterateMovableParticles(&UpdateParticlePhysics);

		// collision detection
		for (int i = 0; i < TOT_CELLS; i++) {
			// if there is more than two particles in cell, check collision
			if (m_UniformGrid[i].size() >= 2) {
				CheckCollisions(m_UniformGrid[i]);
			}
		}
	}

	void World::AddParticle(Particle particle)
	{

		if (m_Solids.isImmovable(&particle)) {
			return m_ImmovableParticles.push_back(particle);
		}

		m_MovableParticles[particle.type].push_back(particle);
	}

	// collision detection among a set of particles
	void World::CheckCollisions(CellType particles)
	{
		int totParticles = particles.size();

		// if the last particle is immovable, then all other particles are
		if (totParticles < 2 || m_Solids.isImmovable(particles.back())) return;

		// as immovable particles are always added before movable particles,
		// and collisions between immovable particles are trivial, we start checking collisions 
		// only between immovable particles and movable particles, or btw. movable particles

		int start = 0; // index of first movable particle

		// TODO: test, obviously
		while (start < totParticles && m_Solids.isImmovable(particles[start++]));
		
		for (int i = 0; i < totParticles; i++) {
			// for all movable particles (idx >= start), discard checked pairs, 
			// if immovable (idx < start), start at the first movable particle
			for (int j = (i >= start ? i : start);
					 j < totParticles; 
					 j++) {
				
				if (i != j) {

					Particle *p1 = particles[i];
					Particle *p2 = particles[j];

					float r = p1->radius;

					glm::vec2 p2Pos = p2->Pos;
					glm::vec2 corner;

					// if a corner of the collision box is within the other square, collision detected
					for (float xShift = -r; xShift < r; xShift += r * 2) {
						for (float yShift = -r; yShift < r; yShift += r * 2) {
							
							corner = p1->Pos + glm::vec2(xShift, yShift);
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
}
