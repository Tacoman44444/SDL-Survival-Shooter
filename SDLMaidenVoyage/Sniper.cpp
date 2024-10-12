#include "Sniper.h"

Sniper::Sniper(const vec2& sniperPosition, EntitySpawner& spawner) {
	this->sniperPosition.x = sniperPosition.x;
	this->sniperPosition.y = sniperPosition.y;
	mCollider.x = sniperPosition.x + 20;
	mCollider.y = sniperPosition.y + 20;
	mCollider.w = 30;
	mCollider.h = 30;
	health = 50;
	this->spawner = &spawner;
	this->startOffset = 0;	//Remove this
	lastHit = 0;
}

Sniper::Sniper(const Sniper& other) : sniperPosition(other.sniperPosition), health(other.health), mCollider(other.mCollider), startOffset(other.startOffset), spawner(other.spawner), lastHit(other.lastHit) {
}

Sniper& Sniper::operator=(const Sniper& other) {
	if (this != &other) {
		sniperPosition = other.sniperPosition;
		health = other.health;
		mCollider = other.mCollider;
		startOffset = other.startOffset;
		spawner = other.spawner;
		lastHit = other.lastHit;
	}
	return *this;
}

void Sniper::Update(UpdateContext& context, double timestep) {
	if (CooldownCompleted()) {
		Fire(context.player->GetCoordinates());
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
	health -= damage;
}

bool Sniper::CooldownCompleted() {
	if (SDL_GetTicks() > lastHit + SNIPER_ROF * 1000) {
		lastHit = SDL_GetTicks();
		return true;
	}
	return false;
}

bool Sniper::IsDead() {
	if (health <= 0) {
		return true;
	}
	else {
		return false;
	}
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
		TakeDamage(10);		//player bullet damage
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