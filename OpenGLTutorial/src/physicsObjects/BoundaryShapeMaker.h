
#ifndef BOUNDARYSHAPEMAKER_H
#define BOUNDARYSHAPERMAKER_H

#pragma once

#include <math.h> 
#include "World.h"

constexpr float PI = 3.1415926f;

namespace world {

	class BoundaryShapeMaker {
	private:
		BoundaryType m_Type;

		float m_BoundaryRadius;
		Particle m_Particle;
	public:
		BoundaryShapeMaker(BoundaryType type, float radius) :
			m_Type(type),
			m_BoundaryRadius(radius),
			m_Particle{ radius, {0,0}, {0,0}, {0,0}, BARRIER } {};

		void AddWorldBoundary(World& world);

	private:
		void BoxBoundaryShape(World& world);
		void CircleBoundaryShape(World& world);

	};
}

#endif