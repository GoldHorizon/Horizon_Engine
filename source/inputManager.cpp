#include "inputManager.h"

//static void InputManager::GetNextEvent();

using namespace Input;

int GetNextEvent()
{
	return SDL_PollEvent(&currentEvent);
}

bool KeyPressed(SDL_Keycode key)
{
	if (currentEvent.type == SDL_KEYDOWN) {
		if (currentEvent.key.keysym.sym == key)
			return true;
	}
	return false;
}

bool KeyReleased(SDL_Keycode key)
{
	if (currentEvent.type == SDL_KEYUP) {
		if (currentEvent.key.keysym.sym == key)
			return true;
	}
	return false;
}

