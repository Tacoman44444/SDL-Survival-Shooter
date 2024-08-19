#include "Timer.h"

LTimer::LTimer() {
	mStartTicks = 0;
	mPauseTicks = 0;
	mStarted = false;
	mPaused = false;
}

void LTimer::start() {
	mStarted = true;
	mPaused = false;

	mStartTicks = SDL_GetTicks();
	mPauseTicks = 0;
}

void LTimer::stop() {
	if (mStarted) {
		mStarted = false;
		mPaused = false;

		mStartTicks = 0;
		mPauseTicks = 0;
	}
}

void LTimer::pause() {
	if (mStarted && !mPaused) {
		mPaused = true;

		mPauseTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void LTimer::unpause() {
	if (mStarted && mPaused) {
		mPaused = false;

		mStartTicks = SDL_GetTicks() - mPauseTicks;
		mPauseTicks = 0;
	}
}

Uint32 LTimer::getTicks() {
	if (mStarted) {
		if (mPaused) {
			return mPauseTicks;
		}
		else {
			return SDL_GetTicks() - mStartTicks;
		}
	}
}