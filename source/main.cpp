#include <iostream>

#include "game.h"
#include "constants.h"

#ifdef _WIN32
	#ifdef _WIN64
		#define BUILD_WIN64

	#else
		#define BUILD_WIN32

	#endif
#elif __linux__
	#define BUILD_LINUX

#else
	#define BUILD_UNKNOWN

#endif

// Program start
int main(int argc, char** argv)
{
	// Start game
	Game mainGame;

	// Initialize the game, return error if it failed
	if (mainGame.Initialize() == -1)
	{
		return -1;
	}

    // Start tick counter
	unsigned int nextGameTick = SDL_GetTicks();

    // Variable used to track how many updates happened
	int loops;

    // Variable used to keep track of how much to accomodate for processor speed
	float interpolation;

	// Whether or not game is still running
	bool gameIsRunning = true;

	while (gameIsRunning)
	{
		loops = 0;

		// Check if we have lots of time to process things before the next frame
		while (SDL_GetTicks() > nextGameTick && loops < MAX_FRAMESKIP && gameIsRunning)
		{
            // Get input from keyboard and mouse
			gameIsRunning = mainGame.GetInput();

            // Update entities in the game
			mainGame.Update();

            // Skip ticks and add loops until we have processed up to the next frame
			nextGameTick += SKIP_TICKS;
			loops++;

			// Part of testing loop counter
			//std::cout << loops << " ";
		}

		// Decides how much to predict movement of entity -- @todo rework this
		interpolation = float(SDL_GetTicks() + SKIP_TICKS - nextGameTick) / float(SKIP_TICKS);
		mainGame.Render(interpolation);
	}

	return 0;
}
