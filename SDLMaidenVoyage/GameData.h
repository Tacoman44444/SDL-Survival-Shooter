#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include "vec2.h"

class Bullet;

enum Shooter {
	PLAYER,
	SNIPER,
};

inline const int LEVEL_WIDTH = 2000;
inline const int LEVEL_HEIGHT = 2000;

inline const int GRIDSIZE_X = 25;
inline const int GRIDSIZE_Y = 25;

inline const int SCREEN_WIDTH = 1440;
inline const int SCREEN_HEIGHT = 810;

inline const int TOTAL_SNIPER_SPAWNS = 13;
inline const int TOTAL_ZOMBIE_SPAWNS = 13;

inline SDL_Window* gWindow = nullptr;
inline SDL_Renderer* gRenderer = nullptr;
inline SDL_Surface* gScreenSurface = nullptr;

inline Mix_Music* gMusic = nullptr;
inline Mix_Chunk* gSniperFireSFX = nullptr;
inline Mix_Chunk* gPlayerFireSFX = nullptr;

inline TTF_Font* gFont = nullptr;
inline SDL_Rect gPlayerSprites[4];
inline SDL_Rect gTileClips[12];

inline Coordinate sniperSpawnPoints[TOTAL_SNIPER_SPAWNS] = { {360, 360}, {920, 360}, {360, 1320}, {40, 1800}, {1960, 40}, {1320, 200}, {600, 1960}, {1240, 360}, {1960, 360}, {1960, 1160}, {1880, 1480}, {1400, 1720}, {1640, 1720} };

inline Coordinate zombieSpawnPoints[TOTAL_ZOMBIE_SPAWNS] = { {320, 320}, {880, 320}, {320, 1280}, {0, 1760}, {1920, 0}, {1280, 160}, {560, 1920}, {1200, 320}, {1920, 320}, {1920, 1120}, {1840, 1440}, {1360, 1680}, {1600, 1680} };


inline std::vector<std::vector<int>> grid;

