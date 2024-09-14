#pragma once

#include <SDL.h>
#include "GameState.h"
#include "PlayState.h"
#include "MainMenuState.h"

class GameOverState : public GameState {

	public:
		GameOverState(Level& level);
		void Enter() override;
		GameState* HandleEvent(SDL_Event& e) override;
		void Update() override;
		void Render() override;
	
	private:
		Level previousLevel;
};