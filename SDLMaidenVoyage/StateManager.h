#pragma once

#include <iostream>
#include <SDL.h>
#include "GameState.h"
#include "MainMenuState.h"


class StateManager {
	public:
		StateManager();
		void ChangeState(GameState* newState);

		void HandleEvent(SDL_Event& e);
		void Update();
		void Render();


	private:
		GameState* currentState;

};