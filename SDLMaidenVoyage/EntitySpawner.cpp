#include "EntitySpawner.h"
#include "World.h" //patch

EntitySpawner::EntitySpawner(World& world_) {
	world = &world_;
}

void EntitySpawner::SpawnZombie() {
	int spawnIndex = HelperFunctions::GenerateRandomSpawn(0, TOTAL_ZOMBIE_SPAWNS);
	vec2 spawnPoint = zombieSpawnPoints[spawnIndex];
	Wave* worldWaveInfo = world->GetWaveInfo();
	Zombie* zombie = new Zombie(spawnPoint, worldWaveInfo->zombieSpeed, worldWaveInfo->zombieHealth, worldWaveInfo->zombieDamage);
	world->AddEntity(zombie);
}

void EntitySpawner::SpawnSniper() {
	
	int spawnIndex = HelperFunctions::GenerateRandomSpawn(0, TOTAL_SNIPER_SPAWNS);
	vec2 spawnPoint = zombieSpawnPoints[spawnIndex];

	Sniper* sniper = new Sniper(spawnPoint, *this, world->GetWaveInfo()->sniperSpeed, world->GetWaveInfo()->sniperHealth);
	world->AddEntity(sniper);

}

void EntitySpawner::SpawnBullet(Bullet* bullet) {
	bullet->PLAYER_BULLET_DAMAGE = world->GetWaveInfo()->weaponDamage;
	bullet->SNIPER_BULLET_DAMAGE = world->GetWaveInfo()->sniperDamage;
	world->AddEntity(bullet);
}



/*			--------NOT IN USE--------

 void EntitySpawner::FreeSniperLocation(const vec2& sniperLocation) {
	auto it = std::find(activeSniperLocations.begin(), activeSniperLocations.end(), sniperLocation);
	if (it != ActiveSniperLocations.end()) {
		ActiveSniperLocations.erase(it);
	}
}

*/
