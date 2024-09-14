#include "EntitySpawner.h"
#include "World.h"

EntitySpawner::EntitySpawner(World& world_) {
	world = &world_;
}

void EntitySpawner::SpawnZombie() {
	int spawnIndex = HelperFunctions::GenerateRandomSpawn(0, TOTAL_ZOMBIE_SPAWNS);
	vec2 spawnPoint = zombieSpawnPoints[spawnIndex];
	Zombie* zombie = new Zombie(spawnPoint);
	world->AddEntity(zombie);
}

void EntitySpawner::SpawnSniper(std::vector<vec2>& activeSniperLocations) {
	
	Coordinate spawnPoint = Coordinate(-100, -100);
	do
	{
		std::cout << "spawn sniper while loop running\n";
		int spawnIndex = HelperFunctions::GenerateRandomSpawn(0, TOTAL_SNIPER_SPAWNS);
		spawnPoint = sniperSpawnPoints[spawnIndex];
	} while (std::find(activeSniperLocations.begin(), activeSniperLocations.end(), spawnPoint) != activeSniperLocations.end());

	std::cout << "code extis out of spawnsniper while loop with spawn point; " << spawnPoint << std::endl;
	Sniper* sniper = new Sniper(spawnPoint, *this);
	activeSniperLocations.push_back(spawnPoint);
	world->AddEntity(sniper);

}

void EntitySpawner::SpawnBullet(Bullet* bullet) {
	std::cout << "spawn bullet gets called" << std::endl;

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
