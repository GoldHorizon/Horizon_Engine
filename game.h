#pragma once

#include "header.h"

class Game
{
public:
	Game();
	~Game();

	int Initialize();
	void ChangeState(GameState newState);
	bool GetInput();
	void Update(double elapsedTime);
	void Render();

private:
	SDL_Window* _mainWindow;
	SDL_Renderer* _mainRenderer;
	SDL_Event _event;
	GameState _state;
};
