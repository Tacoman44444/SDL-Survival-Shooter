#pragma once
#include "Wave.h"

namespace Attributes {
	enum BaseAttributeTypes {
		PLAYER_HEALTH = 1,
		PLAYER_SPEED = 2,

		WEAPON_DAMAGE = 3,
		WEAPON_ROF = 4,
	};

	enum SpecialAbilityTypes {
		LIFE_STEAL,
		SECOND_LIFE,

		ENERGY_BLAST,
	};

	inline void UpgradePlayerHealth(Wave* waveInfo) {
		waveInfo->playerHealth += 10;
	}

	inline void UpgradePlayerSpeed(Wave* waveInfo) {
		waveInfo->playerSpeed += 2;
	}

	inline void UpgradeWeaponDamage(Wave* waveInfo) {
		waveInfo->weaponDamage += 2;
	}

	inline void UpgradeWeaponROF(Wave* waveInfo) {
		waveInfo->weaponROF -= waveInfo->weaponROF / 10;
	}

	inline void EnableLifeSteal(Wave* waveInfo) {
		waveInfo->lifeStealEnabled = true;
	}

	inline void EnableSecondLife(Wave* waveInfo) {
		waveInfo->secondLifeEnabled = true;
	}

	inline void EnableEnergyBlast(Wave* waveInfo) {
		waveInfo->energyBlastEnabled = true;
	}
}
