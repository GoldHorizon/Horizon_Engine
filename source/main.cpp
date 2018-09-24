#include <iostream>

#include "game.h"
#include "constants.h"

// Program start
int main(int argc, char** argv)
{
	// Entry point for debug
	//std::cout << "Entry point" << std::endl;

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

		// Decides how much to predict movement of entity
		interpolation = float(SDL_GetTicks() + SKIP_TICKS - nextGameTick) / float(SKIP_TICKS);
		mainGame.Render(interpolation);

		// Part of testing loop counter
		//std::cout << interpolation << std::endl;
	}

//
//  OLD GAME LOOP
//
// userQuit : If the user has somehow exited the application
//	bool userQuit = false;
//
//	long startTime = SDL_GetTicks();
//	long endTime = SDL_GetTicks();
//
//	double difference = 0;
//
//	while (!userQuit)
//	{
//		startTime = SDL_GetTicks();
//
//		userQuit = mainGame.GetInput();
//		mainGame.Update(difference);
//		mainGame.Render();
//
//		endTime = SDL_GetTicks();
//
//		difference = static_cast<double>(endTime - startTime) / 1000;
//		//std::cout << difference << std::endl;
//
//	}




	return 0;
}
