#pragma once

#include <SDL.h>
#include <vector>
#include "Entity.h"

class World;

class CollisionDetector {
public:
	void checkAll(std::vector<Entity*>& entities);


private:
	bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
};