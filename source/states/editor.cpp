#include "states/editor.h"
#include "drawing.h"
#include "constants.h"

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
			std::string level = "";

			// Get level string somehow...?
			// @todo: time for console?
			SetLevel(level);
			// @todo
			break;


		}
	}

	return -1;
}

void ClassName::Update()
{
	if (!IsPaused())
	{
		_entities.UpdateAll();
	}
}

void ClassName::Render(float interpolation)
{
	// We will render objects, but not update them
    _entities.RenderAll(interpolation);

	// Drawing grid
	if (_drawGrid)
	{
		for (int j = _gridSize; j < SCREEN_HEIGHT; j += _gridSize) {
			DrawLine(0, j, SCREEN_WIDTH, j, SDL_Color {50, 50, 50, 255});
		}
		for (int i = _gridSize; i < SCREEN_WIDTH; i += _gridSize) {
			DrawLine(i, 0, i, SCREEN_HEIGHT, SDL_Color {50, 50, 50, 255});
		}
	}
}

void ClassName::SaveLevel()
{
	if (_levelName != "")
		_currentLevel.SaveToFile();
}

bool ClassName::LoadLevel()
{
	if (_levelName != "")
		return _currentLevel.LoadFromFile();
	else
		return false;
}

void ClassName::SetLevel(std::string name)
{
	_levelName = name;

	if (_levelName != "")
		_currentLevel.SetFileName(name);
}

#ifdef ClassName
#undef ClassName
#endif
