#include "World.h"

World::World(Level& level, ScoreManager* scoreManager, Wave* waveInfo) : spawner(*this), currentLevel(level)

{
	context = new UpdateContext;
	camera = new Camera();
	player = new Player(waveInfo->playerSpeed, waveInfo->playerHealth, waveInfo->weaponROF, waveInfo->lifeStealEnabled, waveInfo->secondLifeEnabled);
	_scoreManager = scoreManager;
	_waveInfo = waveInfo;
	context->camera = camera;
	context->player = player;
	entities.push_back(player);
	numEntities = 1;
	numSnipers = 0;
	numZombies = 0;
	collisionDetector = CollisionDetector();
	std::cout << "The world constructor gets called" << std::endl;
	
	gWaveNumberTextTexture.LoadFromRenderedText("Wave " + std::to_string(waveInfo->waveNumber), SDL_Color{ 180, 0, 0 });

	DEBUG_OUTPUT_PLAYER_COORDINATES();
}

World::~World() {
	if (player != nullptr) {
		delete player;
	}
	if (camera != nullptr) {
		delete camera;
	}
	if (context != nullptr) {
		delete context;
	}
}

void World::Initialise() {		//this is where level specific media should be initialized
	if (!SetTiles(context->tiles, currentLevel.mapFile)) {
		std::cout << "FAILED TO LOAD TILES";
		//exit game
	}
	player->SetSpawner(spawner);
	DEBUG_OUTPUT_PLAYER_COORDINATES();
}

bool World::Dead() {
	if (player->GetHealth() <= 0) {
		return true;
	}
	return false;
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
				std::cout << "bruv" << std::endl;
				numZombies--;
			}

			if (Player* player = dynamic_cast<Player*>(entities[i])) {
				DEBUG_OUTPUT_PLAYER_HEALTH();
			}
			else {
				delete entities[i];
				entities.erase(entities.begin() + i);
			}
		}
	}

	numEntities = entities.size();

	context->camera->Adjust(player->GetCoordinates());

	HandleCollisions();
	
	if (numSnipers < 3) {
		//std::cout << "spawing numsnipers\n";
		spawner.SpawnSniper();
		numSnipers++;
	}

	if (numZombies < 5) {
		//std::cout << "spawning numzombies\n";
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

		}
		else {
			entity->Render(*context);
		}
		i++;
		
	}
	_scoreManager->DisplayScore(20, 20);
	player->DisplayHealth(20, 65);
	DisplayWaveInfo();
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

Wave* World::GetWaveInfo() {
	return _waveInfo;
}

void World::DisplayWaveInfo() {
	gWaveNumberTextTexture.Render(1200, 20);
}

void World::DEBUG_OUTPUT_PLAYER_COORDINATES() {
	std::cout << "player coordinates: " << player->GetCoordinates() << std::endl;
}

void World::DEBUG_OUTPUT_PLAYER_HEALTH() {
	std::cout << "player health: " << player->GetHealth() << std::endl;
}