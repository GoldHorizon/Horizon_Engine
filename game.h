#pragma once

#include "entityCollection.h"
#include "enumerations.h"
#include "SDL2/SDL.h"

class Game
{
public:
	Game();
	~Game();

	int Initialize();
	void ChangeState(GameState newState);
	bool GetInput();
	void Update();
	void Render(float interpolation);

	EntityCollection& Entities();

private:
	SDL_Window* _mainWindow;
	SDL_Renderer* _mainRenderer;
	SDL_Event _event;
	GameState _state;

	EntityCollection _entities;
};
