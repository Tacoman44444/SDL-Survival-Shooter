#pragma once

//cnotains information about all configurable attributes

struct Wave {

public:

	//PLAYER DATA
	int playerHealth = 100;
	int playerSpeed = 10;
	bool lifeStealEnabled = false;
	bool secondLifeEnabled = false;

	//WEAPON DATA
	int weaponDamage = 10;
	int weaponROF = 250;
	bool energyBlastEnabled = false;

	//ZOMBIE DATA
	int zombieHealth = 50;
	float zombieSpeed = 1;
	int zombieDamage = 10;

	//SNIPER DATA
	int sniperHealth = 20;
	float sniperSpeed = 1;
	int sniperDamage = 15;

	//CREEPER DATA
	bool creeperEnabled = false;
	int creeperHealth = 80;
	int creeperSpeed = 8;

	int waveNumber = 1;

	int HEALTH_LEVEL = 0;
	int SPEED_LEVEL = 0;
	int DAMAGE_LEVEL = 0;
	int ROF_LEVEL = 0;

};