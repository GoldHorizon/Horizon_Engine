#include "../header.h"

Game::Game():
	_mainWindow(0),
	_mainRenderer(0),
	_state(GameState::UNINITIALIZED)
{
	// Set the draw color for our renderer (rendered when renderer is cleared)
	SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);

	TEMP = nullptr;
}

Game::~Game()
{

}

int Game::Initialize()
{
	// If the game was already initialized, there's a problem.
	if (_state != GameState::UNINITIALIZED)
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
	ChangeState(GameState::MAIN_MENU);

	// TEMP
	TEMP = new Entity();
	TEMP->LoadFromFile("images/PlayButton.png");
	TEMP->SetOrigin(0, 0);
	TEMP->SetAngle(45);
	TEMP->SetPosition(100, 0);

	return 0;
}

void Game::ChangeState(GameState newState)
{
	switch(newState)
	{
	case GameState::MAIN_MENU:
		// Create buttons here
		break;
	default:
		break;
	}

	_state = newState;
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
			return true;
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
			return true;
			break;
		default:
			break;
		}
	}

	// The player has not quit the game, so return false
	return false;
}

void Game::Update(double elapsedTime)
{

	// STEP 2: Update


}

void Game::Render()
{
	// STEP 3: Render

	// Clear the renderer to the set color
	SDL_RenderClear(_mainRenderer);

	// TEMP
	TEMP->Render();

	// Draw (present) the renderer to the screen
	SDL_RenderPresent(_mainRenderer);
}
