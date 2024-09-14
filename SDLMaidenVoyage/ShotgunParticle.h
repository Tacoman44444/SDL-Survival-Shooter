#pragma once

#include "Particle.h"

class ShotgunParticle : public Particle {

	public:
		ShotgunParticle(const vec2& position);
		void Render() override;
		bool IsDead() override;

	private:
		vec2 mPosition;
		int mFrame;
		LTexture* mTexture;


};