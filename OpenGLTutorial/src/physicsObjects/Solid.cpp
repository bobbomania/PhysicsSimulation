#include "Solid.h"

// class implementing the Solid header file

namespace world {
	void Solid::Update(World* world)
	{
		
	}


	void Solid::AddParticles(std::vector<Particle> particles)
	{
		m_Particles.insert(m_Particles.end(), particles.begin(), particles.end());
	}
}
