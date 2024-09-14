#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cmath> 
#include <vector>
#include "vec2.h"
#include "LTexture.h"
#include "Tile.h"
#include "GameData.h"
#include "SetupHelper.h"
#include "HelperFunctions.h"
#include "Timer.h"
#include "Zombie.h"
#include "LButton.h"
#include "Camera.h"
#include "Bullet.h"
#include "Sniper.h"
#include "StateManager.h"

const double MS_PER_UPDATE = 10;

int main(int argc, char* args[]) {
	if (!Init()) {
		std::cout << "failed to initialize\n";
	}
	else {

		if (!LoadMedia()) {
			std::cout << "failed to load media\n";
		}
		else {
			StateManager stateManager;
			LTimer timer;
			timer.start();
			double previousTicks = timer.getTicks();
			double lag = 0.0;
			bool quit = false;
			SDL_Event e;

			while (!quit) {

				double currentTicks = timer.getTicks();
				double elapsed = currentTicks - previousTicks;
				previousTicks = currentTicks;
				lag += elapsed;

				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else {
						stateManager.HandleEvent(e);
					}
					//std::cout << "in SDL_Pollevent loop, e: \n";
				}
				//std::cout << "main loop running";
				
				while (lag >= MS_PER_UPDATE) {
					stateManager.Update();
					lag -= MS_PER_UPDATE;
				}

				stateManager.Render();	// implement Render(lag / MS_PER_UPDATE) later
			}
		}
		
	}
	

	return 0;
}