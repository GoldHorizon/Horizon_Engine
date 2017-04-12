#pragma once

#include "entityCollection.h"
#include "enumerations.h"
#include "SDL2/SDL.h"

class Game
{
public:
	/*
	 * Constructors/Destructors
	 */
	Game();
	~Game();

	/*
	 * Class Methods
	 */
	// Initialize()			- Initialize SDL and other game necessities
	int Initialize();

	// ChangeState()		- Changes state to specified state
	//	newState:		new state to change to
	void ChangeState(GameState newState);

	// GetInput()			- Retrieves global window input, returns quit value
	bool GetInput();

	// Update()				- Updates entire game by one frame
	void Update();

	// Render()				- Renders game with interpolation
	//	interpolation:	how much to predict in advance
	void Render(float interpolation);

	// Entities()			- General function, returns main entity collection
	EntityCollection& Entities();

private:
	// _mainWindow		- main window to render to
	SDL_Window* _mainWindow;
	// _mainRenderer	- main renderer, renders to _mainWindow
	SDL_Renderer* _mainRenderer;
	// _event			- global event gathered by game
	SDL_Event _event;
	// _state			- global state gathered by game
	GameState _state;

	// _entities		- collection of game entities
	EntityCollection _entities;
};
