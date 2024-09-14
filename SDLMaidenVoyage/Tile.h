#pragma once

//in the future I would like to have maps determine the size of the level. 
//Presently, map size is determined by the level dimensions set in GameData.h.

#include "vec2.h"
#include "fstream"
#include <SDL.h>
#include "LTexture.h"
#include "TileData.h"
#include "HelperFunctions.h"

class Tile {
public:

	Tile(int x, int y, int tileType);
	void render(const SDL_Rect& camera);

	Tile getTile() const;
	int getType() const;
	SDL_Rect getBox() const;
	Coordinate GetCenter() const;
	int getIndex() const;

private:
	SDL_Rect box;
	int type;
};

extern bool operator == (const Tile& tile1, const Tile& tile2);

extern bool operator != (const Tile& tile1, const Tile& tile2);

extern bool TouchesWall(SDL_Rect box, std::vector<Tile*> tiles);

extern bool SetTiles(std::vector<Tile*>& tiles, std::string mapFile);