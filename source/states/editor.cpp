#include "states/editor.h"
#include "drawing.h"
#include "constants.h"
#include "player.h"
#include "ball.h"
#include "wall.h"

#include <iostream>

#define ClassName StateEditor

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{

}

void ClassName::Initialize()
{
	_levelName = "";

	// Set editing values
	_drawGrid = true;
	_gridSize = 32;
	_entityType = EditorEntityType::PLAYER;

	_isCreating = false;
	_isDeleting = false;

	_drawType = true;
	_textType.SetFont(defaultFont);
	_textType.SetPosition(8, 8);
	Entities().AddEntity(&_textType);
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

			// DEBUG!!!!
			// Get level string somehow...?
			// @todo: time for console?
			std::getline(std::cin, level);

			SetLevel(level);
			break;
		}
	}

	else if (event->type == SDL_MOUSEBUTTONDOWN && 
			event->button.clicks == 1)
	{
		if (event->button.button == SDL_BUTTON_LEFT) {
			_isCreating = true;
			if (_isDeleting) _isDeleting = false;	
		}
		else if (event->button.button == SDL_BUTTON_RIGHT) {
			_isDeleting = true;
			if (_isCreating) _isCreating = false;	
		}
	}
	else if (event->type == SDL_MOUSEBUTTONUP &&
			event->button.clicks == 1) 
	{
		if (event->button.button == SDL_BUTTON_LEFT) {
			_isCreating = false;
		}
		else if (event->button.button == SDL_BUTTON_RIGHT) {
			_isDeleting = false;
		}
	}

	else if (event->type == SDL_MOUSEWHEEL)
	{
		if (event->wheel.y < 0)
		{
			_entityType = static_cast<EditorEntityType>((static_cast<int>(_entityType)) + 1);	

			if (static_cast<int>(_entityType) >= static_cast<int>(EditorEntityType::Count))
				_entityType = static_cast<EditorEntityType>(0);
		}
		else if (event->wheel.y > 0)
		{
			_entityType = static_cast<EditorEntityType>((static_cast<int>(_entityType)) - 1);	

			if (static_cast<int>(_entityType) < 0)
				_entityType = static_cast<EditorEntityType>(static_cast<int>(EditorEntityType::Count) - 1);
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

		if (_isCreating || _isDeleting) {
			int x, y;

			SDL_GetMouseState(&x, &y);
			
			x = x - (x % _gridSize);
			y = y - (y % _gridSize);

			if (_isCreating) {

				//std::cout << _currentLevel.CheckPoint(x, y) << std::endl;
				if (_currentLevel.CheckPoint(x, y) == true) {
					// Delete the existing entity at this location
					_currentLevel.RemoveEntity(x, y);
				}

				// Try to create ball at coords.
				// @todo: find a way to select the entity we want to create...
				//////////////////////
				//
				// Entity Selection
				//
				//////////////////////
				Entity* obj = nullptr;

				switch (_entityType)
				{
					case EditorEntityType::PLAYER:
						obj = new Player();
						break;

					case EditorEntityType::BALL:
						obj = new Ball();
						break;

					case EditorEntityType::WALL:
						obj = new Wall();
						break;

					// Probably won't want to add text...
					//case EditorEntityType::TEXT:
					//	obj = new Text();
					//	std::string text;
					//	std::getline(std::cin, text);
					//	static_cast<Text*>(obj)->SetText(text);
					//	break;

					default:
						std::cout << "Error: Trying to add entity to level of invalid type (not in enum class)" << std::endl;
				}

				if (obj == nullptr) return;

				obj->SetPosition(x, y);

				// Breaks if we add to our own entity list, then try to load
				//_entities.AddEntity(ball);
				if (_levelName != "")
				{
					_currentLevel.AddEntity(obj);
				}

				// Debug
				//std::cout << _currentLevel.CheckPoint(x, y) << std::endl;
				//std::cout << "Count: " << _currentLevel.GetCount() << std::endl;
			}

			if (_isDeleting) {

				//std::cout << _currentLevel.CheckPoint(x, y) << std::endl;
				if (_currentLevel.CheckPoint(x, y) == true) {
					// Delete the existing entity at this location
					_currentLevel.RemoveEntity(x, y);
				}
			}
		}
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

	if (_drawType)
	{
		switch (_entityType)
		{
			case EditorEntityType::PLAYER:
				_textType.SetText("Player");				
				break;

			case EditorEntityType::BALL:
				_textType.SetText("Ball");				
				break;

			case EditorEntityType::WALL:
				_textType.SetText("Wall");
				break;

			default:
				_textType.SetText("Invalid");
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

	std::cout << "Setting editor level to " << name << "..." << std::endl;

	if (_levelName != "") {
		_currentLevel.SetFileName(name);
		LoadLevel();
	}
}

void ClassName::SetLevel(Level* level)
{
	std::cout << "Setting editor level to " << level->GetFileName() << "..." << std::endl;
}

std::string ClassName::GetLevel()
{
	return _levelName;
}

void ClassName::ResetLevel()
{
	_currentLevel.ClearEntities();
}

#ifdef ClassName
#undef ClassName
#endif
