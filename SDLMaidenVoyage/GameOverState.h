#pragma once

#include <SDL.h>
#include "GameState.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "ScoreManager.h"

class GameOverState : public GameState {

	public:
		GameOverState(Level& level, ScoreManager* scoreManager, Wave* waveInfo, std::string gameOverText);
		~GameOverState();
		void Enter() override;
		GameState* HandleEvent(SDL_Event& e) override;
		void Update() override;
		void Render() override;
	
	private:
		Level previousLevel;
		ScoreManager* _scoreManager;
		Wave* _waveInfo;
		std::string _gameOverText;
		LTexture wavesStatusTexture;
		LTexture mainMenuTexture;
		LTexture restartTexture;
};