#include "Node.h"

Node::Node(int _x, int _y, bool _walkable) {
	PosX = _x;
	PosY = _y;
	walkable = _walkable;
}

Coordinate Node::GetCoordinates() {
	return Coordinate(PosX, PosY);
}

bool Node::IsWalkable() {
	return walkable;
}