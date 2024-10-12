#include "Zombie.h"

Zombie::Zombie(vec2 initialPosition) {	//change to vec2&
	zombiePosition.x = initialPosition.x;
	zombiePosition.y = initialPosition.y;
	health = ZOMBIE_HEALTH;
	mMainCollider.x = zombiePosition.x + 20;
	mMainCollider.y = zombiePosition.y + 20;
	mMainCollider.w = ZOMBIE_WIDTH;
	mMainCollider.h = ZOMBIE_HEIGHT;

	lastHit = SDL_GetTicks();
}

void Zombie::Update( UpdateContext& context, double timestep) {
	if (HelperFunctions::EntityInFrame(context.camera->cameraRect, zombiePosition)) {
		LOS_Move(context.player, context.tiles);
	}
	
}

void Zombie::Render(UpdateContext& context) {
	vec2 cameraCoords = context.camera->GetCameraCoords();
	vec2 direction = context.player->GetCoordinates() - zombiePosition;
	double rotationAngle = ClockwiseAngle(vec2::right(), direction);
	ZombieTexture.Render(zombiePosition.x - cameraCoords.x, zombiePosition.y - cameraCoords.y, NULL, rotationAngle);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect Box = { mMainCollider.x - cameraCoords.x, mMainCollider.y - cameraCoords.y, mMainCollider.w, mMainCollider.h };
	SDL_RenderDrawRect(gRenderer, &Box);
}

bool Zombie::IsDead() {
	if (health <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void Zombie::TakeDamage(int damage) {
	health -= damage;
}

/*
void Zombie::Move(const Coordinate& playerCoordinates, std::vector<Tile*>& tiles) {		//using a simple LOS based function for now, will update to a more comprehensive BFS based algorithm later.
	vec2 directionVector = playerCoordinates - zombiePosition;
	vec2 incrementVector = directionVector.MakeUnitVector();	//change MakeUnitVector() to a helper function later...

	zombiePosition = zombiePosition + incrementVector * 2;
	mMainCollider.x = zombiePosition.x;
	mMainCollider.y = zombiePosition.y;
	if (TouchesWall(mMainCollider, tiles)) {
		zombiePosition = zombiePosition - incrementVector * 2;
		mMainCollider.x = zombiePosition.x;
		mMainCollider.y = zombiePosition.y;
	}
}
*/

void Zombie::LOS_Move(Player* player, const std::vector<Tile*>& tiles) {
	if (HelperFunctions::RayCaster(GetCenter(), player->GetCoordinates(), tiles)) {
		vec2 directionVector = direction(zombiePosition, player->GetCoordinates());
		zombiePosition = zombiePosition + directionVector;
		mMainCollider.x = zombiePosition.x + 20;
		mMainCollider.y = zombiePosition.y + 20;
		if (HitsWall(tiles)) {
			zombiePosition = zombiePosition - directionVector;
			mMainCollider.x = zombiePosition.x + 20;
			mMainCollider.y = zombiePosition.y + 20;
		}
	}
	if (currentPath.empty()) {
		return;
	}
	if (zombiePosition == currentPath[0]->GetCenter()) {
		currentPath.erase(currentPath.begin());
	}
	if (currentPath.empty()) {
		return;
	}
	
	//zombiePosition = currentPath[0]->GetCenter();
}

void Zombie::UpdatePath(const Coordinate& playerCoordinates, std::vector<Tile*>& tiles) {
	vec2 startVector = zombiePosition;
	std::vector<const Tile*> path = HelperFunctions::BreadthFirstSearch(startVector, playerCoordinates, tiles);
	for (const Tile* tile : path) {
		std::cout << tile->GetCenter() << std::endl;
	}
	currentPath = path;
}

bool Zombie::HitsWall(const std::vector<Tile*>& tiles) {

	Coordinate zombieCoordsOnGrid = HelperFunctions::GetNodePointFromWorld(Coordinate(zombiePosition.x, zombiePosition.y));

	Tile* currentTile = tiles[zombieCoordsOnGrid.y * TileData::TOTAL_TILES_ROW + zombieCoordsOnGrid.x];

	std::vector<const Tile*> neighboringTiles = HelperFunctions::GetNeighborsEIGHT(currentTile, tiles);

	for(const Tile* tile : neighboringTiles) {
		if (tile->getType() >= 3) {
			if (HelperFunctions::CheckCollision(tile->getBox(), mMainCollider)) {
				return true;
			}
		}
	}
	return false;
	/*
	if (tiles[zombieCoordsOnGrid.y * TileData::TOTAL_TILES_ROW + zombieCoordsOnGrid.x]->getType() >= 3) {
		return true;
	}
	return false;
	*/
	
}


void Zombie::OnCollide(Entity& entity) {
	if (Bullet* bullet = dynamic_cast<Bullet*>(&entity)) {
		OnCollide(*bullet);
	}
}

void Zombie::OnCollide(Bullet& bullet) {
	if (bullet.shooter == PLAYER) {
		TakeDamage(10);	//player bullet damage value
	}
}

void Zombie::OnCollide(Player& player) {

}

void Zombie::OnCollide(Sniper& sniper) {

}

bool Zombie::CooldownCompleted() {
	Uint32 hitTime = SDL_GetTicks();
	if (lastHit + 2000 < hitTime) {
		lastHit = hitTime;
		return true;
	}
	else {
		return false;
	}
}

Coordinate Zombie::GetCoordinates() {
	return zombiePosition;
}

Coordinate Zombie::GetCenter() {
	return Coordinate(mMainCollider.x + (mMainCollider.w / 2), mMainCollider.y + (mMainCollider.h / 2));
}

SDL_Rect Zombie::GetCollider() {
	return mMainCollider;
}

SDL_Rect Zombie::GetMainCollider() {
	return mMainCollider;
}

