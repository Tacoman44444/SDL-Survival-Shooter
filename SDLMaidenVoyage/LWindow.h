#pragma once

#include <SDL.h>
#include "GameData.h"

class LWindow {
public:

	LWindow();

	bool init();
	SDL_Renderer* CreateRenderer();
	void HandleEvent(SDL_Event& e);

	int GetWidth();
	int GetHeight();

	bool IsMinimized();

private:
	SDL_Window* mWindow;

	int mWidth;
	int mHeight;

	bool mMinimized;
	bool mFullscreen;

};