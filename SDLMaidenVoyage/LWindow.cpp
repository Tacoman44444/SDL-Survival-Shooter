#include "LWindow.h"

LWindow::LWindow() {
	mWindow = NULL;

	mWidth = 0;
	mHeight = 0;

	mMinimized = false;
	mFullscreen = false;
}

bool LWindow::init() {
	mWindow = SDL_CreateWindow("Last Weapon Standing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (mWindow != NULL) {
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;

	}

	return mWindow != NULL;
}

SDL_Renderer* LWindow::CreateRenderer() {
	return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

