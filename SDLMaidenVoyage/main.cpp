#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cmath> 
#include <vector>
#include "vec2.h"
#include "LTexture.h"
#include "Tile.h"
#include "GameData.h"
#include "SetupHelper.h"
#include "HelperFunctions.h"
#include "Timer.h"
#include "Zombie.h"
#include "LButton.h"

class Player;
class Bullet;
class Sniper;
class Camera;

void SniperRenderFire(const vec2& playerCoords, const Camera& camera);
void RenderSnipers(const vec2& previousPlayerCoords, const Camera& camera);
bool CheckCollisionWithSnipers(const SDL_Rect& collider);
void BulletFire(const Bullet& bullet);
void BulletMove(Player& player, const Camera& camera, Tile* tiles[]);
int GenerateSniperSpawn();
int CheckDeadSniperLoc(const Coordinate& deadSniperLoc);
Sniper ReplaceSniper(int new_loc, int old_loc);
void UpdateHighScore();

std::vector<Bullet> bulletList;
std::vector<Sniper> sniperList;
std::vector<Zombie> zombieList;

class Camera {

public:
	Camera();
	void Adjust(const vec2& playerCoords);
	Coordinate GetCameraCoords();
	SDL_Rect cameraRect;	//should be private
};

class Bullet {

public:

	Bullet(double PosX, double PosY, Shooter shooter, double TargetX, double TargetY);

	static const int PLAYER_FIRE_VELOCITY = 17;
	static const int SNIPER_FIRE_VELOCITY = 12;
	static const int BULLET_DAMAGE = 15;

	void Render(const vec2& cameraCoords);
	int GetPosX();
	int GetPosY();
	int	GetDirX();
	int GetDirY();
	vec2 GetDirection();
	void UpdateColliderPosition();
	SDL_Rect GetCollider();
	double PosX, PosY;
	double DirX, DirY;
	vec2 bulletDirection = vec2(0, 0);
	Shooter shooter;

private:
	SDL_Rect mCollider;
	LTexture* bulletTexture;
};

class Sniper {

public:

	static const int ACTIVE_SNIPER_COUNT = 3;
	static int ActiveSniperLocations[];

	const int SNIPER_WIDTH = 73;
	const int SNIPER_HEIGHT = 51;

	const int SNIPER_ROF = 3;

	Sniper(const vec2& sniperPosition, int startOffset);
	Sniper(const Sniper& other);
	Sniper& operator=(const Sniper& other);

	void Fire(const vec2& playerCoords);
	void Render(const vec2& playerCoords, const vec2& cameraCoords);
	void TakeDamage(int damage);
	bool IsDead();
	SDL_Rect GetCollider();
	vec2 sniperLoc;

private:
	vec2 sniperPosition;
	int health;
	SDL_Rect mCollider;
	int startOffset;
};

int Sniper::ActiveSniperLocations[Sniper::ACTIVE_SNIPER_COUNT] = { -1, -1, -1 };	//since these are invalid locations, they'll be overridden. 

void SniperRenderFire(const vec2& playerCoords, const Camera& camera) {
	for (auto it = sniperList.begin(); it != sniperList.end();) {
		vec2 cameraCoords = vec2(camera.cameraRect.x, camera.cameraRect.y);
		it->Render(playerCoords, cameraCoords);
		it->Fire(playerCoords);
		++it;
	}
}



void RenderSnipers(const vec2& previousPlayerCoords, const Camera& camera) {
	std::vector<Sniper> newSnipers;
	for (auto it = sniperList.begin(); it != sniperList.end();) {
		if (it->IsDead()) {
			UpdateHighScore();
			int new_spawn = GenerateSniperSpawn();
			std::cout << "output from GenerateSniperSpawn(): " << new_spawn << "\n";
			//std::cout << "value that is going into CheckDeadSniperLoc: " << it->sniperLoc.x << "," << it->sniperLoc.y << "\n";
			int dead_sniper_loc = CheckDeadSniperLoc(it->sniperLoc);
			it = sniperList.erase(it);
			newSnipers.push_back(ReplaceSniper(new_spawn, dead_sniper_loc));

		}
		else {
			vec2 cameraCoords = vec2(camera.cameraRect.x, camera.cameraRect.y);
			it->Render(previousPlayerCoords, cameraCoords);
			++it;
		}
	}
	sniperList.insert(sniperList.end(), newSnipers.begin(), newSnipers.end());
}

bool CheckCollisionWithSnipers(const SDL_Rect& collider) {
	for (auto it = sniperList.begin(); it != sniperList.end(); ++it) {
		if (HelperFunctions::CheckCollision(it->GetCollider(), collider)) {
			it->TakeDamage(Bullet::BULLET_DAMAGE);
			return true;
		}
	}
	return false;
}



void BulletMove(Player& player, const Camera& camera, Tile* tiles[]) {

	//Make te bullets move
	vec2 cameraCoords = vec2(camera.cameraRect.x, camera.cameraRect.y);
	for (auto it = bulletList.begin(); it != bulletList.end();) {

		if (it->GetPosX() > LEVEL_WIDTH || it->GetPosX() < 0 || it->GetPosY() > LEVEL_HEIGHT || it->GetPosY() < 0) {
			it = bulletList.erase(it);
		}
		else if (TouchesWall(it->GetCollider(), tiles)) {
			it = bulletList.erase(it);
		}
		else if (HelperFunctions::CheckCollision(player.GetCollider(), it->GetCollider()) && it->shooter == Shooter::SNIPER) {
			it = bulletList.erase(it);
			player.TakeDamage(Bullet::BULLET_DAMAGE);
		}


		else if (it->shooter == Shooter::PLAYER) {
			if (CheckCollisionWithSnipers(it->GetCollider())) {
				it = bulletList.erase(it);
			}
			else if (CheckCollisionWithZombies(zombieList, it->GetCollider())) {
				it = bulletList.erase(it);
			}
			else {
				it->PosX += it->GetDirection().x * Bullet::PLAYER_FIRE_VELOCITY;
				it->PosY += it->GetDirection().y * Bullet::PLAYER_FIRE_VELOCITY;
				it->UpdateColliderPosition();
				it->Render(cameraCoords);
				++it;
			}
		}

		else {
			it->PosX += it->GetDirection().x * Bullet::SNIPER_FIRE_VELOCITY;
			it->PosY += it->GetDirection().y * Bullet::SNIPER_FIRE_VELOCITY;
			it->UpdateColliderPosition();

			it->Render(cameraCoords);
			++it;
		}

	}
}

void BulletFire(const Bullet& bullet) {
	bulletList.push_back(bullet);
}

int GenerateSniperSpawn() {
	while (true) {
		int random_number = HelperFunctions::RandomSniperSpawn();
		bool repeated = false;
		for (int i = 0; i < Sniper::ACTIVE_SNIPER_COUNT; ++i) {
			if (random_number == Sniper::ActiveSniperLocations[i]) {
				repeated = true;
				break;
			}
		}
		if (!repeated) {
			return random_number;
		}
	}
}

int CheckDeadSniperLoc(const Coordinate& deadSniperLoc) {
	//std::cout << deadSniperLoc.x << ", " << deadSniperLoc.y;
	for (int i = 0; i < TOTAL_SNIPER_SPAWNS; ++i) {
		if (deadSniperLoc == sniperSpawnPoints[i]) {
			std::cout << "output from CheckDeadSniperLoc: " << i << "\n";
			return i;
		}
	}
	std::cout << "CheckDeadSniperLoc() did not work\n";
	return -1;	//did not work
}

Sniper ReplaceSniper(int new_loc, int old_loc) {
	for (int i = 0; i < Sniper::ACTIVE_SNIPER_COUNT; ++i) {
		if (Sniper::ActiveSniperLocations[i] == old_loc) {
			Sniper::ActiveSniperLocations[i] = new_loc;
			Sniper sniper = Sniper(sniperSpawnPoints[new_loc], 1);
			return sniper;
		}
	}
	std::cout << "ReplaceSniper did not work\n";
}

void UpdateHighScore() {
	score += 1;
	if (!gHighScoreTexture.LoadFromRenderedText("Score: " + std::to_string(score), SDL_Color{128, 128, 128})) {
		std::cout << "could not loadfromrenderedtext high score";
	}
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
		if (!fired && SDL_GetTicks() > startTime + (RATE_OF_FIRE * 1000)) {
			Fire();
			startTime = SDL_GetTicks();
		}
		fired = true;
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

	if (e.type == SDL_MOUSEBUTTONUP) {
		fired = false;
	}
}

Player::Player() {
	PosX = LEVEL_WIDTH / 2 - 40;
	PosY = LEVEL_HEIGHT / 2;
	VelX = 0;
	VelY = 0;
	mCollider.h = PLAYER_HEIGHT - 10;
	mCollider.w = PLAYER_WIDTH - 10;
	mCollider.x = PosX - 10;
	mCollider.y = PosY - 10;
	health = 100;
	startTime = SDL_GetTicks();
}

void Player::Move(Tile* tiles[], double timestep) {
	PosX += VelX * timestep;
	mCollider.x = PosX;
	if (PosX < 0) {
		PosX = 0;
		mCollider.x = PosX;
	}
	else if (PosX + PLAYER_WIDTH > LEVEL_WIDTH) {
		PosX = LEVEL_WIDTH - PLAYER_WIDTH;
		mCollider.x = PosX;
	}


	PosY += VelY * timestep;
	mCollider.y = PosY;
	if (PosY < 0) {
		PosY = 0;
		mCollider.y = PosY;
	}
	else if (PosY + PLAYER_HEIGHT > LEVEL_HEIGHT) {
		PosY = LEVEL_HEIGHT - PLAYER_HEIGHT;
		mCollider.y = PosY;
	}

	if (TouchesWall(mCollider, tiles)) {
		PosX -= VelX * timestep;
		PosY -= VelY * timestep;
		mCollider.x = PosX;
		mCollider.y = PosY;
	}
}

void Player::Fire() {
	Mix_PlayChannel(-1, gPlayerFireSFX, 0);
	Bullet bullet(double(PosX + PLAYER_WIDTH / 4), double(PosY + PLAYER_HEIGHT / 4), PLAYER, rotationVector.x, rotationVector.y);
	BulletFire(bullet);
}

void Player::Render(int CamX, int CamY) {
	playerTexture.Render(PosX - CamX, PosY - CamY);
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

Bullet::Bullet(double PosX, double PosY, Shooter shooter, double TargetX, double TargetY) {
	this->PosX = PosX;
	this->PosY = PosY;
	this->DirX = TargetX;
	this->DirY = TargetY;
	this->shooter = shooter;
	bulletDirection = direction(vec2(PosX, PosY), vec2(TargetX, TargetY));
	if (shooter == SNIPER) {
		bulletTexture = &sniperBulletTexture;
	}
	else if (shooter == PLAYER) {
		bulletTexture = &playerBulletTexture;
	}
	else {
		bulletTexture = NULL;
	}
	mCollider.x = PosX;
	mCollider.y = PosY;
	mCollider.w = 25;
	mCollider.h = 25;
}

int Bullet::GetPosX() {
	return PosX;
}

int Bullet::GetPosY() {
	return PosY;
}

int Bullet::GetDirX() {
	return DirX;
}

int Bullet::GetDirY() {
	return DirY;
}

vec2 Bullet::GetDirection() {
	return bulletDirection;
}

void Bullet::UpdateColliderPosition() {
	mCollider.x = PosX;
	mCollider.y = PosY;
}

SDL_Rect Bullet::GetCollider() {
	return mCollider;
}

void Bullet::Render(const vec2& cameraCoords) {
	SDL_Rect bulletClip;
	if (shooter == SNIPER) {
		bulletClip = { 620, 350, 90, 80 };
	}
	else if (shooter == PLAYER) {
		bulletClip = { 530, 388, 60, 25 };
	}
	bulletTexture->Render(PosX - cameraCoords.x, PosY - cameraCoords.y);
}

Sniper::Sniper(const vec2& sniperPosition, int startOffset) {
	sniperLoc.x = sniperPosition.x;
	sniperLoc.y = sniperPosition.y;
	this->sniperPosition.x = sniperPosition.x - SNIPER_WIDTH / 2;
	this->sniperPosition.y = sniperPosition.y - SNIPER_HEIGHT / 2;
	mCollider.x = sniperPosition.x - SNIPER_WIDTH / 2;
	mCollider.y = sniperPosition.y - SNIPER_HEIGHT / 2;
	mCollider.w = SNIPER_WIDTH;
	mCollider.h = SNIPER_HEIGHT;
	health = 50;
	this->startOffset = startOffset;
}

Sniper::Sniper(const Sniper& other) : sniperLoc(other.sniperLoc), sniperPosition(other.sniperPosition), health(other.health), mCollider(other.mCollider), startOffset(other.startOffset) {
}

Sniper& Sniper::operator=(const Sniper& other) {
	if (this != &other) {
		sniperLoc = other.sniperLoc;
		sniperPosition = other.sniperPosition;
		health = other.health;
		mCollider = other.mCollider;
		startOffset = other.startOffset;
	}
	return *this;
}

void Sniper::Fire(const vec2& playerCoords) {
	//Mix_PlayChannel(-1, gSniperFireSFX, 0);
	Bullet bullet(sniperPosition.x, sniperPosition.y, SNIPER, playerCoords.x, playerCoords.y);
	BulletFire(bullet);
}

void Sniper::Render(const vec2& playerCoords, const vec2& cameraCoords) {
	vec2 directionVector = playerCoords - sniperPosition;
	double rotationAngle = ClockwiseAngle(vec2::right(), directionVector);
	sniperTexture.Render(sniperPosition.x - cameraCoords.x, sniperPosition.y - cameraCoords.y, NULL, rotationAngle);
}

void Sniper::TakeDamage(int damage) {
	health -= damage;
}

bool Sniper::IsDead() {
	if (health <= 0) {
		return true;
	}
	else {
		return false;
	}
}

SDL_Rect Sniper::GetCollider() {
	return mCollider;
}

Camera::Camera() {
	cameraRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

void Camera::Adjust(const vec2& playerCoords) {
	//later, I should take into account the width and height of the player as well
	cameraRect.x = (playerCoords.x) - SCREEN_WIDTH / 2;
	cameraRect.y = (playerCoords.y) - SCREEN_HEIGHT / 2;

	if (cameraRect.x < 0) {
		cameraRect.x = 0;
	}
	if (cameraRect.y < 0) {
		cameraRect.y = 0;
	}
	if (cameraRect.x > LEVEL_WIDTH - cameraRect.w) {
		cameraRect.x = LEVEL_WIDTH - cameraRect.w;
	}
	if (cameraRect.y > LEVEL_HEIGHT - cameraRect.h) {
		cameraRect.y = LEVEL_HEIGHT - cameraRect.h;
	}
}

inline Coordinate Camera::GetCameraCoords() {
	return Coordinate(cameraRect.x, cameraRect.y);
}

int main(int argc, char* args[]) {
	if (!Init()) {
		std::cout << "failed to initialize\n";
	}
	else {
		Tile* tileSet[TileData::TOTAL_TILES];
		if (!LoadMedia(tileSet)) {
			std::cout << "failed to load media\n";
		}
		else {
			bool quit = false;
			bool started = false;
			SDL_Event e;
			LTimer stepTimer;
			LButton PressPlayButton{ gPressPlayTexture };
			PressPlayButton.SetDimensions(SCREEN_WIDTH / 2 - gPressPlayTexture.GetWidth() / 2, SCREEN_HEIGHT / 2 - gPressPlayTexture.GetHeight() / 2, gPressPlayTexture.GetWidth(), gPressPlayTexture.GetHeight());
			Player player;
			Sniper sniper1 = Sniper{ sniperSpawnPoints[1], 1};
			Sniper sniper2 = Sniper{ sniperSpawnPoints[2], 2};
			Sniper sniper3 = Sniper{ sniperSpawnPoints[5], 3};
			sniperList.push_back(sniper1);
			sniperList.push_back(sniper2);
			sniperList.push_back(sniper3);
			Sniper::ActiveSniperLocations[0] = 1;
			Sniper::ActiveSniperLocations[1] = 2;
			Sniper::ActiveSniperLocations[2] = 5;
			Uint32 startTime = 0;
			vec2 previousPlayerCoords = player.GetCoordinates();
			Camera camera;

			while (!quit) {

				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					if (started) {
						vec2 camCoords = vec2(camera.cameraRect.x, camera.cameraRect.y);
						player.HandleEvent(e, camCoords);
					}
					if (e.type == SDL_MOUSEBUTTONDOWN && started == false) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						if(PressPlayButton.CheckCollisionWithButton(Coordinate(x, y))) {
							started = true;
							Mix_PlayMusic(gMusic, -1);
							startTime = SDL_GetTicks();
						}
					}
				}

				if (started) {
					
					if (player.GetHealth() <= 0) {
						//Game over
						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);
						gGameOverBackgroundTexture.Render((SCREEN_WIDTH / 2) - gGameOverBackgroundTexture.GetWidth() / 2, (SCREEN_HEIGHT / 2) - gGameOverBackgroundTexture.GetHeight() - 50);
						gGameOverTextTexture.Render((SCREEN_WIDTH / 2) - gGameOverTextTexture.GetWidth() / 2, (SCREEN_HEIGHT / 2) - gGameOverTextTexture.GetHeight() / 2);
						gHighScoreTexture.Render((SCREEN_WIDTH / 2) - gHighScoreTexture.GetWidth() / 2, (SCREEN_HEIGHT / 2) + 20);
						SDL_RenderPresent(gRenderer);
					}
					else {
						float timeStep = stepTimer.getTicks() / 1000.f;
						player.Move(tileSet, timeStep);
						stepTimer.start();
						const vec2 playerCoords = player.GetCoordinates();
						camera.Adjust(playerCoords);
						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);
						for (int i = 0; i < TileData::TOTAL_TILES; ++i) {
							tileSet[i]->render(camera.cameraRect);
						}
						gHighScoreTexture.Render(0, 0);
						player.Render(camera.cameraRect.x, camera.cameraRect.y);
						BulletMove(player, camera, tileSet);
						if (SDL_GetTicks() > startTime + 3000) {
							SpawnZombie(zombieList);
							SniperRenderFire(player.GetCoordinates(), camera);
							previousPlayerCoords = player.GetCoordinates();
							startTime = SDL_GetTicks();
						}
						else {
							RenderSnipers(previousPlayerCoords, camera);
						}
						RenderZombies(zombieList, camera.GetCameraCoords(), camera.cameraRect,  playerCoords, tileSet, player);
						player.DisplayHealth();
						SDL_RenderPresent(gRenderer);
					}
				}
				else {
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
					SDL_RenderClear(gRenderer);
					gMainMenuTexture.Render(0, 0);
					PressPlayButton.Render();
					SDL_RenderPresent(gRenderer);
				}
				
			}
		}
	}
	Close();

	return 0;
}