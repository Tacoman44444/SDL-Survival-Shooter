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

	std::vector<const Tile*> GetNeighborsFOUR(const Tile* tile, const std::vector<Tile*>& tiles) {
		std::vector<const Tile*> neighbors;
		int tileIndex = tile->getIndex();

		int kRIGHT = tileIndex + 1;
		int kLEFT = tileIndex - 1;
		int kUP = tileIndex - GRIDSIZE_Y;
		int kDOWN = tileIndex + GRIDSIZE_Y;

		if (kRIGHT < tiles.size() && tileIndex % GRIDSIZE_Y != GRIDSIZE_Y - 1) { neighbors.push_back(tiles[kRIGHT]); }
		if (kLEFT >= 0 && tileIndex % GRIDSIZE_Y != 0) { neighbors.push_back(tiles[kLEFT]); }
		if (kUP >= 0) { neighbors.push_back(tiles[kUP]); }
		if (kDOWN < tiles.size()) { neighbors.push_back(tiles[kDOWN]); }

		return neighbors;
	}

	std::vector<const Tile*> GetNeighborsEIGHT(const Tile* tile, const std::vector<Tile*>& tiles) {
		std::vector<const Tile*> neighbors;
		int tileIndex = tile->getIndex();

		int kRIGHT = tileIndex + 1;
		int kLEFT = tileIndex - 1;
		int kUP = tileIndex - GRIDSIZE_Y;
		int kDOWN = tileIndex + GRIDSIZE_Y;
		int kTOPLEFT = tileIndex - GRIDSIZE_Y - 1;
		int kTOPRIGHT = tileIndex - GRIDSIZE_Y + 1;
		int kBOTTOMLEFT = tileIndex + GRIDSIZE_Y - 1;
		int kBOTTOMRIGHT = tileIndex + GRIDSIZE_Y + 1;

		if (kRIGHT < tiles.size() && tileIndex % GRIDSIZE_Y != GRIDSIZE_Y - 1) { neighbors.push_back(tiles[kRIGHT]); }
		if (kLEFT >= 0 && tileIndex % GRIDSIZE_Y != 0) { neighbors.push_back(tiles[kLEFT]); }
		if (kUP >= 0) { neighbors.push_back(tiles[kUP]); }
		if (kDOWN < tiles.size()) { neighbors.push_back(tiles[kDOWN]); }
		if (kTOPLEFT >= 0 && tileIndex % GRIDSIZE_Y != 0) {
			neighbors.push_back(tiles[kTOPLEFT]);
		}
		if (kTOPRIGHT >= 0 && tileIndex % GRIDSIZE_Y != GRIDSIZE_Y - 1) {
			neighbors.push_back(tiles[kTOPRIGHT]);
		}
		if (kBOTTOMLEFT < tiles.size() && tileIndex % GRIDSIZE_Y != 0) {
			neighbors.push_back(tiles[kBOTTOMLEFT]);
		}
		if (kBOTTOMRIGHT < tiles.size() && tileIndex % GRIDSIZE_Y != GRIDSIZE_Y - 1) {
			neighbors.push_back(tiles[kBOTTOMRIGHT]);
		}
		

		return neighbors;
	}

	std::vector<const Tile*> BreadthFirstSearch(const Coordinate& startPoint, const Coordinate& endPoint, std::vector<Tile*>& tiles) {

		Coordinate start = GetNodePointFromWorld(startPoint);
		Coordinate end = GetNodePointFromWorld(endPoint);

		int iStart = start.y;
		int jStart = start.x;
		int kStart = iStart * GRIDSIZE_Y + jStart;

		int iEnd = end.y;
		int jEnd = end.x;
		int kEnd = iEnd * GRIDSIZE_Y + jEnd;

		if (kStart < 0 || kStart >= tiles.size() || kEnd < 0 || kEnd >= tiles.size()) {
			// Handle invalid indices
			return {};
		}

		const Tile* endTile = tiles[kEnd];
		const Tile* startTile = tiles[kStart];
		std::queue<const Tile*> frontier;
		frontier.push(startTile);
		std::map<const Tile*, const Tile*> came_from;
		came_from[startTile] = nullptr;

		while (!frontier.empty()) {
			const Tile* currentNode = frontier.front();
			if (currentNode == endTile) {
				break;
			}
			frontier.pop();

			for (auto next : GetNeighborsFOUR(currentNode, tiles)) {
				if ((next->getType() == TileData::TILE_RED) && came_from.count(next) == 0) {
					frontier.push(next);
					came_from[next] = currentNode;
				}
			}
		}

		// Reconstruct the path
		const Tile* current = endTile;
		std::vector<const Tile*> path;

		while (current != nullptr && current != startTile) {
			path.push_back(current);
			current = came_from[current];
		}

		if (current == startTile) {
			path.push_back(startTile);
			std::reverse(path.begin(), path.end());
		}
		else {
			// No valid path found
			return {};
		}

		return path;
	}


	bool EntityInFrame(const SDL_Rect& frame, const vec2& entityPosition) {
		int frameIncrease = 0;
		return (entityPosition.x > frame.x - frameIncrease && entityPosition.x < frame.x + frame.w + frameIncrease && entityPosition.y > frame.y - frameIncrease && entityPosition.y < frame.y + frame.h + frameIncrease);
	}

	bool EntityInFrame(const SDL_Rect& frame, const vec2& entityPosition, int frameDecrease) {
		int decrease = frameDecrease;
		return (entityPosition.x > frame.x + decrease && entityPosition.x < frame.x + frame.w - decrease && entityPosition.y > frame.y + decrease && entityPosition.y < frame.y + frame.h - decrease);
	}

	int GenerateRandomSpawn(int startValue, int endValue) {
		static std::random_device rd;

		static std::default_random_engine eng(rd());

		static std::uniform_int_distribution<int> distr(startValue, endValue - 1);

		return distr(eng);
	}


	
	bool RayCaster(const Coordinate& a, const Coordinate& b, const std::vector<Tile*>& tiles) {
		int x0 = a.x / TileData::TILE_WIDTH;
		int y0 = a.y / TileData::TILE_HEIGHT;
		int x1 = b.x / TileData::TILE_WIDTH;
		int y1 = b.y / TileData::TILE_HEIGHT;

		int dx = abs(x1 - x0);
		int dy = abs(y1 - y0);
		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;
		int err = dx - dy;

		while (x0 != x1 || y0 != y1) {
			if (y0 * TileData::TOTAL_TILES_ROW + x0 >= 0 && y0 * TileData::TOTAL_TILES_ROW + x0 <= TileData::TOTAL_TILES - 1) {
				if (tiles[y0 * TileData::TOTAL_TILES_ROW + x0]->getType() >= 3) {
					return false;
				}
			}
			

			int e2 = 2 * err;
			if (e2 > -dy) {
				err -= dy;
				x0 += sx;
			}
			if (e2 < dx) {
				err += dx;
				y0 += sy;
			}
		}
		return true;
	}

	

}

