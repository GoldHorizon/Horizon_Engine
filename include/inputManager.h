#pragma once

#include "event.h"

#include <SDL.h>
#include <string>
#include <iostream>

namespace Input {

	//SDL_Event currentEvent;

	//int GetNextEvent();

	//bool KeyPressed(SDL_Keycode key);
	//bool KeyReleased(SDL_Keycode key);
	bool KeyHeld(SDL_Keycode key);

	Event* NextEvent();

	SDL_Event SDLEvent;
	Event lastEvent;
};
