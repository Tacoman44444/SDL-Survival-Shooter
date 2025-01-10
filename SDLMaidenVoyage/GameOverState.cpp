#include "GameOverState.h"

GameOverState::GameOverState(Level& level, ScoreManager* scoreManager, Wave* waveInfo, std::string gameOverText) : previousLevel(level), _scoreManager(scoreManager), _waveInfo(waveInfo), _gameOverText(gameOverText) {}

GameOverState::~GameOverState() {
	delete _scoreManager;
	delete _waveInfo;
}

void GameOverState::Enter() {
	std::cout << "we are now in game over state\n";
	wavesStatusTexture.LoadFromRenderedText(_gameOverText, SDL_Color{ 30, 30, 30 });
	mainMenuTexture.LoadFromRenderedText("ESC: MAIN MENU", SDL_Color{ 30, 30, 30 }, gFontSMALL);
	restartTexture.LoadFromRenderedText("ENTER: RESTART", SDL_Color{ 30, 30, 30 }, gFontSMALL);
}

GameState* GameOverState::HandleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		Level level;
		switch (e.key.keysym.sym) {
		case SDLK_RETURN:
			
			level.mapFile = "Assets/open_level.map";
			level.totalTiles = 625;
			std::cout << "we are about to exit game over state and enter a playstate\n";
			return new PlayState(level);

		case SDLK_ESCAPE:
			std::cout << "we are about to exit game over state and enter a mainmenu state\n";
			return new MainMenuState();
		}
	}
	return nullptr;
}

void GameOverState::Update() {

}

void GameOverState::Render() {
	SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 0xFF);
	SDL_RenderClear(gRenderer);
	gGameOverBackgroundTexture.Render((SCREEN_WIDTH / 2) - gGameOverBackgroundTexture.GetWidth() / 2, (SCREEN_HEIGHT / 2) - gGameOverBackgroundTexture.GetHeight() - 50);
	gGameOverTextTexture.Render((SCREEN_WIDTH / 2) - gGameOverTextTexture.GetWidth() / 2, (SCREEN_HEIGHT / 2) - gGameOverTextTexture.GetHeight() / 2);
	wavesStatusTexture.Render((SCREEN_WIDTH / 2) - gHighScoreTexture.GetWidth() / 2 - 90, (SCREEN_HEIGHT / 2) + 20);

	mainMenuTexture.Render(50, 50);
	restartTexture.Render(50, 80);

	SDL_RenderPresent(gRenderer);
}