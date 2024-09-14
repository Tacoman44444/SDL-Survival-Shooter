#include "ShotgunParticle.h"

ShotgunParticle::ShotgunParticle(const vec2& position) {
	mPosition.x = position.x - 5 + (rand() % 25);
	mPosition.y = position.y - 5 + (rand() % 25);

	mFrame = rand() % 5;

	mTexture = &gShotgunParticleTexture;
}

void ShotgunParticle::Render() {
	mTexture->Render(mPosition.x, mPosition.y);

	mFrame++;
}

bool ShotgunParticle::IsDead() {
	return mFrame > 10;
}