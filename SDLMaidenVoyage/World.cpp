#include "World.h"

World::World(Level& level, ScoreManager* scoreManager) : spawner(*this), currentLevel(level)

{
	context = new UpdateContext;
	camera = new Camera();
	player = new Player();
	_scoreManager = scoreManager;
	context->camera = camera;
	context->player = player;
	entities.push_back(player);
	numEntities = 1;
	numSnipers = 0;
	numZombies = 0;
	collisionDetector = CollisionDetector();
	std::cout << "The world constructor gets called" << std::endl;
	
}

void World::Initialise() {		//this is where level specific media should be initialized
	std::cout << "we are here";
	if (!SetTiles(context->tiles, currentLevel.mapFile)) {
		std::cout << "FAILED TO LOAD TILES";
		//exit game
	}
	
	player->SetSpawner(spawner);
}

void World::HandleInput(SDL_Event& e) {
	player->HandleEvent(e, camera->GetCameraCoords());
}

void World::Update(double timestep) {
	int numEntitiesThisFrame = numEntities;
	for (int i = 0; i < numEntitiesThisFrame; i++) {
		entities[i]->Update(*context, timestep);
	}

	for (int i = numEntities - 1; i >= 0; i--) {
		if (entities[i]->IsDead()) {
			std::cout << "why the fuck is my bullet dead???\n";
			if (Sniper* sniper = dynamic_cast<Sniper*>(entities[i])) {
				_scoreManager->IncrementScore();
				numSnipers--;
				auto it = std::find(activeSniperLocations.begin(), activeSniperLocations.end(), sniper->GetCoordinates());
				if (it != activeSniperLocations.end()) {
					activeSniperLocations.erase(it);
				}
			}
			else if (Zombie* zombie = dynamic_cast<Zombie*>(entities[i])) {
				_scoreManager->IncrementScore();
				numZombies--;
			}

			
			delete entities[i];
			entities.erase(entities.begin() + i);
		}
	}

	numEntities = entities.size();

	context->camera->Adjust(player->GetCoordinates());

	HandleCollisions();
	
	if (numSnipers < 3) {
		std::cout << "spawing numsnipers\n";
		spawner.SpawnSniper(activeSniperLocations);
		numSnipers++;
	}

	if (numZombies < 7) {
		std::cout << "spawning numzombies\n";
		spawner.SpawnZombie();
		numZombies++;
	}
	
	
}

void World::Render() {

	for (Tile* tile : context->tiles) {
		tile->render(context->camera->cameraRect);
	}
	int i = 1;
	for (Entity* entity : entities) {
		if (entity == nullptr) {
			std::cout << "the fuck??????\n";
		}
		else {
			entity->Render(*context);
		}
		i++;
		
	}
	_scoreManager->DisplayScore(20, 20);
}

void World::AddEntity(Entity* entity) {
	entities.push_back(entity);
	numEntities++;
}

void World::HandleCollisions() {
	collisionDetector.checkAll(entities);
}

Player* World::GetPlayer() {
	return player;
}