#include "../header.h"

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

	// Time mechanics used for keeping track of elapsed time in game
//	std::chrono::duration<double> duration;
//	std::chrono::steady_clock::time_point timeCurrent;
//	std::chrono::steady_clock::time_point timePrevious;
//
//	timePrevious = std::chrono::steady_clock::now();
//	double lag = 0.0;

	long startTime = SDL_GetTicks();
	long endTime = SDL_GetTicks();

	double difference = 0;

	while (!userQuit)
	{
//		timeCurrent = std::chrono::steady_clock::now();
//		duration = std::chrono::duration_cast<std::chrono::duration<double>>(timeCurrent - timePrevious);
//		timePrevious = timeCurrent;
//		lag += duration.count();
//
//		userQuit = mainGame.GetInput();
//
//		std::cout << std::endl << lag;
//		while (lag >= MS_PER_UPDATE)
//		{
//			std::cout << " In ";
//			mainGame.Update();
//			lag -= MS_PER_UPDATE;
//		}
//
//		mainGame.Render();

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
