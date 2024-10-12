#include "Player.h"

Player::Player() {
	PosX = LEVEL_WIDTH / 2 - 40;
	PosY = LEVEL_HEIGHT / 2;
	VelX = 0;
	VelY = 0;
	mCollider.h = 40;
	mCollider.w = 40;
	mCollider.x = PosX + 10;
	mCollider.y = PosY + 10;
	health = PLAYER_HEALTH;
	fireThisFrame = false;
	startTime = SDL_GetTicks();
	spawner = nullptr; //this might cause issues of you dont call Player::SetSpawner()
}

void Player::SetSpawner(EntitySpawner& spawner) {
	this->spawner = &spawner;
}

void Player::HandleEvent(SDL_Event& e, const vec2& cameraCoords) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_w:
			VelY -= PLAYER_VELOCITY;
			break;

		case SDLK_a:
			VelX -= PLAYER_VELOCITY;
			break;

		case SDLK_s:
			VelY += PLAYER_VELOCITY;
			break;

		case SDLK_d:
			VelX += PLAYER_VELOCITY;
			break;
		}
	}

	if (e.type == SDL_MOUSEMOTION) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		rotationVector.x = x + cameraCoords.x;
		rotationVector.y = y + cameraCoords.y;
		rotationVector.MakeUnitVector();
	}

	if (e.type == SDL_MOUSEBUTTONDOWN) {
		if ( SDL_GetTicks() > startTime + (RATE_OF_FIRE * 1000)) {
			fireThisFrame = true;
		}
	}

	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_w:
			VelY += PLAYER_VELOCITY;
			break;

		case SDLK_a:
			VelX += PLAYER_VELOCITY;
			break;

		case SDLK_s:
			VelY -= PLAYER_VELOCITY;
			break;

		case SDLK_d:
			VelX -= PLAYER_VELOCITY;
			break;
		}

	}
}

void Player::Update(UpdateContext& context, double timestep) {
	Move(context.tiles, timestep);
	if (fireThisFrame) {
		Fire();
		startTime = SDL_GetTicks();
		fireThisFrame = false;
	}
}

void Player::Move(std::vector<Tile*> tiles, double timestep) {
	PosX += VelX;
	mCollider.x = PosX + 10;
	if (PosX < 0) {
		PosX = 0;
		mCollider.x = PosX + 10;
	}
	else if (PosX + PLAYER_WIDTH > LEVEL_WIDTH) {
		PosX = LEVEL_WIDTH - PLAYER_WIDTH;
		mCollider.x = PosX + 10;
	}


	PosY += VelY;
	mCollider.y = PosY + 10;
	if (PosY < 0) {
		PosY = 0;
		mCollider.y = PosY + 10;
	}
	else if (PosY + PLAYER_HEIGHT > LEVEL_HEIGHT) {
		PosY = LEVEL_HEIGHT - PLAYER_HEIGHT;
		mCollider.y = PosY +10;
	}

	if (TouchesWall(mCollider, tiles)) {
		PosX -= VelX;
		PosY -= VelY;
		mCollider.x = PosX;
		mCollider.y = PosY;
	}
}

void Player::Fire() {
	Mix_PlayChannel(-1, gPlayerFireSFX, 0);
	Bullet* bullet = new Bullet(GetCenter().x, GetCenter().y, PLAYER, rotationVector.x, rotationVector.y);
	spawner->SpawnBullet(bullet);
}

void Player::Render(UpdateContext& context) {
	double rotationAngle = ClockwiseAngle(vec2::right(), rotationVector - Coordinate(PosX, PosY));
	playerTexture.Render(PosX - context.camera->GetCameraCoords().x, PosY - context.camera->GetCameraCoords().y, NULL, rotationAngle);
}

void Player::TakeDamage(int damage) {
	health -= damage;
	gPlayerHealthTexture.LoadFromRenderedText("Health: " + std::to_string(health), SDL_Color{ 180, 0, 0 });
}

void Player::DisplayHealth() {
	gPlayerHealthTexture.Render(SCREEN_WIDTH - gPlayerHealthTexture.GetWidth(), 0);
}

int Player::GetHealth() {
	return health;
}

void Player::ResetHealth() {
	health = PLAYER_HEALTH;
}

vec2 Player::GetCoordinates() const {
	float fPosX = float(PosX);
	float fPosY = float(PosY);
	return vec2(fPosX, fPosY);
}

SDL_Rect Player::GetCollider() {
	return mCollider;
}

const SDL_Rect& Player::GetColliderRef() {
	return mCollider;
}

Coordinate Player::GetCenter() {
	return Coordinate(mCollider.x + (mCollider.w / 2), mCollider.y + (mCollider.h / 2));
}

void Player::OnCollide(Entity& entity) {

	if (Bullet* bullet = dynamic_cast<Bullet*>(&entity)) {
		OnCollide(*bullet);
	}
	else if (Zombie* zombie = dynamic_cast<Zombie*>(&entity)) {
		OnCollide(*zombie);
	}
	else if (Sniper* sniper = dynamic_cast<Sniper*>(&entity)) {
		OnCollide(*sniper);
	}

}

void Player::OnCollide(Bullet& bullet) {
	if (bullet.shooter == SNIPER) {
		TakeDamage(10);		//sniper
	}
}

void Player::OnCollide(Sniper& sniper) {
	
}

void Player::OnCollide(Zombie& zombie) {
	if (zombie.CooldownCompleted()) {
		TakeDamage(Zombie::ZOMBIE_DAMAGE);
	}
}

bool Player::IsDead() {
	if (health <= 0) {
		return true;
	}
	return false;
}