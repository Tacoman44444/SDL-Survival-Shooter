#include "LButton.h"

LButton::LButton(LTexture& buttonTexture) {
	buttonDimensions = { 0, 0, 0, 0 };
	mButtonTexture = &buttonTexture;
}

void LButton::SetDimensions(int x, int y, int w, int h) {
	buttonDimensions.x = x;
	buttonDimensions.y = y;
	buttonDimensions.w = w;
	buttonDimensions.h = h;
}

bool LButton::CheckCollisionWithButton(const Coordinate& mousebuttonCoords) {
	if (mousebuttonCoords.x > buttonDimensions.x && mousebuttonCoords.x < buttonDimensions.x + buttonDimensions.w && mousebuttonCoords.y > buttonDimensions.y && mousebuttonCoords.y < buttonDimensions.y + buttonDimensions.h) {
		return true;
	}
	else {
		return false;
	}
}

void LButton::Render() {
	mButtonTexture->Render(buttonDimensions.x, buttonDimensions.y);
}