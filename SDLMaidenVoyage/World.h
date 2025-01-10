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
#include "Wave.h"

class CollisionDetector;
class EntitySpawner;
class Sniper;

class World {
public:

	World(Level& level,	ScoreManager* scoreManager, Wave* waveInfo);
	~World();

	//make copy constructor and copy assignment operator if needed

	void Initialise();
	bool Dead();
	void HandleInput(SDL_Event& e);
	void Update(double timestep);
	void Render();
	void AddEntity(Entity* entity);
	Player* GetPlayer();
	Wave* GetWaveInfo();
	void DisplayWaveInfo();

	void DEBUG_OUTPUT_PLAYER_COORDINATES();
	void DEBUG_OUTPUT_PLAYER_HEALTH();
	

private:
	Player* player;
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
	Wave* _waveInfo;
	EntitySpawner spawner;

	void HandleCollisions();
};

