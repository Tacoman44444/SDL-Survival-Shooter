#include "Sniper.h"

Sniper::Sniper(const vec2& sniperPosition, EntitySpawner& spawner) {
	sniperLoc.x = sniperPosition.x;
	sniperLoc.y = sniperPosition.y;
	this->sniperPosition.x = sniperPosition.x - SNIPER_WIDTH / 2;
	this->sniperPosition.y = sniperPosition.y - SNIPER_HEIGHT / 2;
	mCollider.x = sniperPosition.x - SNIPER_WIDTH / 2;
	mCollider.y = sniperPosition.y - SNIPER_HEIGHT / 2;
	mCollider.w = SNIPER_WIDTH;
	mCollider.h = SNIPER_HEIGHT;
	health = 50;
	this->spawner = &spawner;
	this->startOffset = 0;	//Remove this
	lastHit = 0;
}

Sniper::Sniper(const Sniper& other) : sniperLoc(other.sniperLoc), sniperPosition(other.sniperPosition), health(other.health), mCollider(other.mCollider), startOffset(other.startOffset), spawner(other.spawner), lastHit(other.lastHit) {
}

Sniper& Sniper::operator=(const Sniper& other) {
	if (this != &other) {
		sniperLoc = other.sniperLoc;
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
	Bullet* bullet = new Bullet(sniperPosition.x, sniperPosition.y, SNIPER, playerCoords.x, playerCoords.y);
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
		score++;
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

Coordinate Sniper::GetCoordinates() {
	return sniperPosition;
}