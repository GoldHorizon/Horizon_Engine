#include <iostream>

#include "game.h"
#include "constants.h"
#include "globals.h"

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
	Game main_game;

	// Initialize the game, return error if it failed
	if (main_game.Initialize() == GameStatus::error)
		return -1;

    // Start tick counter and frame counter
	unsigned next_game_tick = SDL_GetTicks();
	unsigned frames = 0;

	unsigned last_frame_update = next_game_tick;

    // Variable used to track how many updates happened
	int loops;

    // Variable used to keep track of how much to accomodate for processor speed
	float interpolation;

	// Whether or not game is still running
	bool game_is_running = true;

	while (game_is_running)
	{
		loops = 0;

		// Check if we have to process things before the next frame
		while (SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP && game_is_running)
		{
            // Get input from keyboard and mouse
			game_is_running = (main_game.GetInput() == GameStatus::running);

            // Update entities in the game
			main_game.Update();

            // Skip ticks and add loops until we have processed up to the next frame
			next_game_tick += SKIP_TICKS;
			loops++;
		}

		// Decides how much to predict movement of entity -- @todo rework this?
		interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);

		main_game.Render(interpolation);
		++frames;

		unsigned current_tick = SDL_GetTicks();
		if (current_tick - last_frame_update > 1000) {
			currentFPS = frames;
			last_frame_update = current_tick;
			frames = 0;
		}
	}

	return 0;
}
