#include "ScoreManager.h"

ScoreManager::ScoreManager() {
	
	score = 0;
	if (!gHighScoreTexture.LoadFromRenderedText("Score: " + std::to_string(score), SDL_Color{ 128, 128, 128 })) {
		std::cout << "failed to render score texture\n";
	}
	std::cout << "New ScoreManager class created!, score = " << score << std::endl;
}

void ScoreManager::DisplayScore(int x, int y) {
	gHighScoreTexture.Render(x, y);
}

void ScoreManager::IncrementScore() {
	std::cout << "Increment score gets called" << std::endl;
	score++;
	if (!gHighScoreTexture.LoadFromRenderedText("Score: " + std::to_string(score), SDL_Color{ 128, 128, 128 })) {
		std::cout << "failed to render score texture\n";
	}
}