#pragma once

#include "LTexture.h"
#include <string>

class ScoreManager {
	public:
		ScoreManager();
		void DisplayScore(int x, int y);
		void IncrementScore();

	private:
		int score;
};