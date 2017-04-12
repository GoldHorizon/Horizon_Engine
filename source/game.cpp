#include "../game.h"
#include <iostream>
#include "../globals.h"
#include "../constants.h"
#include "../TEMPball.h"

#include "../states/playing.h"
#include "../states/uninitialized.h"

Game::Game():
	_mainWindow(0),
	_mainRenderer(0)
	//_state(GameState::UNINITIALIZED)
{
	// Set the draw color for our renderer (rendered when renderer is cleared)
	SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);

    // Set our stack to only be uninitialized.
    // _stateStack.push(
    _stateStack.push_back(StateUninitialized::Instance());
}

Game::~Game()
{
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
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		// If it fails, output error message and quit
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	// STEP 2
	// Setup our main window with an SDL_Window pointer
	_mainWindow = SDL_CreateWindow("Main Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	// Check to make sure it properly created the window
	if (_mainWindow == nullptr)
	{
		std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
		return -1;
	}

	// STEP 3
	// Create a renderer for use with our mainWindow
	// The -1 is the 'index', which determines the rendering driver to use. -1 tells it to choose the first one it finds
	_mainRenderer = SDL_CreateRenderer(_mainWindow, -1, SDL_RENDERER_ACCELERATED);
	// Check to see that is created the renderer
	if (_mainRenderer == nullptr)
	{
		std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
		return -1;
	}

	globalRenderer = _mainRenderer;

	// Set resolution of renderer to window resolution, output if there's an error
	// NOTE - This error checking was not done in the tutorial; more for my own practice
	//		  Will refrain from doing too much error checking, only where appropriate
	if (SDL_RenderSetLogicalSize(_mainRenderer, SCREEN_WIDTH, SCREEN_HEIGHT) == -1)
	{
		std::cout << "Failed to set renderer resolution: " << SDL_GetError() << std::endl;
		return -1;
	}

	// If all is well, set the game state and return something besides -1
	ChangeState(StatePlaying::Instance());

	//TEMPball
	Ball* myBall = new Ball;
	Ball* myBall2 = new Ball;
	myBall->LoadFromFile("images/Paddle.png");
	myBall2->LoadFromFile("images/PlayButton.png");
	myBall->SetY(100);
	myBall2->SetY(200);
	myBall->SetImageOrigin(20, 20);

	_entities.AddEntity("ball", myBall);
	_entities.AddEntity("ball2", myBall2);

	return 0;
}

void Game::ChangeState(GameState* newState)
{
    while (!_stateStack.empty())
    {
        _stateStack.back()->Cleanup();
        _stateStack.pop_back();
    }

    GameStateType type = newState->GetType();
	switch(type)
	{
	case GameStateType::MAIN_MENU:
		// Create buttons here
		break;

    case GameStateType::PLAYING_GAME:
        _stateStack.push_back(StatePlaying::Instance());
        break;

	default:
        std::cerr << "ERROR: Trying to change to error state" << std::endl;
        _stateStack.push_back(StateUninitialized::Instance());
		break;
	}
}

bool Game::GetInput()
{
	// Poll the system for an event of some kind
	SDL_PollEvent(&_event);

	// STEP 1: Process Input

	// There will eventually be a switch statement here to
	// determine what game state we are in

	// If our event is a keyboard button press
	if (_event.type == SDL_KEYDOWN)
	{
		switch (_event.key.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			return false;
			break;
		default:
			break;
		}
	}
	else if (_event.type == SDL_WINDOWEVENT)
	{
		switch (_event.window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			// If window is closed, take this as the user quitting
			// In the future, this must be made more elegant.
			return false;
			break;
		default:
			break;
		}
	}

	// The player has not quit the game, so return false
	return true;
}

void Game::Update()
{
	// STEP 2: Update

	_entities.UpdateAll();
}

void Game::Render(float interpolation)
{
	// STEP 3: Render

	// Clear the renderer to the set color
	SDL_RenderClear(_mainRenderer);

	_entities.RenderAll(interpolation);

	// Draw (present) the renderer to the screen
	SDL_RenderPresent(_mainRenderer);
}

EntityCollection& Game::Entities()
{
	return _entities;
}
