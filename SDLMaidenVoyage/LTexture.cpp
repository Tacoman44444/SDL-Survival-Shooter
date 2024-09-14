#include "LTexture.h"

LTexture playerTexture;
LTexture sniperTexture;
LTexture ZombieTexture;

LTexture sniperBulletTexture;
LTexture playerBulletTexture;

LTexture gYouWinTexture;
LTexture gGameOverTextTexture;
LTexture gPressPlayTexture;
LTexture gMainMenuTexture;
LTexture gHighScoreTexture;
LTexture gGameOverBackgroundTexture;
LTexture gPlayerHealthTexture;
LTexture gShotgunParticleTexture;


LTexture gTileTexture;

LTexture::LTexture() {
	mWidth = 0;
	mHeight = 0;
	mTexture = NULL;
}

LTexture::~LTexture() {
	free();
}

bool LTexture::LoadFromFile(std::string path) {

	free();
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		std::cout << "could not load surface from image  " << path << "   , SDL_image error: " << IMG_GetError() << "\n";
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x80, 0x80, 0x40));
		mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (mTexture == NULL) {
			std::cout << "could not create texture from surface, SDL error: " << SDL_GetError() << "\n";
		}
		else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	return mTexture != NULL;

}

bool LTexture::LoadFromRenderedText(std::string text, SDL_Color color) {
	free();
	SDL_Surface* loadedSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);
	if (loadedSurface == NULL) {
		std::cout << "could not load ttf text" << text << ", TTF error: " << TTF_GetError() << "\n";
	}
	else {
		mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (mTexture == NULL) {
			std::cout << "could not create texture from surface. SDL Error: " << SDL_GetError() << "\n";
		}
		else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	return mTexture != NULL;
}

void LTexture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x ,y, mWidth, mHeight };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void LTexture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = -1;
		mHeight = -1;
	}
}

int LTexture::GetHeight() {
	return mHeight;
}

int LTexture::GetWidth() {
	return mWidth;
}