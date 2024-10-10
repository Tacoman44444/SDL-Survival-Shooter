#pragma once

#include <vector>
#include <memory>
#include "Entity.h"
#include "Player.h"
#include "UpdateContext.h"
#include "GameData.h"
#include "CollisionDetector.h"
#include "EntitySpawner.h"
#include "Level.h"
#include "Tile.h"
#include "Camera.h"
#include "ScoreManager.h"

class CollisionDetector;
class EntitySpawner;
class Sniper;

class World {
public:

	World(Level& level,	ScoreManager* scoreManager);

	//make copy constructor and copy assignment operator if needed

	void Initialise();
	void HandleInput(SDL_Event& e);
	void Update(double timestep);
	void Render();
	void AddEntity(Entity* entity);
	Player* GetPlayer();
	

private:
	Player* player;		//could make player and camera shared pointers
	Camera* camera;
	ScoreManager* _scoreManager;
	std::vector<Entity*> entities;
	std::vector<vec2> activeSniperLocations;
	int numEntities;
	int numSnipers;
	int numZombies;
	Level currentLevel;
	UpdateContext* context;
	CollisionDetector collisionDetector;
	EntitySpawner spawner;

	void HandleCollisions();
};