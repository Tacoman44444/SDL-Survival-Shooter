#pragma once

#include <SDL.h>
#include <random>
#include <cmath>
#include "vec2.h"
#include "GameData.h"
#include "Tile.h"
#include <queue>
#include <map>

namespace HelperFunctions {
	bool CheckCollision(SDL_Rect a, SDL_Rect b);

	int RandomSniperSpawn();

	int RandomZombieSpawn();

	Coordinate GetNodePointFromWorld(const Coordinate& worldPoint);

	bool EntityInFrame(const SDL_Rect& frame, const vec2& entityPosition);

}