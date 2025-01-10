#include "Sniper.h"

Sniper::Sniper(const vec2& sniperPosition, EntitySpawner& spawner, float velocity, int health) {
	this->sniperPosition.x = sniperPosition.x;
	this->sniperPosition.y = sniperPosition.y;
	mCollider.x = sniperPosition.x + 20;
	mCollider.y = sniperPosition.y + 20;
	mCollider.w = 50;
	mCollider.h = 50;
	sniperHealth = health;
	sniperSpeed = velocity;
	this->spawner = &spawner;
	this->startOffset = 0;	//Remove this
	lastHit = 0;
}

Sniper::Sniper(const Sniper& other) : sniperPosition(other.sniperPosition), sniperHealth(other.sniperHealth), mCollider(other.mCollider), startOffset(other.startOffset), spawner(other.spawner), lastHit(other.lastHit) {
}

Sniper& Sniper::operator=(const Sniper& other) {
	if (this != &other) {
		sniperPosition = other.sniperPosition;
		sniperHealth = other.sniperHealth;
		mCollider = other.mCollider;
		startOffset = other.startOffset;
		spawner = other.spawner;
		lastHit = other.lastHit;
	}
	return *this;
}

void Sniper::Update(UpdateContext& context, double timestep) {
	if (HelperFunctions::EntityInFrame(context.camera->cameraRect, sniperPosition, 100)) {
		if (CooldownCompleted()) {
			Fire(context.player->GetCoordinates());
		}
	}
	else {
		LOS_Move(context.player, context.tiles);
	}
}

void Sniper::Render(UpdateContext& context) {
	vec2 directionVector = context.player->GetCoordinates() - sniperPosition;
	double rotationAngle = ClockwiseAngle(vec2::right(), directionVector);
	sniperTexture.Render(sniperPosition.x - context.camera->GetCameraCoords().x, sniperPosition.y - context.camera->GetCameraCoords().y, NULL, rotationAngle);
}

void Sniper::Fire(const vec2& playerCoords) {
	//Mix_PlayChannel(-1, gSniperFireSFX, 0);
	Bullet* bullet = new Bullet(GetCenter().x, GetCenter().y, SNIPER, playerCoords.x, playerCoords.y);
	spawner->SpawnBullet(bullet);
}

void Sniper::TakeDamage(int damage) {
	sniperHealth -= damage;
}

bool Sniper::CooldownCompleted() {
	if (SDL_GetTicks() > lastHit + SNIPER_ROF * 1000) {
		lastHit = SDL_GetTicks();
		return true;
	}
	return false;
}

bool Sniper::IsDead() {
	if (sniperHealth <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void Sniper::LOS_Move(Player* player, const std::vector<Tile*>& tiles) {
	if (HelperFunctions::RayCaster(GetCenter(), player->GetCoordinates(), tiles)) {
		vec2 directionVector = direction(sniperPosition, player->GetCoordinates());
		sniperPosition = sniperPosition + directionVector * sniperSpeed;
		mCollider.x = sniperPosition.x + 20;
		mCollider.y = sniperPosition.y + 20;
		/* DONT NEED THIS IF WALLS ARE NOT PRESENT 
		if (HitsWall(tiles)) {
			zombiePosition = zombiePosition - directionVector;
			mMainCollider.x = zombiePosition.x + 20;
			mMainCollider.y = zombiePosition.y + 20;
		}
		*/
		
	}
	/*
	if (currentPath.empty()) {
		return;
	}
	
	if (zombiePosition == currentPath[0]->GetCenter()) {
		currentPath.erase(currentPath.begin());
	}
	if (currentPath.empty()) {
		return;
	}
	*/
}

void Sniper::OnCollide(Entity& entity) {
	if (Bullet* bullet = dynamic_cast<Bullet*>(&entity)) {
		OnCollide(*bullet);
	}
	else {
		return;
	}
}

void Sniper::OnCollide(Bullet& bullet) {
	if (bullet.shooter == PLAYER) {
		TakeDamage(bullet.PLAYER_BULLET_DAMAGE);		//player bullet damage
	}
}

void Sniper::OnCollide(Player& player) {

}

void Sniper::OnCollide(Zombie& zombie) {

}

SDL_Rect Sniper::GetCollider() {
	return mCollider;
}

Coordinate Sniper::GetCenter() {
	return Coordinate(mCollider.x + (mCollider.w / 2), mCollider.y + (mCollider.h / 2));
}

Coordinate Sniper::GetCoordinates() {
	return sniperPosition;
}