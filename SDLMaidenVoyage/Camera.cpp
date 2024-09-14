#include "Camera.h"

Camera::Camera() {
	cameraRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

void Camera::Adjust(const vec2& playerCoords) {
	//later, I should take into account the width and height of the player as well
	cameraRect.x = (playerCoords.x) - SCREEN_WIDTH / 2;
	cameraRect.y = (playerCoords.y) - SCREEN_HEIGHT / 2;

	if (cameraRect.x < 0) {
		cameraRect.x = 0;
	}
	if (cameraRect.y < 0) {
		cameraRect.y = 0;
	}
	if (cameraRect.x > LEVEL_WIDTH - cameraRect.w) {
		cameraRect.x = LEVEL_WIDTH - cameraRect.w;
	}
	if (cameraRect.y > LEVEL_HEIGHT - cameraRect.h) {
		cameraRect.y = LEVEL_HEIGHT - cameraRect.h;
	}
}

const Coordinate Camera::GetCameraCoords() {
	return Coordinate(cameraRect.x, cameraRect.y);
}