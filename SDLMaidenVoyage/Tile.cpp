#include "Tile.h"

Tile::Tile(int x, int y, int tileType) : type(tileType) {
	box.x = x;
	box.y = y;
	box.w = TileData::TILE_WIDTH;
	box.h = TileData::TILE_HEIGHT;
}

void Tile::render(const SDL_Rect& camera) {
	if (HelperFunctions::CheckCollision(camera, box)) {
		gTileTexture.Render(box.x - camera.x, box.y - camera.y, &gTileClips[type]);
	}
}

Tile Tile::getTile() const {
	return *this;
}

int Tile::getType() const {
	return type;
}

SDL_Rect Tile::getBox() const {
	return box;
}

Coordinate Tile::GetCenter() const {
	return Coordinate(box.x + (box.w / 2), box.y + (box.h / 2));
}

int Tile::getIndex() const {
	int i = box.y / TileData::TILE_WIDTH;
	int j = box.x / TileData::TILE_WIDTH;
	
	return i * GRIDSIZE_Y + j;
}

bool operator == (const Tile& tile1, const Tile& tile2) {
	if (tile1.getBox().x == tile2.getBox().x && tile1.getBox().y == tile2.getBox().y) {
		return true;
	}
	return false;
}

bool operator != (const Tile& tile1, const Tile& tile2) {
	return !(tile1 == tile2);
}

bool TouchesWall(SDL_Rect box, std::vector<Tile*> tiles) {
	for (int i = 0; i < TileData::TOTAL_TILES; i++) {
		if ((tiles[i]->getType() >= TileData::TILE_CENTER) && (tiles[i]->getType() <= TileData::TILE_TOPLEFT)) { //see const values of tile center and topleft to understand 
			if (HelperFunctions::CheckCollision(box, tiles[i]->getBox())) {
				return true;
			}
		}
	}
	return false;
}

bool SetTiles(std::vector<Tile*>& tiles, std::string mapFile) {
	bool tilesLoaded = true;

	int x = 0, y = 0;

	std::ifstream map(mapFile);

	if (map.fail()) {
		std::cout << "Unable to load map file \n";
		tilesLoaded = false;
	}
	else {
		std::cout << "we here";
		for (int i = 0; i < TileData::TOTAL_TILES; ++i) {
			int tileType = -1;

			map >> tileType;

			if (map.fail()) {
				std::cout << "Error loading map: Unexpected end of file!\n";
				tilesLoaded = false;
				break;
			}
			if ((tileType >= 0) && (tileType < TileData::TOTAL_TILE_SPRITES)) {
				Tile* newTile = new Tile(x, y, tileType);
				tiles.push_back(newTile);
			}
			else {
				std::cout << "Error loading map: invalis tile type at " << i << "\n";
				tilesLoaded = false;
				break;
			}

			x += TileData::TILE_WIDTH;

			if (x >= LEVEL_WIDTH) {
				x = 0;
				y += TileData::TILE_HEIGHT;
			}

			std::cout << i << "\n";
		}
		if (tilesLoaded) {
			gTileClips[TileData::TILE_RED].x = 0;
			gTileClips[TileData::TILE_RED].y = 0;
			gTileClips[TileData::TILE_RED].w = TileData::TILE_WIDTH;
			gTileClips[TileData::TILE_RED].h = TileData::TILE_HEIGHT;

			gTileClips[TileData::TILE_GREEN].x = 0;
			gTileClips[TileData::TILE_GREEN].y = 80;
			gTileClips[TileData::TILE_GREEN].w = TileData::TILE_WIDTH;
			gTileClips[TileData::TILE_GREEN].h = TileData::TILE_HEIGHT;

			gTileClips[TileData::TILE_BLUE].x = 0;
			gTileClips[TileData::TILE_BLUE].y = 160;
			gTileClips[TileData::TILE_BLUE].w = TileData::TILE_WIDTH;
			gTileClips[TileData::TILE_BLUE].h = TileData::TILE_HEIGHT;

			gTileClips[TileData::TILE_TOPLEFT].x = 80;
			gTileClips[TileData::TILE_TOPLEFT].y = 0;
			gTileClips[TileData::TILE_TOPLEFT].w = TileData::TILE_WIDTH;
			gTileClips[TileData::TILE_TOPLEFT].h = TileData::TILE_HEIGHT;

			gTileClips[TileData::TILE_LEFT].x = 80;
			gTileClips[TileData::TILE_LEFT].y = 80;
			gTileClips[TileData::TILE_LEFT].w = TileData::TILE_WIDTH;
			gTileClips[TileData::TILE_LEFT].h = TileData::TILE_HEIGHT;

			gTileClips[TileData::TILE_BOTTOMLEFT].x = 80;
			gTileClips[TileData::TILE_BOTTOMLEFT].y = 160;
			gTileClips[TileData::TILE_BOTTOMLEFT].w = TileData::TILE_WIDTH;
			gTileClips[TileData::TILE_BOTTOMLEFT].h = TileData::TILE_HEIGHT;

			gTileClips[TileData::TILE_TOP].x = 160;
			gTileClips[TileData::TILE_TOP].y = 0;
			gTileClips[TileData::TILE_TOP].w = TileData::TILE_WIDTH;
			gTileClips[TileData::TILE_TOP].h = TileData::TILE_HEIGHT;

			gTileClips[TileData::TILE_CENTER].x = 160;
			gTileClips[TileData::TILE_CENTER].y = 80;
			gTileClips[TileData::TILE_CENTER].w = TileData::TILE_WIDTH;
			gTileClips[TileData::TILE_CENTER].h = TileData::TILE_HEIGHT;

			gTileClips[TileData::TILE_BOTTOM].x = 160;
			gTileClips[TileData::TILE_BOTTOM].y = 160;
			gTileClips[TileData::TILE_BOTTOM].w = TileData::TILE_WIDTH;
			gTileClips[TileData::TILE_BOTTOM].h = TileData::TILE_HEIGHT;

			gTileClips[TileData::TILE_TOPRIGHT].x = 240;
			gTileClips[TileData::TILE_TOPRIGHT].y = 0;
			gTileClips[TileData::TILE_TOPRIGHT].w = TileData::TILE_WIDTH;
			gTileClips[TileData::TILE_TOPRIGHT].h = TileData::TILE_HEIGHT;

			gTileClips[TileData::TILE_RIGHT].x = 240;
			gTileClips[TileData::TILE_RIGHT].y = 80;
			gTileClips[TileData::TILE_RIGHT].w = TileData::TILE_WIDTH;
			gTileClips[TileData::TILE_RIGHT].h = TileData::TILE_HEIGHT;

			gTileClips[TileData::TILE_BOTTOMRIGHT].x = 240;
			gTileClips[TileData::TILE_BOTTOMRIGHT].y = 160;
			gTileClips[TileData::TILE_BOTTOMRIGHT].w = TileData::TILE_WIDTH;
			gTileClips[TileData::TILE_BOTTOMRIGHT].h = TileData::TILE_HEIGHT;
		}
	}

	map.close();
	return tilesLoaded;
}