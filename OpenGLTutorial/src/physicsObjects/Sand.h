#pragma once
#include "Solid.h"

namespace world {
	class Sand : public Solid{
	public:
		void Update(World* world);
	};
}