#pragma once

#include "Sniper.h"
#include "Zombie.h"
#include "HelperFunctions.h"
#include <algorithm>

class World;

class EntitySpawner {

public:

	EntitySpawner(World& world);

	void SpawnZombie();
	void SpawnSniper();
	void SpawnBullet(Bullet* bullet);

	void FreeSniperLocation(const vec2& sniperLocation);

private:
	
	World* world;
};