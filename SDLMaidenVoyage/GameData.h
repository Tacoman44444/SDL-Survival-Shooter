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

inline const int TOTAL_SNIPER_SPAWNS = 4;
inline const int TOTAL_ZOMBIE_SPAWNS = 4;

inline SDL_Window* gWindow = nullptr;
inline SDL_Renderer* gRenderer = nullptr;
inline SDL_Surface* gScreenSurface = nullptr;

inline Mix_Music* gMusic = nullptr;
inline Mix_Chunk* gSniperFireSFX = nullptr;
inline Mix_Chunk* gPlayerFireSFX = nullptr;
inline Mix_Chunk* gGotHitSFX = nullptr;

inline TTF_Font* gFontLARGE = nullptr;
inline TTF_Font* gFontSMALL = nullptr;
inline TTF_Font* gFont = nullptr;
inline SDL_Rect gPlayerSprites[4];
inline SDL_Rect gTileClips[12];

inline Coordinate sniperSpawnPoints[TOTAL_SNIPER_SPAWNS] = { {300, 300}, {200, 1800}, {1800, 200}, {1700, 1700} };

inline Coordinate zombieSpawnPoints[TOTAL_ZOMBIE_SPAWNS] = { {300, 300}, {200, 1800}, {1800, 200}, {1700, 1700} };


inline std::vector<std::vector<int>> grid;

