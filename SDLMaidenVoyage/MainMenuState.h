#pragma once

#include <SDL.h>
#include "GameData.h"
#include "LTexture.h"
#include "LButton.h"
#include "GameState.h"
#include "PlayState.h"
#include "GameOverState.h"

class MainMenuState : public GameState {

	public:
		MainMenuState();
		void Enter() override;
		GameState* HandleEvent(SDL_Event& e) override;
		void Update() override;
		void Render() override;

	private:
		LButton PressPlayButton;

};
