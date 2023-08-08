#ifndef WORLD_H
#define WORLD_H

#pragma once

// class handling the update of the entire world, containing all physics objects

#include <array>
#include <vector>
#include <memory>

#include "Solid.h"
#include "Particle.h"

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

		void CheckCollisions(CellType particles);
		void SimulateCollision(Particle *p1, Particle *p2);

	public:
		World(BoundaryType type = NO_BOUNDARY);
		void IterateMovableParticles(void (*iter)(Particle *particle, World& world));
		void IterateImmovableParticles(void (*iter)(Particle* particle, World& world));

		void Update(float delta);
		void AddParticle(Particle particle);
	};
}

#endif