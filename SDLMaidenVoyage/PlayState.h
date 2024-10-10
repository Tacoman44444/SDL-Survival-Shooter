#pragma once

#include <SDL.h>
#include <memory>
#include "GameState.h"
#include "World.h"
#include "CollisionDetector.h"
#include "Player.h"
#include "GameOverState.h"
#include "ScoreManager.h"

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
		ScoreManager* scoreManager;
		std::unique_ptr<World> world; 
};