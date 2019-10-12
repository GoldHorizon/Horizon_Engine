#pragma once

// Graphics/Display Constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int DEFAULT_FONT_SIZE = 12;
const SDL_Color DEFAULT_COLOR = { 0, 0, 0 };

const int FONT_COUNT = 4;

// Used in variable step game loop, not sure if chrono uses MS though...
// http://gameprogrammingpatterns.com/game-loop.html
//const double MS_PER_UPDATE = 0.0005;
const unsigned TICKS_PER_SECOND = 30;				// Game ticks per second - should be MUCH less than render frames
const float SKIP_TICKS = 1000 / TICKS_PER_SECOND;	//
const int MAX_FRAMESKIP = 5;						//

const unsigned MAX_FPS = 120;
const float SKIP_RENDERS = 1000 / MAX_FPS;

// Math Constants
const float PI = 3.14159265;
