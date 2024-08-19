#pragma once

#include "vec2.h"

class Node {
public:

	Node(int _x, int _y, bool _walkable);
	Coordinate GetCoordinates();
	bool IsWalkable();

private:
	int PosX;
	int PosY;
	bool walkable;
};