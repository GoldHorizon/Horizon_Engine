#include "inputManager.h"

using namespace Input;

//int Input::GetNextEvent()
//{
//	return SDL_PollEvent(&currentEvent);
//}
//
//bool Input::KeyPressed(SDL_Keycode key)
//{
//	if (currentEvent.type == SDL_KEYDOWN) {
//		if (currentEvent.key.keysym.sym == key)
//			return true;
//	}
//	return false;
//}
//
//bool Input::KeyReleased(SDL_Keycode key)
//{
//	if (currentEvent.type == SDL_KEYUP) {
//		if (currentEvent.key.keysym.sym == key)
//			return true;
//	}
//	return false;
//}

bool Input::KeyHeld(SDL_Keycode key)
{
	SDL_Scancode sc = SDL_GetScancodeFromKey(key);
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	return (state[sc] == 1);
}
