#pragma once

#include <SDL.h>
#include <memory>
#include "GameState.h"
#include "World.h"
#include "CollisionDetector.h"
#include "Player.h"
#include "GameOverState.h"
#include "ScoreManager.h"
#include "Attributes.h"
#include "LButton.h"

class PlayState : public GameState {

	public:
		PlayState(Level& level);
		~PlayState();
		void Enter() override;
		GameState* HandleEvent(SDL_Event& e) override;
		void Update() override;
		void Render() override;
		void SetupRenderUpgradeTextures();
		void RenderUpgradeScreen();

		void MakeWorld();

		const Uint32 waveDuration = 30000;
		const int TOTAL_WAVES = 6;

	private:
		Level currentLevel;
		Uint32 startTime;
		ScoreManager* scoreManager;
		Wave* waveInfo;	
		std::unique_ptr<World> world;
		bool worldState;
		LButton upgradeHealthButton;
		LButton upgradeSpeedButton;
		LButton upgradeDamageButton;
		LButton upgradeROFButton;
		std::vector<LButton> upgradeButtons;
		std::vector<LTexture*> upgradeScreenTextures;
};

void InitializeWaveStruct(Wave* waveInfo);
void SelectAttributeUpgrade(Wave* waveInfo, Attributes::BaseAttributeTypes ATTRIBUTE_TYPE);
void IncrementMobStrength(Wave* waveInfo);