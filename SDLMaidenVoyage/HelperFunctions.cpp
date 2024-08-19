#include "HelperFunctions.h"

namespace HelperFunctions {
	bool CheckCollision(SDL_Rect a, SDL_Rect b) {
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

	int RandomSniperSpawn() {

		static std::random_device rd;

		static std::default_random_engine eng(rd());

		static std::uniform_int_distribution<int> distr(0, TOTAL_SNIPER_SPAWNS - 1);

		return distr(eng);
	}

	int RandomZombieSpawn() {

		static std::random_device rd;

		static std::default_random_engine eng(rd());

		static std::uniform_int_distribution<int> distr(0, TOTAL_ZOMBIE_SPAWNS - 1);

		return distr(eng);
	}

	Coordinate GetNodePointFromWorld(const Coordinate& worldPoint) {

		Coordinate adjustedWorldPoint = Coordinate(worldPoint.x - LEVEL_WIDTH / 2, worldPoint.y - LEVEL_HEIGHT / 2);
		double percentX = (adjustedWorldPoint.x + LEVEL_WIDTH / 2) / LEVEL_WIDTH;
		double percentY = (adjustedWorldPoint.y + LEVEL_HEIGHT / 2) / LEVEL_HEIGHT;
		
		//clamp percentX and precentY later if needed

		percentX = std::clamp(percentX, 0.0, 1.0);
		percentY = std::clamp(percentY, 0.0, 1.0);


		int x = round((GRIDSIZE_X - 1) * percentX);
		int y = round((GRIDSIZE_Y - 1) * percentY);

		return Coordinate(x, y);
	}

	std::vector<const Tile*> GetNeighbors(const Tile* tile, const Tile* tiles[]) {

		std::vector<const Tile*> neighbors;
		int tileIndex = tile->getIndex();
		int kRIGHT = tileIndex + 1;
		int kLEFT = tileIndex - 1;
		int kUP = tileIndex - GRIDSIZE_Y;
		int kDOWN = tileIndex + GRIDSIZE_Y;
		if (kRIGHT >= 0 && kRIGHT < 625) { neighbors.push_back(tiles[kRIGHT]); }
		if (kUP >= 0 && kUP < 625) { neighbors.push_back(tiles[kUP]); }
		if (kLEFT >= 0 && kLEFT < 625) { neighbors.push_back(tiles[kLEFT]); }
		if (kDOWN >= 0 && kDOWN < 625) { neighbors.push_back(tiles[kDOWN]); }
		return neighbors;
		
	}

	std::vector<const Tile*> BreadthFirstSearch(const Coordinate& startPoint, Coordinate& endPoint, const Tile* tiles[]) {

		Coordinate start = GetNodePointFromWorld(startPoint);
		Coordinate end = GetNodePointFromWorld(endPoint);
		int iStart = start.y / TileData::TILE_WIDTH;
		int jStart = start.x / TileData::TILE_HEIGHT;
		int kStart = iStart * GRIDSIZE_Y + jStart;
		int iEnd = end.y / TileData::TILE_WIDTH;
		int jEnd = end.x / TileData::TILE_HEIGHT;
		int kEnd = iEnd * GRIDSIZE_Y + jEnd;

		const Tile* endTile = tiles[kEnd];
		const Tile* startTile = tiles[kStart];
		std::queue<const Tile*> frontier;
		frontier.push(startTile);
		std::map<const Tile*, const Tile*> came_from;
		came_from[startTile] = NULL;

		while (!frontier.empty()) {
			const Tile* currentNode = frontier.front();
			if (currentNode == endTile) {
				break;
			}
			frontier.pop();
			for (auto next : GetNeighbors(currentNode, tiles)) {
				if (!(next->getType() >= TileData::TILE_CENTER) && (next->getType() <= TileData::TILE_TOPLEFT) && came_from.count(next) == 0) {
					frontier.push(next);
					came_from[next] = currentNode;
				}
			}
		}

		const Tile* current = endTile;
		std::vector<const Tile*> path;

		while (*current != *startTile) {
			path.push_back(current);
			current = came_from[current];
		}
		path.push_back(startTile);

		return path;
	}

	bool EntityInFrame(const SDL_Rect& frame, const vec2& entityPosition) {
		int frameIncrease = 100;
		return (entityPosition.x > frame.x - frameIncrease && entityPosition.x < frame.x + frame.w + frameIncrease && entityPosition.y > frame.y - frameIncrease && entityPosition.y < frame.y + frame.h + frameIncrease);
	}

}
