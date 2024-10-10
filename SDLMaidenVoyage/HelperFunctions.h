#pragma once

#include <SDL.h>
#include <random>
#include <cmath>
#include "vec2.h"
#include "GameData.h"
#include "Tile.h"
#include "Sniper.h"
#include <queue>
#include <map>

class Tile;

namespace HelperFunctions {
	bool CheckCollision(SDL_Rect a, SDL_Rect b);

	int RandomSniperSpawn();

	int RandomZombieSpawn();

	Coordinate GetNodePointFromWorld(const Coordinate& worldPoint);

	std::vector<const Tile*> GetNeighbors(const Tile* tile, const Tile* tiles[]);

	std::vector<const Tile*> BreadthFirstSearch(const Coordinate& startPoint, const Coordinate& endPoint, std::vector<Tile*>& tiles);

	bool EntityInFrame(const SDL_Rect& frame, const vec2& entityPosition);

	int GenerateRandomSpawn(int startValue, int endValue);

	bool RayCaster(const Coordinate& a, const Coordinate& b, const std::vector<Tile*>& tiles);
}