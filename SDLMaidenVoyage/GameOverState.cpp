#include "GameOverState.h"

GameOverState::GameOverState(Level& level, ScoreManager* scoreManager) : previousLevel(level), _scoreManager(scoreManager) {}

GameOverState::~GameOverState() {
	delete _scoreManager;
}

void GameOverState::Enter() {

}

GameState* GameOverState::HandleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		Level level;
		switch (e.key.keysym.sym) {
		case SDLK_RETURN:
			
			level.mapFile = "Assets/level.map";
			level.totalTiles = 625;
			return new PlayState(level);

		case SDLK_ESCAPE:
			return new MainMenuState();
		}
	}
	return nullptr;
}

void GameOverState::Update() {

}

void GameOverState::Render() {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	gGameOverBackgroundTexture.Render((SCREEN_WIDTH / 2) - gGameOverBackgroundTexture.GetWidth() / 2, (SCREEN_HEIGHT / 2) - gGameOverBackgroundTexture.GetHeight() - 50);
	gGameOverTextTexture.Render((SCREEN_WIDTH / 2) - gGameOverTextTexture.GetWidth() / 2, (SCREEN_HEIGHT / 2) - gGameOverTextTexture.GetHeight() / 2);
	_scoreManager->DisplayScore((SCREEN_WIDTH / 2) - gHighScoreTexture.GetWidth() / 2, (SCREEN_HEIGHT / 2) + 20);
	SDL_RenderPresent(gRenderer);
}