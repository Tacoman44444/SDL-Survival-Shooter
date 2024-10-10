#pragma once

namespace TileData {
	//Tile constants
	inline const int TILE_WIDTH = 80;
	inline const int TILE_HEIGHT = 80;
	inline const int TOTAL_TILES = 625;
	inline const int TOTAL_TILES_ROW = 25;
	inline const int TOTAL_TILES_COLUMN = 25;
	inline const int TOTAL_TILE_SPRITES = 12;

	//The different tile sprites
	inline const int TILE_RED = 0;
	inline const int TILE_GREEN = 1;
	inline const int TILE_BLUE = 2;
	inline const int TILE_CENTER = 3;
	inline const int TILE_TOP = 4;
	inline const int TILE_TOPRIGHT = 5;
	inline const int TILE_RIGHT = 6;
	inline const int TILE_BOTTOMRIGHT = 7;
	inline const int TILE_BOTTOM = 8;
	inline const int TILE_BOTTOMLEFT = 9;
	inline const int TILE_LEFT = 10;
	inline const int TILE_TOPLEFT = 11;
}
