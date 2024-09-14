#pragma once

#include <vector>
#include "vec2.h"
#include "Tile.h"
#include "Player.h"

class Player;
class Camera;
class Tile;

struct UpdateContext {
	Player* player;
	Camera* camera;
	std::vector<Tile*> tiles;
};