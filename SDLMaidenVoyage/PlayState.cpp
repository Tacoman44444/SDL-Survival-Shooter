#include "PlayState.h"

PlayState::PlayState(Level& level) : upgradeHealthButton(gUpgradeButtonTexture), upgradeSpeedButton(gUpgradeButtonTexture), upgradeDamageButton(gUpgradeButtonTexture), upgradeROFButton(gUpgradeButtonTexture) {
	currentLevel = level;
	scoreManager = new ScoreManager();
	waveInfo = new Wave();
	InitializeWaveStruct(waveInfo);
	std::cout << "New Playstate created" << std::endl;
	upgradeHealthButton.SetDimensions(600, 200, 43, 43);
	upgradeButtons.push_back(upgradeHealthButton);
	upgradeSpeedButton.SetDimensions(600, 270, 43, 43);
	upgradeButtons.push_back(upgradeSpeedButton);
	upgradeDamageButton.SetDimensions(600, 340, 43, 43);
	upgradeButtons.push_back(upgradeDamageButton);
	upgradeROFButton.SetDimensions(600, 410, 43, 43);
	upgradeButtons.push_back(upgradeROFButton);
}

PlayState::~PlayState() {
	for (LTexture* texture : upgradeScreenTextures) {
		delete texture;
	}
	upgradeScreenTextures.clear();
	std::cout << "playstate was destroyed\n";
}

void PlayState::Enter() 
{
	MakeWorld();
	SetupRenderUpgradeTextures();
	
}

GameState* PlayState::HandleEvent(SDL_Event& e) {
	if (worldState) {
		if (world->Dead()) {
			std::cout << "player died, entering gameover state\n";
			return new GameOverState(currentLevel, scoreManager, waveInfo, "waves survived: " + std::to_string(waveInfo->waveNumber - 1));
		}
		world->HandleInput(e);
		return nullptr;
	}
	else {
		
		if (waveInfo->waveNumber == TOTAL_WAVES) {
			std::cout << "waves survived, entering gameover state\n";
			return new GameOverState(currentLevel, scoreManager, waveInfo, "Waves Survived");
		}
		else {
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				int input = 100;
				SDL_GetMouseState(&x, &y);
				if (upgradeHealthButton.CheckCollisionWithButton(Coordinate(x, y)) && waveInfo->HEALTH_LEVEL < 5) {
					input = 1;
					waveInfo->HEALTH_LEVEL++;
					upgradeScreenTextures[5]->LoadFromRenderedText(std::to_string(waveInfo->HEALTH_LEVEL) + " / 5", SDL_Color{ 255, 255, 255 });
				}
				else if (upgradeSpeedButton.CheckCollisionWithButton(Coordinate(x, y)) && waveInfo->SPEED_LEVEL < 5) {
					input = 2;
					waveInfo->SPEED_LEVEL++;
					upgradeScreenTextures[6]->LoadFromRenderedText(std::to_string(waveInfo->SPEED_LEVEL) + " / 5", SDL_Color{ 255, 255, 255 });
				}
				else if (upgradeDamageButton.CheckCollisionWithButton(Coordinate(x, y)) && waveInfo->DAMAGE_LEVEL < 5) {
					input = 3;
					waveInfo->DAMAGE_LEVEL++;
					upgradeScreenTextures[7]->LoadFromRenderedText(std::to_string(waveInfo->DAMAGE_LEVEL) + " / 5", SDL_Color{ 255, 255, 255 });
				}
				else if (upgradeROFButton.CheckCollisionWithButton(Coordinate(x, y)) && waveInfo->ROF_LEVEL < 5) {
					input = 4;
					waveInfo->ROF_LEVEL++;
					upgradeScreenTextures[8]->LoadFromRenderedText(std::to_string(waveInfo->ROF_LEVEL) + " / 5", SDL_Color{ 255, 255, 255 });
				}
				else {
					return nullptr;
				}
				Attributes::BaseAttributeTypes attribute = static_cast<Attributes::BaseAttributeTypes>(input);
				SelectAttributeUpgrade(waveInfo, attribute);
				IncrementMobStrength(waveInfo);
				waveInfo->waveNumber++;
				worldState = true;
				MakeWorld();
				return nullptr;
			}
		}
		return nullptr;
	}
		
}

void PlayState::Update() {
	if (worldState) {
		if (world->Dead()) {
			return;
		}
		Uint32 currentTime = SDL_GetTicks();
		world->Update(0);
		if (startTime + waveDuration < currentTime && !world->Dead()) {
			worldState = false;
			world = nullptr;
		}
	}
}

void PlayState::Render() {
	
	SDL_RenderClear(gRenderer);
	if (worldState) {
		world->Render();
		Uint32 timeLeft = (waveDuration - (SDL_GetTicks() - startTime)) / 1000;
		gWaveTimerTextTexture.LoadFromRenderedText(std::to_string(timeLeft), SDL_Color{ 180, 0, 0 }); //performance optimization possible
		gWaveTimerTextTexture.Render(1200, 65);
	}
	else {
		
		SDL_Rect tempRect = { 0, 0, 2000, 2000 };
		SDL_SetRenderDrawColor(gRenderer, 30, 30, 30, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(gRenderer, &tempRect);
		RenderUpgradeScreen();
		for (LButton button : upgradeButtons) {
			button.Render();
		}
	}
	SDL_RenderPresent(gRenderer);
}

void PlayState::SetupRenderUpgradeTextures() {
	LTexture* SELECT_UPGRADE_TEXTURE = new LTexture();;
	SELECT_UPGRADE_TEXTURE->LoadFromRenderedText("SELECT UPGRADE", SDL_Color{ 255, 255, 255 }, gFontLARGE);
	LTexture* HEALTH_TEXT_TEXTURE = new LTexture();
	HEALTH_TEXT_TEXTURE->LoadFromRenderedText("HEALTH", SDL_Color{ 255, 255, 255 });
	LTexture* SPEED_TEXT_TEXTURE = new LTexture();
	SPEED_TEXT_TEXTURE->LoadFromRenderedText("SPEED", SDL_Color{ 255, 255, 255 });
	LTexture* DAMAGE_TEXT_TEXTURE = new LTexture();
	DAMAGE_TEXT_TEXTURE->LoadFromRenderedText("DAMAGE", SDL_Color{ 255, 255, 255 });
	LTexture* ROF_TEXT_TEXTURE = new LTexture();
	ROF_TEXT_TEXTURE->LoadFromRenderedText("FIRE RATE", SDL_Color{ 255, 255, 255 });
	LTexture* HEALTH_LEVEL_TEXT_TEXTURE = new LTexture();
	HEALTH_LEVEL_TEXT_TEXTURE->LoadFromRenderedText("0 / 5", SDL_Color{ 255, 255, 255 });
	LTexture* SPEED_LEVEL_TEXT_TEXTURE = new LTexture();
	SPEED_LEVEL_TEXT_TEXTURE->LoadFromRenderedText("0 / 5", SDL_Color{ 255, 255, 255 });
	LTexture* DAMAGE_LEVEL_TEXT_TEXTURE = new LTexture();
	DAMAGE_LEVEL_TEXT_TEXTURE->LoadFromRenderedText("0 / 5", SDL_Color{ 255, 255, 255 });
	LTexture* ROF_LEVEL_TEXT_TEXTURE = new LTexture();
	ROF_LEVEL_TEXT_TEXTURE->LoadFromRenderedText("0 / 5", SDL_Color{ 255, 255, 255 });

	upgradeScreenTextures.push_back(SELECT_UPGRADE_TEXTURE);
	upgradeScreenTextures.push_back(HEALTH_TEXT_TEXTURE);
	upgradeScreenTextures.push_back(SPEED_TEXT_TEXTURE);
	upgradeScreenTextures.push_back(DAMAGE_TEXT_TEXTURE);
	upgradeScreenTextures.push_back(ROF_TEXT_TEXTURE);
	upgradeScreenTextures.push_back(HEALTH_LEVEL_TEXT_TEXTURE);
	upgradeScreenTextures.push_back(SPEED_LEVEL_TEXT_TEXTURE);
	upgradeScreenTextures.push_back(DAMAGE_LEVEL_TEXT_TEXTURE);
	upgradeScreenTextures.push_back(ROF_LEVEL_TEXT_TEXTURE);

}

void PlayState::RenderUpgradeScreen() {
	upgradeScreenTextures[0]->Render(200, 100);
	int y_offset = 200;
	for (int i = 1; i <= 4; i++) {
		upgradeScreenTextures[i]->Render(250, y_offset);
		y_offset += 70;
	}
	y_offset = 200;
	for (int i = 5; i <= 8; i++) {
		upgradeScreenTextures[i]->Render(700, y_offset);
		y_offset += 70;
	}
}

void PlayState::MakeWorld() {
	std::cout << "We have entered PlayState::Enter()/MakeWorld()" << std::endl;
	world = std::make_unique<World>(currentLevel, scoreManager, waveInfo);
	std::cout << "The world has been initialized" << std::endl;
	world->Initialise();
	std::cout << "The world was initialized";
	startTime = SDL_GetTicks();
	worldState = true;
}

void InitializeWaveStruct(Wave* waveInfo) {
	//PLAYER DATA
	waveInfo->playerHealth = 100;
	waveInfo->playerSpeed = 10;
	waveInfo->lifeStealEnabled = false;
	waveInfo->secondLifeEnabled = false;

	//WEAPON DATA
	waveInfo->weaponDamage = 10;
	waveInfo->weaponROF = 250;
	waveInfo->energyBlastEnabled = false;

	//ZOMBIE DATA
	waveInfo->zombieHealth = 30;
	waveInfo->zombieSpeed = 1;
	waveInfo->zombieDamage = 10;

	//SNIPER DATA
	waveInfo->sniperHealth = 20;
	waveInfo->sniperSpeed = 1;
	waveInfo->sniperDamage = 15;

	//CREEPER DATA
	waveInfo->creeperEnabled = false;
	waveInfo->creeperHealth = 80;
	waveInfo->creeperSpeed = 8;

	waveInfo->waveNumber = 1;

	waveInfo->HEALTH_LEVEL = 0;
	waveInfo->SPEED_LEVEL = 0;
	waveInfo->DAMAGE_LEVEL = 0;
	waveInfo->ROF_LEVEL = 0;
}

void SelectAttributeUpgrade(Wave* waveInfo, Attributes::BaseAttributeTypes ATTRIBUTE_TYPE) {
	switch (ATTRIBUTE_TYPE) {
	case Attributes::PLAYER_HEALTH:
		Attributes::UpgradePlayerHealth(waveInfo);
		break;
	case Attributes::PLAYER_SPEED:
		Attributes::UpgradePlayerSpeed(waveInfo);
		break;
	case Attributes::WEAPON_DAMAGE:
		Attributes::UpgradeWeaponDamage(waveInfo);
		break;
	case Attributes::WEAPON_ROF:
		Attributes::UpgradeWeaponROF(waveInfo);
		break;
	default:
		std::cout << "Invalid attribute selected. Please try again.\n";
		break;
	}

}

void IncrementMobStrength(Wave* waveInfo) {
	waveInfo->zombieHealth += 5;
	waveInfo->zombieSpeed += 0.5f;

	waveInfo->sniperDamage += 2;
	waveInfo->sniperHealth += 4;
}