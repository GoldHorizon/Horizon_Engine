#include "../include/game.h"
#include "../include/globals.h"
#include "../include/constants.h"
#include "../include/ball.h"
#include "enumerations.h"
#include "types.h"

#include "../include/states/playing.h"
#include "../include/states/uninitialized.h"
#include "../include/states/titleScreen.h"
#include "../include/states/options.h"
#include "../include/states/pauseMenu.h"
#include "states/editor.h"
#include "states/console.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <functional>

Game::Game():
	_mainWindow(0),
	_mainRenderer(0),
	_playing(true)
	//_state(GameState::UNINITIALIZED)
{
	// Set the draw color for our renderer (rendered when renderer is cleared)
	SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);

    // Set our stack to only be uninitialized.
    _stateStack.push_back(StateUninitialized::Instance());

	auto quit_game_command = [this](sVector args) { QuitGame(); };

	commands["quit"] = quit_game_command;
	commands["exit"] = quit_game_command;

	//commands["close"] = [this](sVector args) { CloseConsole(); };
}

Game::~Game()
{
	TTF_Quit();
	SDL_Quit();
}

int Game::Initialize()
{
	// If the game was already initialized, there's a problem.
	//if (_state != GameState::UNINITIALIZED)
    if (_stateStack.empty() || (_stateStack.back()->GetType() != GameStateType::UNINITIALIZED))
   	{   
   		return -1;
   	}
	// STEP 1
	// Initialize SDL using SDL_Init
	// Note: Using SDL_INIT_EVERYTHING slows startup considerably on 32-bit versions
	// Consider implementing startup of subsystems in threads?
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1)
	{
		// If it fails, output error message and quit
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	if (TTF_Init() == -1) {
		//printf("TTF_Init: %s\n", TTF_GetError());
		//exit(2);
		std::cerr << "Failed to initialize SDL_TTF: " << TTF_GetError() << std::endl;
	}

	// Also initialize TTF, for fonts
	TTF_Init();
	// After doing that, load global fonts for our use.
	LoadFonts();

	// STEP 2
	// Setup our main window with an SDL_Window pointer
	_mainWindow = SDL_CreateWindow("Main Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	// Check to make sure it properly created the window
	if (_mainWindow == nullptr)
	{
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		return -1;
	}

	// STEP 3
	// Create a renderer for use with our mainWindow
	// The -1 is the 'index', which determines the rendering driver to use. -1 tells it to choose the first one it finds
	_mainRenderer = SDL_CreateRenderer(_mainWindow, -1, SDL_RENDERER_ACCELERATED);
	// Check to see that is created the renderer
	if (_mainRenderer == nullptr)
	{
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
		return -1;
	}

	globalRenderer = _mainRenderer;

	// Set resolution of renderer to window resolution, output if there's an error
	// NOTE - This error checking was not done in the tutorial; more for my own practice
	//		  Will refrain from doing too much error checking, only where appropriate
	if (SDL_RenderSetLogicalSize(_mainRenderer, SCREEN_WIDTH, SCREEN_HEIGHT) == -1)
	{
		std::cerr << "Failed to set renderer resolution: " << SDL_GetError() << std::endl;
		return -1;
	}

	// If all is well, set the game state and return something besides -1
	//ChangeState(StateTitleScreen::Instance());
    ChangeState(StatePlaying::Instance());

	return 0;
}

void Game::LoadFonts()
{
	defaultFont 	= new Font("DefaultFont", 	"assets/Inconsolata-Regular.ttf", 	12);
	menuTitleFont 	= new Font("MenuTitle", 	"assets/Inconsolata-Regular.ttf", 	36);
	menuOptionFont 	= new Font("MenuOption", 	"assets/Inconsolata-Regular.ttf", 	24);
	consoleFont 	= new Font("ConsoleFont", 	"assets/Inconsolata-Regular.ttf", 	16);

	fontList[0] = defaultFont;
	fontList[1] = menuTitleFont;
	fontList[2] = menuOptionFont;
	fontList[3] = consoleFont;
}

void Game::ChangeState(GameState* newState)
{
    while (!_stateStack.empty())
    {
        //_stateStack.back()->Cleanup();
        _stateStack.pop_back();
    }

	if (newState != nullptr)
	{
		GameStateType type = newState->GetType();
		switch(type)
		{
			case GameStateType::MAIN_MENU:
				// Create buttons here???
				// Probably not, do that in main menu state class...
				break;

			case GameStateType::PLAYING_GAME:
				break;

			case GameStateType::LEVEL_EDITOR:
				break;

			default:
				//std::cerr << "ERROR: Trying to change to error state" << std::endl;
				//_stateStack.push_back(StateUninitialized::Instance());
				break;
		}

		_stateStack.push_back(newState);
	}
}

void Game::PushState(GameState* newState)
{
    _stateStack.push_back(newState);
}

void Game::PopState()
{
    //_stateStack.back()->Cleanup();
    _stateStack.pop_back();
}

bool Game::GetInput()
{
	// For the method, assume we are continuing
	//bool continueGame = true;

	int event_response = -1;

	// Poll the system for an event of some kind
	while (SDL_PollEvent(&_event))
	{
		// STEP 1: Process Input

		// This will allow the topmost gamestate to handle any events given to the window
		// (Preventing lower gamestates from taking input i.e. when a pause menu overlay is up)
		std::vector<GameState*>::iterator it = _stateStack.end();
		it--;
		event_response = (*it)->HandleEvents(&_event);

		if (event_response != -1)
		{
			switch (event_response)
			{
			case CLOSE_MENU:
				//std::cout << "Closing menu..." << std::endl;
				if ((*it)->GetType() == GameStateType::PAUSE_MENU) {
					//_stateStack.back()->Cleanup();
					_stateStack.pop_back();
					_stateStack.back()->Resume();
				}
				break;

			case OPEN_MENU:
				//std::cout << "Opening menu..." << std::endl;
				if ((*it)->GetType() == GameStateType::PLAYING_GAME) {
				// @todo: reimplement pause as boolean in game state class, to stop processing updates (but continue updating the display
					(*it)->Pause();
					PushState(StatePauseMenu::Instance());
					StatePauseMenu::Instance()->SetSelectedOption(0);
					StatePauseMenu::Instance()->ChangeMenuOption("Edit", 2);
					//StatePauseMenu::Instance()->RemoveMenuOption(2);
				}

				if ((*it)->GetType() == GameStateType::LEVEL_EDITOR) {
				// @todo: reimplement pause as boolean in game state class, to stop processing updates (but continue updating the display
					(*it)->Pause();
					PushState(StatePauseMenu::Instance());
					StatePauseMenu::Instance()->SetSelectedOption(0);
					StatePauseMenu::Instance()->ChangeMenuOption("Play", 2);
					//StatePauseMenu::Instance()->RemoveMenuOption(2);
				}
				break;

			case LEVEL_EDITOR:
				{
					//std::cout << "Changing to level editor..." << std::endl;
					ChangeState(StateEditor::Instance());

					Level* temp = StatePlaying::Instance()->GetLevel();
					if (temp != nullptr) {
						StateEditor::Instance()->SetLevel(temp->GetFileName());
					}

					StateEditor::Instance()->Resume(); 
				}
				break;

			case PLAY_MODE:
				//std::cout << "Changing back to play mode..." << std::endl;
				ChangeState(StatePlaying::Instance());

				StatePlaying::Instance()->ChangeLevel(StateEditor::Instance()->GetLevel());
				StatePlaying::Instance()->Resume(); 
				break;

			case RESTART:
				StatePlaying::Instance()->Restart();
				StateEditor::Instance()->ResetLevel();
if ((*it)->GetType() == GameStateType::PAUSE_MENU) {
					//_stateStack.back()->Cleanup();
					_stateStack.pop_back();
					_stateStack.back()->Resume();
				}
				break;

			//case CLOSE_CONSOLE: 
			//	CloseConsole();
			//	break;

			case GAME_QUIT:
			  QuitGame();
				break;

			default:
				std::cout << "Error: Unimplemented key event detected..." << std::endl;
				break;
			}
		}

		// If our event is a keyboard button press
		if (_event.type == SDL_KEYDOWN)
		{
			switch (_event.key.keysym.sym)
			{
			case SDLK_BACKQUOTE:
				//std::cout << "Pressed backquote! ";
				if (_stateStack.back()->GetType() == GameStateType::CONSOLE)
				{
					//std::cout << "Console open, closing... " << std::endl;
					//StateConsole::Instance()->Close();
				}
				else
				{
					PushState(StateConsole::Instance());
					//std::cout << "Console closed, opening ";
					if (_event.key.keysym.mod & KMOD_LSHIFT)
					{
						//std::cout << "big..." << std::endl;
						StateConsole::Instance()->Open(true);
					}
					else
					{
						//std::cout << "small..." << std::endl;
						StateConsole::Instance()->Open(false);
					}
				}

			default:
				break;
			}
		}
		else if (_event.type == SDL_WINDOWEVENT && _event.window.windowID == SDL_GetWindowID(_mainWindow))
		{
			switch ((int)(_event.window.event))
			{
			case SDL_WINDOWEVENT_CLOSE:
			  // If window is closed, take this as the user quitting
			  // In the future, this must be made more elegant.
			  //std::cout << "Close window event" << std::endl;
			  QuitGame();
			  break;
			default:
				//std::cout << (int)(_event.window.event);
				break;
			}
		}

	}
	// The player has not quit the game, so return false
	return _playing;
}

void Game::Update()
{
  // STEP 2: Update
  if (!_stateStack.empty())
    {
        std::vector<GameState*>::iterator it = _stateStack.begin();

        while (it != _stateStack.end())
        {
            (*it)->Update();
			it++;
        }
    }

	// Check console (if we have it open) if it should be closed
	if (_stateStack.back()->GetType() == GameStateType::CONSOLE && StateConsole::Instance()->IsClosed())
		CloseConsole();

    // deprecated ***
	//_entities.UpdateAll();
}

void Game::Render(float interpolation)
{
	// STEP 3: Render
    SDL_SetRenderDrawColor(_mainRenderer, 200, 200, 200, 255);

	// Clear the renderer to the set color
	SDL_RenderClear(_mainRenderer);

    if (!_stateStack.empty())
    {
        std::vector<GameState*>::iterator it = _stateStack.begin();

        while (it != _stateStack.end())
        {
            (*it)->Render(interpolation);
            it++;
        }
    }

    // deprecated ***
	//_entities.RenderAll(interpolation);

	// Draw (present) the renderer to the screen
	SDL_RenderPresent(_mainRenderer);
}

EntityCollection& Game::Entities()
{
	return _entities;
}

void Game::CloseConsole()
{
	if (_stateStack.back()->GetType() == GameStateType::CONSOLE)
	{
		//std::cout << "Closing console..." << std::endl;
		_stateStack.pop_back();
		_stateStack.back()->Resume();

		if (SDL_IsTextInputActive())
		{
			std::cout << "Stopping text input..." << std::endl;
			SDL_StopTextInput();
		}
	}
}

void Game::QuitGame()
{
	_playing = false;
}
