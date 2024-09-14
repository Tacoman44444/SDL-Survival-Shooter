#pragma once

#include <SDL.h>

class GameState {

	public:
		virtual ~GameState();
		virtual void Enter() = 0;
		virtual GameState* HandleEvent(SDL_Event& e) = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

};