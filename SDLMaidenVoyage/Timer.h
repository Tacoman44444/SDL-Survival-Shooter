#pragma once
 
#include <SDL.h>

class LTimer {
public:
	LTimer();

	Uint32 getTicks();

	void start();
	void pause();
	void stop();
	void unpause();

	bool isPaused();
	bool isStarted();

private:
	Uint32 mStartTicks;
	Uint32 mPauseTicks;

	bool mPaused;
	bool mStarted;
};