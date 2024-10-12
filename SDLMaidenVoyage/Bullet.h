#pragma once

#include <array>
#include "GameData.h"
#include "LTexture.h"
#include "Player.h"
#include "Sniper.h"
#include "Zombie.h"
#include "UpdateContext.h"
#include "ShotgunParticle.h"
#include "TileData.h"

class Zombie;

class Sniper;
class Player;

class Bullet : public Entity{

public:

	Bullet(double PosX, double PosY, Shooter shooter, double TargetX, double TargetY);
	~Bullet();

	static const int FIRE_VELOCITY = 20;
	static const int BULLET_DAMAGE = 15;
	static const int TOTAL_SHOTGUN_PARTICLES = 10;

	void Update(UpdateContext& context, double timestep);
	void Render(UpdateContext& context);
	bool IsDead();

	void Move();

	vec2 GetDirection();
	SDL_Rect GetCollider();

	void OnCollide(Entity& entity);

	void OnCollide(Player& player);
	void OnCollide(Sniper& sniper);
	void OnCollide(Zombie& zombie);

	bool OutOfBounds();
	bool HitsWall(const std::vector<Tile*>& tiles);

	double PosX, PosY;
	double DirX, DirY;
	vec2 bulletDirection = vec2(0, 0);
	Shooter shooter;

private:
	bool isDestroyed;
	SDL_Rect mCollider;
	LTexture* bulletTexture;
};
