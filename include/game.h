#pragma once

#include <vector>

#include "entityCollection.h"
#include "enumerations.h"

#include "SDL.h"

class GameState;

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

	// LoadFonts()			- Load used fonts into memory
	void LoadFonts();

	// ChangeState()		- Changes state to specified state
	//	newState:		new state to change to
	void ChangeState(GameState* newState);

    // PushState()          - Push another state onto the stack of states
    void PushState (GameState* newState);

    // PopState()           - Pop the latest state from the top of the stack
    void PopState();

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

    // _stateStack      - stack of all states in game
    std::vector<GameState*> _stateStack;

	// _entities		- collection of game entities
	EntityCollection _entities;
};
