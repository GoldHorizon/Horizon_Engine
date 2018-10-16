#include "inputManager.h"

using namespace Input;

bool Input::KeyHeld(SDL_Keycode key)
{
	SDL_Scancode sc = SDL_GetScancodeFromKey(key);
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	return (state[sc] == 1);
}

bool Input::NextEvent(Event& event)
{
	if (SDL_PollEvent(&event.ev))
	{
		event.Reset();

		return true;
	}
	return false;
}
