#include "StateManager.h"

StateManager::StateManager() {
	currentState = new MainMenuState();
	currentState->Enter();
}

void StateManager::ChangeState(GameState* newState) {
	delete currentState;
	currentState = newState;
	currentState->Enter();
}

void StateManager::HandleEvent(SDL_Event& e) {
	GameState* newState = currentState->HandleEvent(e);
	if (newState != nullptr) {
		ChangeState(newState);
	}
}

void StateManager::Update() {
	currentState->Update();
}

void StateManager::Render() {
	currentState->Render();
}

