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

		float xShift = 60.0f;
		float yShift = 60.0f;

		// make top and bottom edges
		for (float x = xShift; x < WIDTH_W - xShift; x += m_BoundaryRadius) {

			m_Particle.Pos = { x, yShift };
			world.AddParticle(m_Particle);

			m_Particle.Pos = { x, HEIGHT_W - yShift};
			world.AddParticle(m_Particle);

		}

		// make left and right edges
		for (float y = yShift; y < HEIGHT_W - yShift; y += m_BoundaryRadius) {

			m_Particle.Pos = { xShift, y };
			world.AddParticle(m_Particle);

			m_Particle.Pos = { WIDTH_W - xShift, y };
			world.AddParticle(m_Particle);
		}
	}

	void BoundaryShapeMaker::CircleBoundaryShape(World& world)
	{
		float del = 0.01f;

		// get minimum 
		float radius = (HEIGHT_W > WIDTH_W) ? WIDTH_W : HEIGHT_W;
		radius /= 2; // was diameter

		float centerX = radius + (WIDTH_W / 2 - radius);
		float centerY = radius + (HEIGHT_W / 2 - radius);


		// make top and bottom edges
		for (float theta = 0.0f; theta <= 2 * PI; theta += del) {

			m_Particle.Pos = { centerX + radius * cos(theta), centerY + radius * sin(theta) };
			world.AddParticle(m_Particle);

		}
	}
}
