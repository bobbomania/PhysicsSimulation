#pragma once

// class handling the update of the entire world, containing all physics objects

#include <array>
#include <vector>
#include <memory>

#include "Utils.h"
#include "Solid.h"

#define GRAVITY_ACC glm::vec2({0.0f, -10.0f})

#define CELL_WIDTH 10 // in pixels, in reference to the uniform grid
#define GRID_WIDTH (int) (WIDTH_W / CELL_WIDTH)
#define GRID_HEIGHT (int) (HEIGHT_W / CELL_WIDTH)

#define TOT_CELLS GRID_WIDTH * GRID_HEIGHT

namespace world {

	using CellType = std::vector<Particle*>;

	class World {
	public:
		float m_Delta;

		// this grid is stored from top to bottom, left to right
		std::array< CellType, TOT_CELLS > m_UniformGrid;
		Solid m_Solids;

	private:
		std::unordered_map<SolidType, std::vector<Particle>> m_MovableParticles;
		std::vector<Particle> m_ImmovableParticles;

		glm::vec2 m_ZeroVector;

	private:
		void ClearGrid();

		int CoordToIndex(glm::vec2 coord);

		void CheckCollisions(CellType particles);
		void SimulateCollision(Particle *p1, Particle *p2);

	public:
		World(bool hasBoundaryBox = false);
		void IterateMovableParticles(void (*iter)(Particle *particle, World& world));
		void IterateImmovableParticles(void (*iter)(Particle* particle, World& world));
		std::vector<int> ParticleToIndices(Particle *particle);

		void Update(float delta);
		void AddParticle(Particle particle);
	};
}