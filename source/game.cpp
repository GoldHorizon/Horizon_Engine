#include "game.h"
#include "globals.h"
#include "constants.h"
#include "enumerations.h"
#include "types.h"
#include "inputManager.h"
#include "drawing.h"

#include "states/playing.h"
#include "states/uninitialized.h"
#include "states/titleScreen.h"
#include "states/options.h"
#include "states/pauseMenu.h"
#include "states/editor.h"
#include "states/console.h"
#include "states/minesweeper.h"

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
    _stateStack.push_back(std::make_unique<StateUninitialized>());

	auto quit_game_command = [this](std::vector<std::string> args) { QuitGame(); };

	commands["quit"] = quit_game_command;
	commands["exit"] = quit_game_command;

	//commands["close"] = [this](sVector args) { CloseConsole(); };
}

Game::~Game()
{
	_varFile.CloseFile();

	TTF_Quit();
	SDL_Quit();
}

GameStatus Game::Initialize()
{
	// If the game was already initialized, there's a problem.
	//if (_state != GameState::UNINITIALIZED)
    if (_stateStack.empty() || (_stateStack.back()->GetType() != GameStateType::UNINITIALIZED))
   	{   
   		return GameStatus::error;
   	}
	// STEP 1
	// Initialize SDL using SDL_Init
	// Note: Using SDL_INIT_EVERYTHING slows startup considerably on 32-bit versions
	// Consider implementing startup of subsystems in threads?
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1)
	{
		// If it fails, output error message and quit
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return GameStatus::error;
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

	// Start up our camera before other stuff
	globalCam = new Camera();

	// STEP 2
	// Setup our main window with an SDL_Window pointer
	_mainWindow = SDL_CreateWindow("Main Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	// Check to make sure it properly created the window
	if (_mainWindow == nullptr)
	{
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		return GameStatus::error;
	}

	// STEP 3
	// Create a renderer for use with our mainWindow
	// The -1 is the 'index', which determines the rendering driver to use. -1 tells it to choose the first one it finds
	_mainRenderer = SDL_CreateRenderer(_mainWindow, -1, SDL_RENDERER_ACCELERATED);
	// Check to see that is created the renderer
	if (_mainRenderer == nullptr)
	{
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
		return GameStatus::error;
	}

	globalRenderer = _mainRenderer;

	// Set blend mode of the renderer, so we can use alpha
	SDL_SetRenderDrawBlendMode (_mainRenderer, SDL_BLENDMODE_BLEND);

	// Set resolution of renderer to window resolution, output if there's an error
	// NOTE - This error checking was not done in the tutorial; more for my own practice
	//		  Will refrain from doing too much error checking, only where appropriate
	if (SDL_RenderSetLogicalSize(_mainRenderer, SCREEN_WIDTH, SCREEN_HEIGHT) == -1)
	{
		std::cerr << "Failed to set renderer resolution: " << SDL_GetError() << std::endl;
		return GameStatus::error;
	}

	// If all is well, set the game state and return something besides -1
	//ChangeState(StateTitleScreen::Instance());
    ChangeState(GameStateType::PLAYING_GAME);

	//
	// COMMANDS
	//
	// Some game commands to be implemented
	commands["state"] = [this](std::vector<std::string> args) {
		if (args.size() > 0) 
		{
			for (size_t i = 0; i < args.size(); i++)
			{
				if (args[i] == "uninitialized") {
					ChangeState(GameStateType::UNINITIALIZED);
				}
				else if (args[i] == "playing") {
					ChangeState(GameStateType::PLAYING_GAME);
				}
				else if (args[i] == "editor") {
					ChangeState(GameStateType::LEVEL_EDITOR);
				}
				else if (args[i] == "minesweeper") {
					ChangeState(GameStateType::MINESWEEPER);
				}
				else break;

				GetState()->Pause();

				// @todo - reimplement console appearing back on top?
				//auto it = _stateStack.begin();
				//while ((*it)->GetType() != GameStateType::CONSOLE && _stateStack.size() > 0) {
				//	_stateStack.erase(it);
				//	it = _stateStack.begin();
				//}
			}
		}
	};

	//commands["level"] = [this](sVector args) {
	//	if (args.size() > 1) {
	//		StateConsole::Instance()->AddError("Command requires at most 1 argument!");
	//	}
	//	else {
	//		std::vector<GameState*>::iterator it = _stateStack.end();

	//		while (it != _stateStack.begin())
	//		{
	//			it--;
	//			if ((*it)->GetType() == GameStateType::PLAYING_GAME) {
	//				if (args.size() == 1) {
	//					StateConsole::Instance()->AddOutput("Changing played level");
	//					StatePlaying::Instance()->ChangeLevel(args[0]);
	//					return;
	//				} else {
	//					if (StatePlaying::Instance()->GetLevel() != nullptr)
	//						StateConsole::Instance()->AddOutput(StatePlaying::Instance()->GetLevel()->GetFileName());
	//					else
	//						StateConsole::Instance()->AddOutput("No level selected...");
	//				}

	//				return;
	//			} else if ((*it)->GetType() == GameStateType::LEVEL_EDITOR) {
	//				if (args.size() == 1) {
	//					StateConsole::Instance()->AddOutput("Changing edited level");
	//					StateEditor::Instance()->SetLevel(args[0]);
	//					return;
	//				} else {
	//					if (StateEditor::Instance()->GetLevel()->GetFileName() != "")
	//						StateConsole::Instance()->AddOutput(StateEditor::Instance()->GetLevel()->GetFileName());
	//					else
	//						StateConsole::Instance()->AddOutput("No level selected...");
	//				}

	//				return;
	//			}
	//		}

	//		StateConsole::Instance()->AddError("Not in a correct state to use command!");
	//	}
	//};

	//commands["list"] = [this](sVector args) {
	//	std::vector<GameState*>::iterator it = _stateStack.end();

	//	while (it != _stateStack.begin())
	//	{
	//		it--;

	//		StateConsole::Instance()->AddOutput(std::to_string(static_cast<int>((*it)->GetType())));
	//		for (int i = 0; i < (*it)->Entities().GetCount(); i++)
	//		{
	//			Entity* temp = (*it)->Entities().GetByIndex(i);

	//			StateConsole::Instance()->AddOutput("\t" + temp->name());
	//		}

	//		if ((*it)->GetType() == GameStateType::PLAYING_GAME)
	//		{
	//			StatePlaying* ptr = dynamic_cast<StatePlaying*>((*it));
	//			for (int i = 0; i < ptr->GetLevel()->GetCount(); i++)
	//			{
	//				Entity* temp = ptr->GetLevel()->GetByIndex(i);

	//				StateConsole::Instance()->AddOutput("  " + std::to_string(static_cast<int>(temp->x)) 
	//						+ " " + std::to_string(static_cast<int>(temp->y))
	//						+ " " + std::to_string(temp->ID)
	//						+ " " + std::to_string(static_cast<int>(temp->depth)));
	//			}
	//		}
	//	}
	//};
	//
	// END OF COMMANDS
	//
	
	// Test file stuff
	_varFile.OpenFile("variables.txt", true, false);

	return GameStatus::initialized;
}

void Game::LoadFonts()
{
	defaultFont 	= new Font("DefaultFont", 	"assets/Inconsolata-Regular.ttf", 	16);
	menuTitleFont 	= new Font("MenuTitle", 	"assets/Inconsolata-Regular.ttf", 	36);
	menuOptionFont 	= new Font("MenuOption", 	"assets/Inconsolata-Regular.ttf", 	24);
	consoleFont 	= new Font("ConsoleFont", 	"assets/Hack-Regular.ttf", 	16);

	fontList[0] = defaultFont;
	fontList[1] = menuTitleFont;
	fontList[2] = menuOptionFont;
	fontList[3] = consoleFont;
}

GameState* Game::ChangeState(GameStateType type)
{
    while (!_stateStack.empty())
    {
		PopState();
    }

	return PushState(type);
}

GameState* Game::PushState(GameStateType type)
{
	std::unique_ptr<GameState> newState = nullptr;
	//GameStateType type = newState->GetType();

	switch(type)
	{
	case GameStateType::MAIN_MENU: {
		// Create buttons here???
		// Probably not, do that in main menu state class...
		newState = std::make_unique<StateTitleScreen>();
		break;
	}

	case GameStateType::PAUSE_MENU: {
		
		newState = std::make_unique<StatePauseMenu>();
		break;
	}

	case GameStateType::PLAYING_GAME: {

		newState = std::make_unique<StatePlaying>();
		break;
	}

	case GameStateType::LEVEL_EDITOR: {

		newState = std::make_unique<StateEditor>();
		break;
	}

	case GameStateType::MINESWEEPER: {

		newState = std::make_unique<StateMinesweeper>();
		break;
	}

	default: {
		std::cerr << "ERROR: Trying to change to unimplemented state" << std::endl;
		//_stateStack.push_back(StateUninitialized::Instance());
	} 
	}

	if (newState) {
		auto statePtr = newState.get();
		_stateStack.push_back(std::move(newState));
		return statePtr;
	}

	return nullptr;
}

void Game::PopState()
{
    _stateStack.back()->Cleanup();
    _stateStack.pop_back();
}

GameState* Game::GetState(GameStateType type)
{
	if (type == GameStateType::NONE)
		return _stateStack.back().get();

	auto reverse_it = _stateStack.rbegin();

	while (reverse_it != _stateStack.rend()) {
		if ((*reverse_it)->GetType() == type) {
			return (*reverse_it).get();
		}
	}

	return nullptr;
}

GameStatus Game::GetInput()
{
	// For the method, assume we are continuing and that we have no input yet
	auto event_response = KeyEvent::none;
	auto report_status  = GameStatus::running;

	// Poll the system for an event of some kind
	while (Input::NextEvent(_event))
	{
		// STEP 1: Process Input

		// This will allow the topmost gamestate to handle any events given to the window
		// (Preventing lower gamestates from taking input i.e. when a pause menu overlay is up)
		if (_console.IsOpen()) {
			event_response = _console.HandleEvents(_event);
		}
		else {
			event_response = (_stateStack.back())->HandleEvents(_event);
		}

		switch (event_response)
		{
		case KeyEvent::close_menu:
			if (_stateStack.back()->GetType() == GameStateType::PAUSE_MENU) {
				PopState();
				_stateStack.back()->Resume();
			}
			break;

		case KeyEvent::open_menu:
			if (_stateStack.back()->GetType() == GameStateType::PLAYING_GAME) {
			// @todo: reimplement pause as boolean in game state class, to stop processing updates (but continue updating the display
				_stateStack.back()->Pause();

				StatePauseMenu* menu = dynamic_cast<StatePauseMenu*>(PushState(GameStateType::PAUSE_MENU));
				menu->SetSelectedOption(0);
				menu->ChangeMenuOption("Edit", 2);
			}

			else if (_stateStack.back()->GetType() == GameStateType::LEVEL_EDITOR) {
			// @todo: reimplement pause as boolean in game state class, to stop processing updates (but continue updating the display
				_stateStack.back()->Pause();

				StatePauseMenu* menu = dynamic_cast<StatePauseMenu*>(PushState(GameStateType::PAUSE_MENU));
				menu->SetSelectedOption(0);
				menu->ChangeMenuOption("Play", 2);
			}
			break;

		case KeyEvent::level_editor: {
			ChangeState(GameStateType::LEVEL_EDITOR);
			//ChangeState(StateEditor::Instance());

			//Level* temp = StatePlaying::Instance()->GetLevel();

			//if (temp != nullptr) {
			//	if (temp->GetFileName() != "")
			//		StateEditor::Instance()->SetLevel(temp->GetFileName());
			//}

			//StateEditor::Instance()->Resume(); 
		}
		break;

		case KeyEvent::play_mode: {
			ChangeState(GameStateType::PLAYING_GAME);

			//StatePlaying::Instance()->ChangeLevel(StateEditor::Instance()->GetLevel()->GetFileName());
			//StatePlaying::Instance()->Resume(); 
			break;
		}

		//case KeyEvent::restart:
		//	StatePlaying::Instance()->Restart();
		//	StateEditor::Instance()->ResetLevel();
		//	if ((*it)->GetType() == GameStateType::PAUSE_MENU) {
		//		// @check
		//		PopState();
		//		_stateStack.back()->Resume();
		//	}
		//	break;

		//// Not needed?!
		//case CLOSE_CONSOLE: 
		//	CloseConsole();
		//	break;

		case KeyEvent::game_quit:
			QuitGame();
			return GameStatus::stopped;
			break;

		case KeyEvent::none:
			// Do nothing
			break;
		default:
			std::cout << "Error: Unimplemented or invalid menu event detected..." << std::endl;
			break;
		}

		// If our event is a keyboard button press
		if (_event.ev.type == SDL_KEYDOWN)
		{
			switch (_event.ev.key.keysym.sym)
			{
			case SDLK_BACKQUOTE: 
			{
				if (_console.IsClosed()) {
					_stateStack.back()->Pause();

					//std::cout << "Console closed, opening ";
					if (_event.ev.key.keysym.mod & KMOD_LSHIFT)
					{
						//std::cout << "big..." << std::endl;
						_console.Open(true);
					}
					else
					{
						//std::cout << "small..." << std::endl;
						_console.Open(false);
					}
				}
			} break;

			}
		}
		else if (_event.ev.type == SDL_WINDOWEVENT && _event.ev.window.windowID == SDL_GetWindowID(_mainWindow))
		{
			switch ((int)(_event.ev.window.event))
			{
			case SDL_WINDOWEVENT_CLOSE:
			  // If window is closed, take this as the user quitting
			  // In the future, this must be made more elegant.
			  //std::cout << "Close window event" << std::endl;
			  QuitGame();
			  break;
			default:
				//std::cout << (int)(_event.ev.window.event);
				break;
			}
		}

	}

	// The player has quit the game, so return stopped
	if (!_playing)
		return GameStatus::stopped;

	// The player has not quit the game
	return report_status;
}

void Game::Update()
{
	// STEP 2: Update

	if (!_console.IsClosed())
		_console.Update();

	if (!_stateStack.empty() && _console.IsClosed())
		{
			// This will allow the topmost gamestate to handle any events given to the window
			// (Preventing lower gamestates from taking input i.e. when a pause menu overlay is up)
			//std::vector<GameState*>::iterator it = _stateStack.end();
			//it--;
			//(*it)->Update();

			auto it = _stateStack.begin();
			while (it != _stateStack.end())
			{
				if (!(*it)->IsPaused()) {
					(*it)->Update();
				}
				it++;
			}
		}

	// Check console (if we have it open) if it should be closed
	// @todo I DONT KNOW IF THIS LINE WORKS
	if (_console.IsClosed())
		CloseConsole();

	//	auto it = _stateStack.end();
	//	it--;
	//	(*it)->Resume();
	//}

	// Check if variables file is outdated, so we can hotload new variables
	if (_varFile.IsOutdated()) {
		std::cout << "File has changed! Begin hotloading..." << std::endl;
	}
}

void Game::Render(float interpolation)
{
	// STEP 3: Render
    SDL_SetRenderDrawColor(_mainRenderer, 200, 200, 200, 255);

	// Clear the renderer to the set color
	SDL_RenderClear(_mainRenderer);

    if (!_stateStack.empty())
    {
        auto it = _stateStack.begin();

        while (it != _stateStack.end())
        {
			if ((*it)->IsPaused()) {
				(*it)->Render(0);
			} else {
				(*it)->Render(interpolation);
			}
            it++;
        }
    }

	// Render the console
	_console.Render(interpolation);


	// Draw FPS in top right, mostly for debug right now
	DrawText("FPS:", TextQuality::SHADED, defaultFont, SCREEN_WIDTH - 80, 16, TextAlignment::ALIGN_LEFT, { 255, 255, 255, 255 });
	DrawText(std::to_string(currentFPS), TextQuality::SHADED, defaultFont, SCREEN_WIDTH - 16, 16, TextAlignment::ALIGN_RIGHT, { 255, 255, 255, 255 });

	// Draw (present) the renderer to the screen
	SDL_RenderPresent(_mainRenderer);
}

EntityCollection& Game::Entities()
{
	return _entities;
}

void Game::CloseConsole()
{
	_stateStack.back()->Resume();

	if (SDL_IsTextInputActive())
	{
		//std::cout << "Stopping text input..." << std::endl;
		SDL_StopTextInput();
	}

	_console.Close();
}

void Game::QuitGame()
{
	_playing = false;
}
