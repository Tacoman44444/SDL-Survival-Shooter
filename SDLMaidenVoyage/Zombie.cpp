#include "Zombie.h"

Zombie::Zombie(vec2 initialPosition) {	//change to vec2&
	zombiePosition.x = initialPosition.x;
	zombiePosition.y = initialPosition.y;
	health = ZOMBIE_HEALTH;
	mMainCollider.x = zombiePosition.x;
	mMainCollider.y = zombiePosition.y;
	mMainCollider.w = ZOMBIE_WIDTH - 20;
	mMainCollider.h = ZOMBIE_HEIGHT - 10;

	mWallCollider.x = zombiePosition.x;
	mWallCollider.y = zombiePosition.y + 30;
	mWallCollider.w = ZOMBIE_WIDTH - 20;
	mWallCollider.h = ZOMBIE_HEIGHT - 40;

	lastHit = SDL_GetTicks();
}

void Zombie::TakeDamage(int damage) {
	health -= damage;
}

void Zombie::Move(const Coordinate& playerCoordinates, Tile* tiles[]) {		//using a simple LOS based function for now, will update to a more comprehensive BFS based algorithm later.
	vec2 directionVector = playerCoordinates - zombiePosition;
	vec2 incrementVector = directionVector.MakeUnitVector();	//change MakeUnitVector() to a helper function later...
	/*
	vec2 startVector = zombiePosition;
	while (startVector != playerCoordinates) {
		Coordinate gridPos = HelperFunctions::GetNodePointFromWorld(startVector);
		int gridIndex = (gridPos.y * GRIDSIZE_Y) + gridPos.x;
		if (tiles[gridIndex]->getType() == TileData::TILE_CENTER) {
			return;
		}
		startVector = startVector + incrementVector;
	}
	*/
	zombiePosition = zombiePosition + incrementVector * 2;
	mMainCollider.x = zombiePosition.x;
	mMainCollider.y = zombiePosition.y;
	mWallCollider.x = zombiePosition.x;
	mWallCollider.y = zombiePosition.y;
	if (TouchesWall(mWallCollider, tiles)) {
		zombiePosition = zombiePosition - incrementVector * 2;
		mMainCollider.x = zombiePosition.x;
		mMainCollider.y = zombiePosition.y;
		mWallCollider.x = zombiePosition.x;
		mWallCollider.y = zombiePosition.y;
	}
}

void Zombie::Render(const vec2& cameraCoords) {
	ZombieTexture.Render(zombiePosition.x - cameraCoords.x, zombiePosition.y - cameraCoords.y);
}

bool Zombie::IsDead() {
	if (health <= 0) {
		return true;
	}
	else {
		return false;
	}
}

Coordinate Zombie::GetCoordinates() {
	return zombiePosition;
}

SDL_Rect Zombie::GetMainCollider() {
	return mMainCollider;
}

SDL_Rect Zombie::GetWallCollider() {
	return mWallCollider;
}

void SpawnZombie(std::vector<Zombie>& zombieList) {
	if (zombieList.size() < 10) {
		int spawn_point = HelperFunctions::RandomZombieSpawn();
		Zombie newZombie = Zombie(zombieSpawnPoints[spawn_point]);
		zombieList.push_back(newZombie);
		std::cout << "Zombie spawned!\n";
	}
	
}

void RenderZombies(std::vector<Zombie>& zombieList, const Coordinate& cameraCoords, const SDL_Rect& cameraRect, const Coordinate& playerCoordinates, Tile* tiles[], Player& player) {	//clean up the code by passing in only a reference to the camera class, not corrds and rect seperately
	for (auto it = zombieList.begin(); it != zombieList.end();) {
		if (it->IsDead()) {
			it = zombieList.erase(it);
		}
		else {
			if (HelperFunctions::CheckCollision(player.GetCollider(), it->GetMainCollider()) && ZombieDamage(*it)) {
				player.TakeDamage(10);
				player.DisplayHealth();
			}
			it->Render(cameraCoords);
			if (HelperFunctions::EntityInFrame(cameraRect, it->GetCoordinates() + Coordinate(Zombie::ZOMBIE_WIDTH / 2, Zombie::ZOMBIE_HEIGHT / 2))) {
				it->Move(playerCoordinates, tiles);
			}
			++it;
		}
	}
}

bool CheckCollisionWithZombies(std::vector<Zombie>& zombieList, const SDL_Rect& collider) {
	bool damageTaken = false;
	for (int i = 0; i < zombieList.size(); i++) {
		if (HelperFunctions::CheckCollision(zombieList[i].GetMainCollider(), collider)) {
			zombieList[i].TakeDamage(10);
			damageTaken = true;
		}
	}
	return damageTaken;
}

bool ZombieDamage(Zombie& zombie) {
	Uint32 hitTime = SDL_GetTicks();
	if (zombie.lastHit + 2000 < hitTime) {
		std::cout << "zombie.lastHit: " << static_cast<int>(zombie.lastHit) << "\n";
		std::cout << "hitTime: " << static_cast<int>(hitTime) << "\n";
		zombie.lastHit = hitTime;
		return true;
	}
	else {
		return false;
	}
	
}