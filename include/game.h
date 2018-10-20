#pragma once

#include <vector>

#include "entityCollection.h"
#include "enumerations.h"
#include "event.h"
#include "file.h"

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

  // CloseConsole()		- Closes the console, if it is open
  void CloseConsole();

  // QuitGame()			- Quits the game
  void QuitGame();

private:
  // LoadFonts()			- Load used fonts into memory
  void LoadFonts();

  // _mainWindow		- main window to render to
  SDL_Window* _mainWindow;
  // _mainRenderer	- main renderer, renders to _mainWindow
  SDL_Renderer* _mainRenderer;
  // _event			- global event gathered by game
  Event _event;

  // _stateStack      - stack of all states in game
  std::vector<GameState*> _stateStack;

  // _entities		- collection of game entities
  EntityCollection _entities;

  // _playing		- whether the game is still being played (running)
  bool _playing;

  // _varFile		- file containing game variables
  File _varFile;
};
