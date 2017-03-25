#include "../game.h"
#include "../constants.h"
#include <iostream>

// Program start
int main(int argc, char** argv)
{
	Game mainGame;

	// Initialize the game, return error if it failed
	if (mainGame.Initialize() == -1)
	{
		return -1;
	}

	unsigned int nextGameTick = SDL_GetTicks();
	int loops;
	float interpolation;

	bool gameIsRunning = true;

	while (gameIsRunning)
	{
		loops = 0;

		while (SDL_GetTicks() > nextGameTick && loops < MAX_FRAMESKIP)
		{
			gameIsRunning = mainGame.GetInput();
			mainGame.Update();

			nextGameTick += SKIP_TICKS;
			loops++;

			std::cout << loops << " ";
		}

		interpolation = float(SDL_GetTicks() + SKIP_TICKS - nextGameTick) / float(SKIP_TICKS);
		mainGame.Render(interpolation);

		std::cout << interpolation << std::endl;
	}

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
