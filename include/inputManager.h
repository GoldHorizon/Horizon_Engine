#pragma once

#include <SDL.h>
#include <string>
#include <iostream>

namespace Input {

	SDL_Event currentEvent;

	void GetNextEvent();

	bool KeyPressed(SDL_Keycode key);
	bool KeyReleased(SDL_Keycode key);

	//class InputManager
	//{
	//public:
	//	static void GetNextEvent();

	//	static bool KeyIsPressed(SDL_Keycode key);
	//	static bool KeyIsReleased(SDL_Keycode key);

	//private:
	//	InputManager();

	//	static SDL_Event currentEvent;
	//};
}
