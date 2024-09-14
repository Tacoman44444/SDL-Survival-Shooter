#pragma once

#include <SDL.h>
#include <memory>
#include "GameState.h"
#include "World.h"
#include "CollisionDetector.h"
#include "Player.h"
#include "GameOverState.h"

class PlayState : public GameState {

	public:
		PlayState(Level& level);
		void Enter() override;
		GameState* HandleEvent(SDL_Event& e) override;
		void Update() override;
		void Render() override;

	private:
		Player* player;
		Level currentLevel;
		Uint32 startTime;
		std::unique_ptr<World> world; 
};