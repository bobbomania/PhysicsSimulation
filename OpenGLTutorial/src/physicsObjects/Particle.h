#pragma once
#include "glm/glm.hpp"

#include "Utils.h"

// class handling the definition of particle related structures and enumerations

namespace world {

	#define GRAVITY_ACC glm::vec2({0.0f, 0.0f})

	#define CELL_WIDTH 50 // in pixels, in reference to the uniform grid
	#define GRID_WIDTH (int) (WIDTH_W / CELL_WIDTH)
	#define GRID_HEIGHT (int) (HEIGHT_W / CELL_WIDTH)

	#define TOT_CELLS GRID_WIDTH * GRID_HEIGHT

	enum SolidType {
		NO_TYPE = -1,
		SAND,
		BARRIER,
		LAST_SOLID_TYPE
	};

	struct Particle {
		float radius;

		glm::vec2 Pos;
		glm::vec2 Vel;
		glm::vec2 Acc;

		SolidType type; 
	};

	// type of outer boundary
	enum BoundaryType {
		NO_BOUNDARY = 0,
		BOX,
		CIRCLE
	};

	// returns the index of the cell containing the given coordinate
	inline int CoordToIndex(glm::vec2 coord)
	{
		int col = (int)coord.x / CELL_WIDTH;
		int row = (int)coord.y / CELL_WIDTH;

		return (col - 1) * GRID_HEIGHT + row; // top to bottom, left to right
	}
}