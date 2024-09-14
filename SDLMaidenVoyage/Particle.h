#pragma once

#include "vec2.h"
#include "LTexture.h"

class Particle {

	public:
		virtual ~Particle() = default;
		virtual void Render() = 0;
		virtual bool IsDead() = 0;
};	