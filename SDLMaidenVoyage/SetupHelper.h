#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "GameData.h"
#include "LTexture.h"
#include "Tile.h"
#include "LWindow.h"
#include "Zombie.h"
#include <string>

class Zombie;
class Bullet;
class Sniper;

bool Init();
bool LoadMedia();
void ResetGameState(std::vector<Bullet> bulletList, std::vector<Sniper> sniperList, std::vector<Zombie> zombieList, Player& player);
void Close();