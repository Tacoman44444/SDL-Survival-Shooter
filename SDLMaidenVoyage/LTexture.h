#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "vec2.h"
#include "GameData.h"

class LTexture {

public:
	LTexture();
	~LTexture();

	bool LoadFromFile(std::string path);
	bool LoadFromFileScaled(std::string path, int width, int height);
	bool LoadFromRenderedText(std::string text, SDL_Color color);
	bool LoadFromRenderedText(std::string text, SDL_Color color, TTF_Font* font);
	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void free();

	int GetWidth();
	int GetHeight();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

extern LTexture playerTexture;
extern LTexture sniperTexture;
extern LTexture ZombieTexture;

extern LTexture sniperBulletTexture;
extern LTexture playerBulletTexture;

extern LTexture gGameOverTextTexture;
extern LTexture gYouWinTexture;
extern LTexture gMainMenuTexture;
extern LTexture gPressPlayTexture;
extern LTexture gHighScoreTexture;
extern LTexture gGameOverBackgroundTexture;
extern LTexture gPlayerHealthTexture;
extern LTexture gShotgunParticleTexture;
extern LTexture gWaveNumberTextTexture;
extern LTexture gWaveTimerTextTexture;
extern LTexture gUpgradeButtonTexture;

extern LTexture gTileTexture;