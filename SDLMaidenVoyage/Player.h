#pragma once

#include "SDL.h"
#include "Entity.h"
#include "Tile.h"
#include "vec2.h"
#include "Bullet.h"
#include "UpdateContext.h"
#include "EntitySpawner.h"
#include <string>

struct UpdateContext;

class Zombie;

class Sniper;

class EntitySpawner;

class Player : public Entity {

public:
	const int PLAYER_WIDTH = 30;
	const int PLAYER_HEIGHT = 70;
	const int PLAYER_VELOCITY = 10; //640 pixels travelled per second
	const int PLAYER_HEALTH = 100;
	const double RATE_OF_FIRE = 0.2;

	Player();
	void SetSpawner(EntitySpawner& spawner);
	void HandleEvent(SDL_Event& e, const vec2& cameraCoords);
	void Update(UpdateContext& context, double timestep);
	void Move(std::vector<Tile*> tiles, double timestep);
	void Fire();
	void Render(UpdateContext& context);
	void TakeDamage(int damage);
	void DisplayHealth();
	int GetHealth();
	void ResetHealth();
	vec2 GetCoordinates() const;
	SDL_Rect GetCollider();
	const SDL_Rect& GetColliderRef();
	Coordinate GetCenter();

	void OnCollide(Entity& entity);
	void OnCollide(Bullet& bullet);
	void OnCollide(Zombie& zombie);
	void OnCollide(Sniper& sniper);

	bool IsDead();

private:
	EntitySpawner* spawner;
	double PosX, PosY;
	double VelX, VelY;
	int health;
	Uint32 startTime;
	vec2 rotationVector = vec2(0, -1);
	bool rotated = false;
	bool fireThisFrame;
	SDL_Rect mCollider;
};