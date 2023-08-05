#pragma once
#include <array>
#include <vector>
#include <memory>

#include "glm/glm.hpp"

#include "Solid.h"
#include "Renderer.h"

#define GRAVITY_ACC glm::vec2({0.0f, 10.0f})

#define CELL_WIDTH 10 // in pixels, in reference to the uniform grid
#define GRID_WIDTH (int) (WIDTH_W / CELL_WIDTH)
#define GRID_HEIGHT (int) (HEIGHT_W / CELL_WIDTH)

#define TOT_CELLS GRID_WIDTH * GRID_HEIGHT

namespace world {

	struct Particle {
		glm::vec2 Pos;
		glm::vec2 Vel;
		glm::vec2 Acc;

		SolidType type;
		float radius; // box shape assumed
	};

	class World {
	private:
		glm::vec2 m_ZeroVector;
		std::vector<Particle> m_Particles;

		Solid m_Solids;
		
		std::array< std::vector<unsigned int>, TOT_CELLS > m_UniformGrid; // this grid is stored from top to bottom, left to right
		float m_Delta;

		void ClearGrid();
		std::vector<int> ParticleToIndices(Particle particle);
		int CoordToIndex(glm::vec2 coord);
		void SimulateCollision(Particle p1, Particle p2);


	public:
		World() : m_ZeroVector(0.0f, 0.0f) {};
		void Update();
		void CheckCollisions(std::vector<unsigned int> particles);
	};
}