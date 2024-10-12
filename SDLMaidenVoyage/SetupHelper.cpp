#include "SetupHelper.h"

bool Init() {

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
		std::cout << "failed to initialize sdl window, SDL error: " << SDL_GetError() << "\n";
		success = false;
	}
	else {
		gWindow = SDL_CreateWindow("last weapon standing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			std::cout << "could not create SDL window, SDL error: " << SDL_GetError() << "\n";
			success = false;
		}
		else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				std::cout << "could not create renderer from window, SDL error: " << SDL_GetError() << "\n";
				success = false;
			}
			else {
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout << "could not initialize SDL_image, SDL_image error: " << IMG_GetError() << "\n";
					success = false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
				else {
					gScreenSurface = SDL_GetWindowSurface(gWindow);
				}
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool LoadMedia() {
	bool success = true;

	if (!playerTexture.LoadFromFile("Assets/mainCharacter.png")) {
		std::cout << "could not load player image \n";
		success = false;
	}

	if (!sniperBulletTexture.LoadFromFile("Assets/pibullet.png")) {
		std::cout << "could not load sniper bullet image \n";
		success = false;
	}

	if (!playerBulletTexture.LoadFromFile("Assets/starbullet.png")) {
		std::cout << "could not load player bullet image \n";
		success = false;
	}

	if (!sniperTexture.LoadFromFile("Assets/Sniper.png")) {
		std::cout << "could not load sniper image \n";
		success = false;
	}
	if (!ZombieTexture.LoadFromFile("Assets/zombie_sprite.png")) {
		std::cout << "could not load zombie image \n";
		success = false;
	}
	if (!gMainMenuTexture.LoadFromFile("Assets/pirate_background.png")) {
		std::cout << "cound not load main menu image\n";
		success = false;
	}
	if (!gGameOverBackgroundTexture.LoadFromFile("Assets/skull and crossbones.png")) {
		std::cout << "could not load Game Over Background Texture\n";
		success = false;
	}
	if (!gShotgunParticleTexture.LoadFromFile("Assets/ShotgunParticle.png")) {
		std::cout << "could not load Shotgun Particle texture\n";
		success = false;
	}
	gFont = TTF_OpenFont("Assets/joystix monospace.otf", 40);
	if (gFont == NULL) {
		std::cout << "failed to load font from file\n";
		success = false;
	}
	else {
		if (!gGameOverTextTexture.LoadFromRenderedText("GAME OVER!", SDL_Color{ 0, 0, 0 })) {
			std::cout << "failed to load YOU LOSE texture\n";
			success = false;
		}
		if (!gPressPlayTexture.LoadFromRenderedText("PLAY", SDL_Color{ 136, 0, 21 })) {
			std::cout << "failed to load PRESS PLAY texture \n";
			success = false;
		}
		if (!gPlayerHealthTexture.LoadFromRenderedText("Health: 100", SDL_Color{ 180, 0, 0 })) {
			std::cout << "could not load player health texture\n";
			success = false;
		}
	}
	
	if (!gTileTexture.LoadFromFile("Assets/tiles.png")) {
		std::cout << "Failed to load tile set testure \n";
		success = false;
	}
	gMusic = Mix_LoadMUS("Assets/music.wav");
	if (gMusic == NULL) {
		std::cout << "Failed to load music! SDL mixer error: " << Mix_GetError() << "\n";
		success = false;
	}

	gSniperFireSFX = Mix_LoadWAV("Assets/sniperfire.mp3");
	if (gSniperFireSFX == NULL) {
		std::cout << "Failed to sniper fire SFX! SDL mixer error: " << Mix_GetError() << "\n";
		success = false;
	}

	gPlayerFireSFX = Mix_LoadWAV("Assets/playerfire.mp3");
	if (gPlayerFireSFX == NULL) {
		success = false;
	}

	return success;
}

void ResetGameState(std::vector<Bullet>& bulletList, std::vector<Sniper>& sniperList, std::vector<Zombie>& zombieList, Player& player) {
	bulletList.clear();
	sniperList.clear();
	zombieList.clear();
	player.~Player();

}

void Close() {

	TTF_CloseFont(gFont);
	gFont = NULL;

	Mix_FreeChunk(gPlayerFireSFX);
	Mix_FreeChunk(gSniperFireSFX);
	gPlayerFireSFX = NULL;
	gSniperFireSFX = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}