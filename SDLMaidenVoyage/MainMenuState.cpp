#include "MainMenuState.h"

MainMenuState::MainMenuState() : PressPlayButton(LButton(gPressPlayTexture)) {}

MainMenuState::~MainMenuState() {
	std::cout << "Main menu state was deleted\n";
}

void MainMenuState::Enter() {
	PressPlayButton.SetDimensions(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, gPressPlayTexture.GetWidth(), gPressPlayTexture.GetWidth());
	Mix_PlayMusic(gMusic, -1);
}

GameState* MainMenuState::HandleEvent(SDL_Event& e) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		if (PressPlayButton.CheckCollisionWithButton(Coordinate(x, y))) {
			
			Level level;
			level.mapFile = "Assets/open_level.map";
			level.totalTiles = 625;
			//startTime = SDL_GetTicks();	
			return new PlayState(level);
		}
	}
	return nullptr;
	
}

void MainMenuState::Update() {

}

void MainMenuState::Render() {
	SDL_RenderClear(gRenderer);
	SDL_Rect tempRect = { 0, 0, 2000, 2000 };
	SDL_SetRenderDrawColor(gRenderer, 30, 30, 30, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(gRenderer, &tempRect);
	PressPlayButton.Render();
	SDL_RenderPresent(gRenderer);
}