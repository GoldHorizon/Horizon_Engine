#include <iostream>

#include "game.h"
#include "globals.h"

// Used in variable step game loop, not sure if chrono uses MS though...
// http://gameprogrammingpatterns.com/game-loop.html
const unsigned TICKS_PER_SECOND = 30;				// Game ticks per second - should be less than render frames
const float SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

const unsigned MAX_FPS = 60;
const float SKIP_RENDERS = 1000 / MAX_FPS;

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
	unsigned next_render = SDL_GetTicks();
	unsigned frames = 0;

	unsigned last_frame_update = next_game_tick;

    // Variable used to track how many updates happened
	unsigned update_loops;
	unsigned render_loops;

    // Variable used to keep track of how much to accomodate for processor speed
	float interpolation;

	// Whether or not game is still running
	bool game_is_running = true;

	while (game_is_running)
	{
		update_loops = 0;

		// Check if we have to process things before the next frame
		while (SDL_GetTicks() > next_game_tick && update_loops < MAX_FRAMESKIP && game_is_running)
		{
            // Get input from keyboard and mouse
			game_is_running = (main_game.GetInput() == GameStatus::running);

            // Update entities in the game
			main_game.Update();

            // Skip ticks and add loops until we have processed up to the next frame
			next_game_tick += SKIP_TICKS;
			++update_loops;
		}

		render_loops = 0;

		while (SDL_GetTicks() > next_render && render_loops < MAX_FRAMESKIP && game_is_running)
		{
			// Decides how much to predict movement of entity
			interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);

			main_game.Render(interpolation);
			++frames;

			next_render += SKIP_RENDERS;
			++render_loops;
		}

		unsigned current_tick = SDL_GetTicks();
		if (current_tick - last_frame_update > 1000) {
			currentFPS = frames;
			last_frame_update = current_tick;
			frames = 0;
		}
	}

	return 0;
}
