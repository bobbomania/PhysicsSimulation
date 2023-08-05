#pragma once

// class handling the update of the entire world, containing all physics objects

#include <array>
#include <vector>
#include <memory>

#include "Renderer.h"

#include "Solid.h"

#define GRAVITY_ACC glm::vec2({0.0f, 10.0f})

#define CELL_WIDTH 10 // in pixels, in reference to the uniform grid
#define GRID_WIDTH (int) (WIDTH_W / CELL_WIDTH)
#define GRID_HEIGHT (int) (HEIGHT_W / CELL_WIDTH)

#define TOT_CELLS GRID_WIDTH * GRID_HEIGHT

namespace world {

	class World {
	private:
		float m_Delta;
		std::vector<Particle> m_Particles;

		Solid m_Solids;

		// this grid is stored from top to bottom, left to right
		std::array< std::vector<unsigned int>, TOT_CELLS > m_UniformGrid; 
		glm::vec2 m_ZeroVector;

	private:
		void ClearGrid();
		std::vector<int> ParticleToIndices(Particle particle);
		int CoordToIndex(glm::vec2 coord);
		void SimulateCollision(Particle p1, Particle p2);

	public:
		World() : m_ZeroVector(0.0f, 0.0f) {};
		void Update();
		void Draw(const Renderer& renderer);
		void CheckCollisions(std::vector<unsigned int> particles);
	};
}