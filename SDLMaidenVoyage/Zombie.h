#pragma once

#include <SDL.h>
#include "vec2.h"
#include "HelperFunctions.h"
#include "TileData.h"

//TEMPORARY DEFINITION OF PLAYER UNTIL I REFACTOR THE CODE ...

class Player {

public:
	const int PLAYER_WIDTH = 50;
	const int PLAYER_HEIGHT = 50;
	const int PLAYER_VELOCITY = 640; //640 pixels travelled per second
	const double RATE_OF_FIRE = 0.2;

	Player();
	void HandleEvent(SDL_Event& e, const vec2& cameraCoords);
	void Move(Tile* tiles[], double timestep);
	void Fire();
	void Render(int camX, int camY);
	void TakeDamage(int damage);
	void DisplayHealth();
	int GetHealth();
	vec2 GetCoordinates() const;
	SDL_Rect GetCollider();
	const SDL_Rect& GetColliderRef();

private:
	double PosX, PosY;
	double VelX, VelY;
	int health;
	Uint32 startTime;
	PlayerSprites rotation;
	vec2 rotationVector = vec2(0, -1);
	bool rotated = false;
	bool fired = false;
	SDL_Rect mCollider;
};

//------------------------------------------------------------

class Zombie {
public:

	static const int ZOMBIE_WIDTH = 50;
	static const int ZOMBIE_HEIGHT = 70;
	static const int ZOMBIE_HEALTH = 70;

	Zombie(vec2 initialPosition); //change to vec2& after debugging
	void TakeDamage(int damage);
	void Move(const Coordinate& playerCoordinates, Tile* tiles[]);
	void Render(const vec2& cameraCoords);
	bool IsDead();

	Coordinate GetCoordinates();
	SDL_Rect GetMainCollider();
	SDL_Rect GetWallCollider();
	Uint32 lastHit;

private:
	vec2 zombiePosition;
	int health;
	SDL_Rect mMainCollider;
	SDL_Rect mWallCollider;
};

void SpawnZombie(std::vector<Zombie>& zombieList);

void RenderZombies(std::vector<Zombie>& zombieList, const Coordinate& cameraCoords, const SDL_Rect& cameraRect, const Coordinate& playerCoordinates, Tile* tiles[], Player& player);

bool CheckCollisionWithZombies(std::vector<Zombie>& zombieList, const SDL_Rect& collider);

bool ZombieDamage(Zombie& zombie);