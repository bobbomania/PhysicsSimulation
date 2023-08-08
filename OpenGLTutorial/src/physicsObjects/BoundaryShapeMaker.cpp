#include "BoundaryShapeMaker.h"

namespace world {

	void BoundaryShapeMaker::AddWorldBoundary(World& world)
	{

		switch (m_Type) {
			case NO_BOUNDARY: return;
			case BOX: return BoxBoundaryShape(world);
			case CIRCLE: return CircleBoundaryShape(world);

			default: return; // unimplemented
		}

	}

	void BoundaryShapeMaker::BoxBoundaryShape(World& world)
	{
		// make top and bottom edges
		for (float x = 0; x < WIDTH_W; x += m_BoundaryRadius) {

			m_Particle.Pos = { x, 0.0f };
			world.AddParticle(m_Particle);

			m_Particle.Pos = { x, HEIGHT_W };
			world.AddParticle(m_Particle);

		}

		// make left and right edges
		for (float y = 0; y < HEIGHT_W; y += m_BoundaryRadius) {

			m_Particle.Pos = { 0.0f, y };
			world.AddParticle(m_Particle);

			m_Particle.Pos = { WIDTH_W, y };
			world.AddParticle(m_Particle);
		}
	}

	void BoundaryShapeMaker::CircleBoundaryShape(World& world)
	{
		float del = 0.01f;

		// get minimum 
		float radius = (HEIGHT_W > WIDTH_W) ? WIDTH_W : HEIGHT_W;
		radius /= 2; // was diameter

		// make top and bottom edges
		for (float theta = 0.0f; theta <= 2 * PI; theta += del) {

			m_Particle.Pos = { radius + radius * cos(theta), radius + radius * sin(theta) };
			world.AddParticle(m_Particle);

		}
	}
}
