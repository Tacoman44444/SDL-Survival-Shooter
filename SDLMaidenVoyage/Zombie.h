#pragma once

#include <SDL.h>
#include "vec2.h"
#include "HelperFunctions.h"
#include "TileData.h"
#include "Player.h"

class Tile;

class Sniper;

class Player;

struct UpdateContext;

class Zombie : public Entity {
public:

	static const int ZOMBIE_WIDTH = 40;
	static const int ZOMBIE_HEIGHT = 40;
	int ZOMBIE_DAMAGE;

	Zombie(vec2 initialPosition, float velocity, int health, int damage); //change to vec2& after debugging
	
	void Update(UpdateContext& context, double timestep);
	void Render(UpdateContext& context);
	bool IsDead();


	void TakeDamage(int damage);
	void LOS_Move(Player* player, const std::vector<Tile*>& tiles);
	void UpdatePath(const Coordinate& playerCoordinates, std::vector<Tile*>& tiles);
	bool HitsWall(const std::vector<Tile*>& tiles);



	void OnCollide(Entity& entity);
	void OnCollide(Bullet& bullet);
	void OnCollide(Sniper& sniper);
	void OnCollide(Player& player);


	bool CooldownCompleted();


	Coordinate GetCoordinates();
	Coordinate GetCenter();
	SDL_Rect GetCollider();
	SDL_Rect GetMainCollider();


private:
	vec2 zombiePosition;
	vec2 targetPosition;
	float zombieVelocity;
	Uint32 lastHit;
	std::vector<const Tile*> currentPath;
	int zombieHealth;
	SDL_Rect mMainCollider;

};