#pragma once

#include "SDL.h"
#include "GameData.h"
#include "vec2.h"

class Camera {

public:
	Camera();
	void Adjust(const vec2& playerCoords);
	const Coordinate GetCameraCoords();
	SDL_Rect cameraRect;	//should be private
};