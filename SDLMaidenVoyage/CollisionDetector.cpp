#include "CollisionDetector.h"
#include "World.h"


void CollisionDetector::checkAll(std::vector<Entity*>& entities) {
	for (int i = 0; i < entities.size() - 1; i++) {
		for (int j = i + 1; j < entities.size(); j++) {
			if (CheckCollision(entities[i]->GetCollider(), entities[j]->GetCollider())) {
				entities[i]->OnCollide(*entities[j]);
				entities[j]->OnCollide(*entities[i]);
			}
		}
	}
}

bool CollisionDetector::CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
	double a_top = a.y;
	double a_bottom = a.y + a.h;
	double a_left = a.x;
	double a_right = a.x + a.w;

	double b_top = b.y;
	double b_bottom = b.y + b.w;
	double b_left = b.x;
	double b_right = b.x + b.h;

	if (a_bottom < b_top || b_bottom < a_top) {
		return false;
	}

	if (a_left > b_right || b_left > a_right) {
		return false;
	}

	return true;
}