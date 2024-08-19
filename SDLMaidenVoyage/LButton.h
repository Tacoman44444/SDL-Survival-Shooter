#pragma once

#include <SDL.h>
#include "LTexture.h"

class LButton {

public:
	LButton(LTexture& buttonTexture);

	void SetDimensions(int x, int y, int w, int h);
	bool CheckCollisionWithButton(const Coordinate& mouseButtonCoords);
	void Render();

private:
	SDL_Rect buttonDimensions;
	LTexture* mButtonTexture;
};