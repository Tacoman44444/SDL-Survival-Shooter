#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "GameData.h"
#include "LTexture.h"
#include "Tile.h"
#include <string>

bool Init();
bool LoadMedia(Tile* tiles[]);
void Close();