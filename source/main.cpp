#include "../game.h"
#include "../constants.h"

// Program start
int main(int argc, char** argv)
{
	Game mainGame;

	// Initialize the game, return error if it failed
	if (mainGame.Initialize() == -1)
	{
		return -1;
	}

	// userQuit : If the user has somehow exited the application
	bool userQuit = false;

	long startTime = SDL_GetTicks();
	long endTime = SDL_GetTicks();

	double difference = 0;

	while (!userQuit)
	{
		startTime = SDL_GetTicks();

		userQuit = mainGame.GetInput();
		mainGame.Update(difference);
		mainGame.Render();

		endTime = SDL_GetTicks();

		difference = static_cast<double>(endTime - startTime) / 1000;
		//std::cout << difference << std::endl;

	}


	return 0;
}
