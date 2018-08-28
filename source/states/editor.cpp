#include "states/editor.h"
#include "drawing.h"
#include "constants.h"
#include "ball.h"

#include <iostream>

#define ClassName StateEditor

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{

}

void ClassName::Initialize()
{
	// Set editing values
	_drawGrid = true;
	_gridSize = 32;

	_levelName = "";
}

void ClassName::Cleanup()
{

}

int ClassName::HandleEvents(SDL_Event* event)
{
	// We don't want to update the objects we are editing

	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (event->key.repeat == 0)
				return OPEN_MENU;
			break;
		case SDLK_SLASH:
			if (event->key.repeat == 0)
				_drawGrid = !_drawGrid;
			break;

		case SDLK_F1:
			std::cout << "Saving level..." << std::endl;
			SaveLevel();
			// @todo
			break;
		case SDLK_F2:
			std::cout << "Loading level..." << std::endl;
			LoadLevel();
			// @todo
			break;
		case SDLK_F3:
			std::cout << "Changing level..." << std::endl;

			// Get level string somehow...?
			// @todo: time for console?
			std::string level = "";

			// DEBUG!!!!
			std::getline(std::cin, level);

			SetLevel(level);
			break;


		}
	}

	else if (event->type == SDL_MOUSEBUTTONDOWN && 
			event->button.state == SDL_PRESSED &&
			event->button.clicks == 1)
	{
		int x = event->button.x;
		int y = event->button.y;

		x = x - (x % _gridSize);
		y = y - (y % _gridSize);

		if (event->button.button == SDL_BUTTON_LEFT) {

			std::cout << _currentLevel.CheckPoint(x, y) << std::endl;
			if (_currentLevel.CheckPoint(x, y) == true) {
				// Delete the existing entity at this location
				_currentLevel.RemoveEntity(x, y);
			}

			// Try to create ball at coords.
			Ball* ball = new Ball();
			ball->SetPosition(x, y);
			ball->SetName("ANUBALL");

			// Breaks if we add to our own entity list, then try to load
			//_entities.AddEntity(ball);
			if (_levelName != "")
			{
				_currentLevel.AddEntity(ball);
			}

			// Debug
			std::cout << _currentLevel.CheckPoint(x, y) << std::endl;
			std::cout << "Count: " << _currentLevel.GetCount() << std::endl;
		}
		else if (event->button.button == SDL_BUTTON_RIGHT) {

			std::cout << _currentLevel.CheckPoint(x, y) << std::endl;
			if (_currentLevel.CheckPoint(x, y) == true) {
				// Delete the existing entity at this location
				_currentLevel.RemoveEntity(x, y);
			}
		}
	}

	return -1;
}

void ClassName::Update()
{
	if (!IsPaused())
	{
		// Only updates entities local to editor, NOT _currentLevel's entities
		_entities.UpdateAll();

		// Put editor entity addition/deletion in here?







	}
}

void ClassName::Render(float interpolation)
{
	// We will render objects, but not update them
    _entities.RenderAll(interpolation);

	// Draw level entities, without updating them
	_currentLevel.RenderAll(interpolation);

	// Drawing grid
	if (_drawGrid)
	{
		for (int j = _gridSize; j < SCREEN_HEIGHT; j += _gridSize) {
			DrawLine(0, j, SCREEN_WIDTH, j, SDL_Color {180, 180, 180, 255});
		}
		for (int i = _gridSize; i < SCREEN_WIDTH; i += _gridSize) {
			DrawLine(i, 0, i, SCREEN_HEIGHT, SDL_Color {180, 180, 180, 255});
		}
	}
}

void ClassName::SaveLevel()
{
	if (_levelName != "")
		_currentLevel.SaveToFile();

	// @todo: Save entities that were added to the _currentLevel's collection through the editor onto file.
}

bool ClassName::LoadLevel()
{
	if (_levelName != "") {
		bool result = false;

		result = _currentLevel.LoadFromFile();

		if (result)
		{
			std::cout << "Loaded " << _levelName << std::endl;
		}
		
		return result;
	}
	else { return false; }
}

void ClassName::SetLevel(std::string name)
{
	_levelName = name;

	std::cout << "Setting level to " << name << "..." << std::endl;

	if (_levelName != "") {
		_currentLevel.SetFileName(name);
		LoadLevel();
	}
}

#ifdef ClassName
#undef ClassName
#endif
