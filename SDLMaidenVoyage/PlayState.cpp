#include "PlayState.h"

PlayState::PlayState(Level& level) {
	currentLevel = level;
	scoreManager = new ScoreManager();
	std::cout << "New Playstate created" << std::endl;
}

void PlayState::Enter() 
{
	std::cout << "We have entered PlayState::Enter()" << std::endl;
	world = std::make_unique<World>(currentLevel, scoreManager);
	std::cout << "The world has been initialized" << std::endl;
	world->Initialise();
	std::cout << "The world was initialized";
	player = world->GetPlayer();
	std::cout << "we got the player" << std::endl;
	startTime = SDL_GetTicks();
}

GameState* PlayState::HandleEvent(SDL_Event& e) {
	if (player->GetHealth() <= 0) {
		return new GameOverState(currentLevel, scoreManager);
	}
	world->HandleInput(e);
	return nullptr;
}

void PlayState::Update() {
	//std::cout << "running \n";
	world->Update(0);
}

void PlayState::Render() {
	SDL_RenderClear(gRenderer);
	world->Render();
	SDL_RenderPresent(gRenderer);
}