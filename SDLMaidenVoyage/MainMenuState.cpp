#include "MainMenuState.h"

MainMenuState::MainMenuState() : PressPlayButton(LButton(gPressPlayTexture)) {}

void MainMenuState::Enter() {
	PressPlayButton.SetDimensions(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, gPressPlayTexture.GetWidth(), gPressPlayTexture.GetWidth());
}

GameState* MainMenuState::HandleEvent(SDL_Event& e) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		if (PressPlayButton.CheckCollisionWithButton(Coordinate(x, y))) {
			Mix_PlayMusic(gMusic, -1);
			Level level;
			level.mapFile = "Assets/level.map";
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
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);
	SDL_Rect stretchedSize = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	gMainMenuTexture.Render(0, 0, &stretchedSize);
	PressPlayButton.Render();
	SDL_RenderPresent(gRenderer);
}