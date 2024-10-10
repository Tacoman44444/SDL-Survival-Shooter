#include "ScoreManager.h"

ScoreManager::ScoreManager() {
	score = 0;
}

void ScoreManager::DisplayScore(int x, int y) {
	gHighScoreTexture.Render(x, y);
}

void ScoreManager::IncrementScore() {
	score++;
	if (!gHighScoreTexture.LoadFromRenderedText("Score: " + std::to_string(score), SDL_Color{ 128, 128, 128 })) {
		std::cout << "failed to render score texture\n";
	}
}