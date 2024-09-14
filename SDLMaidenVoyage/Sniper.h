#pragma once

#include <SDL.h>
#include "HelperFunctions.h"
#include "UpdateContext.h"
#include "vec2.h"
#include "Bullet.h"
#include "Camera.h"
#include <string>

class Zombie;

class Player;

class EntitySpawner;

class Sniper : public Entity{

public:

	static const int ACTIVE_SNIPER_COUNT = 3;
	static int ActiveSniperLocations[];

	const int SNIPER_WIDTH = 73;
	const int SNIPER_HEIGHT = 51;

	const int SNIPER_ROF = 3;

	Sniper(const vec2& sniperPosition, EntitySpawner& spawner);
	Sniper(const Sniper& other);
	Sniper& operator=(const Sniper& other);

	void Update(UpdateContext& context, double timestep);

	void Fire(const vec2& playerCoords);
	void Render(UpdateContext& context);
	bool CooldownCompleted();
	void TakeDamage(int damage);
	bool IsDead();

	void OnCollide(Entity& entity);

	void OnCollide(Bullet& bullet);
	void OnCollide(Player& player);
	void OnCollide(Zombie& zombie);

	SDL_Rect GetCollider();
	Coordinate GetCoordinates();
	vec2 sniperLoc;

private:
	EntitySpawner* spawner;
	Uint32 lastHit;
	vec2 sniperPosition;
	int health;
	SDL_Rect mCollider;
	int startOffset;
};
