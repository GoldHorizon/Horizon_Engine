#include "states/editor.h"
#include "drawing.h"
#include "constants.h"
#include "player.h"
#include "ball.h"
#include "wall.h"
#include "inputManager.h"
#include "engineMethods.h"
#include "panel.h"

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
	//_textType.SetFont(defaultFont);
	//_textType.SetPosition(8, 8);
	//Entities().AddEntity(&_textType);
	
	CreateUI();
}

void ClassName::Cleanup()
{

}

int ClassName::HandleEvents(Event& event)
{
	// We don't want to update the objects we are editing
	_entities.HandleAllEvents(event);

	if (event.ev.type == SDL_KEYDOWN)
	{
		switch (event.ev.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (event.ev.key.repeat == 0)
				return OPEN_MENU;
			break;
		case SDLK_SLASH:
			if (event.ev.key.repeat == 0)
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

		//case SDLK_F3:
		//	std::cout << "Changing level..." << std::endl;

		//	std::string level = "";

		//	// DEBUG!!!!
		//	// Get level string somehow...?
		//	// @todo: time for console?
		//	std::getline(std::cin, level);

		//	SetLevel(level);
		//	break;
		}
	}

	else if (event.ev.type == SDL_MOUSEBUTTONDOWN && 
			event.ev.button.clicks == 1)
	{
		if (event.ev.button.button == SDL_BUTTON_LEFT) {
			_isCreating = true;
		}
		else if (event.ev.button.button == SDL_BUTTON_RIGHT) {
			_isDeleting = true;
		}
	}
	else if (event.ev.type == SDL_MOUSEBUTTONUP &&
			event.ev.button.clicks == 1) 
	{
		if (event.ev.button.button == SDL_BUTTON_LEFT) {
			_isCreating = false;
		}
		else if (event.ev.button.button == SDL_BUTTON_RIGHT) {
			_isDeleting = false;
		}
	}

	else if (event.ev.type == SDL_MOUSEWHEEL)
	{
		if (event.ev.wheel.y < 0)
		{
			_entityType = static_cast<EditorEntityType>((static_cast<int>(_entityType)) + 1);	

			if (static_cast<int>(_entityType) >= static_cast<int>(EditorEntityType::Count))
				_entityType = static_cast<EditorEntityType>(0);
		}
		else if (event.ev.wheel.y > 0)
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

		// Temporary camera movement
		if (Input::KeyHeld(SDLK_h)) globalCam->Move(-4, 0);
		if (Input::KeyHeld(SDLK_j)) globalCam->Move(0, 4);
		if (Input::KeyHeld(SDLK_k)) globalCam->Move(0, -4);
		if (Input::KeyHeld(SDLK_l)) globalCam->Move(4, 0);

		if (_isCreating != _isDeleting) {
			int x, y;

			SDL_GetMouseState(&x, &y);

			vec2<int> temp = ScreenToWorld(x, y);

			x = temp.x - (temp.x % _gridSize);
			y = temp.y - (temp.y % _gridSize);

			if (temp.x < 0) x -= _gridSize;
			if (temp.y < 0) y -= _gridSize;

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
				if (_levelName != "")
				{
					_currentLevel.AddEntity(obj);
				}
			}

			if (_isDeleting) {
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
	// Drawing grid
	if (_drawGrid)
	{
		for (int j = _gridSize; j <= SCREEN_HEIGHT + _gridSize; j += _gridSize) {
			int temp;
			if (globalCam->y() >= 0)
				temp = (globalCam->y() % _gridSize);
			else
				temp = (_gridSize - (std::abs(globalCam->y()) % _gridSize));

			int yy = j - temp;
			DrawLine(0, yy, SCREEN_WIDTH, yy,  SDL_Color {180, 180, 180, 255});
		}

		for (int i = _gridSize; i <= SCREEN_WIDTH + _gridSize; i += _gridSize) {
			int temp;
			if (globalCam->x() >= 0)
				temp = (globalCam->x() % _gridSize);
			else
				temp = (_gridSize - (std::abs(globalCam->x()) % _gridSize));

			int xx = i - temp;
			DrawLine(xx, 0, xx, SCREEN_HEIGHT, SDL_Color {180, 180, 180, 255});
		}
	}

	// We will render objects, but not update them
    _entities.RenderAll(interpolation, -globalCam->x(), -globalCam->y());

	// Draw level entities, without updating them
	_currentLevel.RenderAll(interpolation, -globalCam->x(), -globalCam->y());

	// Draw object type
	if (_drawType)
	{
		std::string type_text = "";
		switch (_entityType)
		{
			case EditorEntityType::PLAYER:
				type_text = "Player";
				break;

			case EditorEntityType::BALL:
				type_text = "Ball";
				break;

			case EditorEntityType::WALL:
				type_text = "Wall";
				break;

			default:
				type_text = "Invalid";
		}
		//DrawText(type_text, defaultFont, 9, 9, TextAlignment::ALIGN_LEFT, {0, 0, 0, 255});
		DrawText(type_text, TextQuality::SHADED, defaultFont, 8, 8, TextAlignment::ALIGN_LEFT, {255, 255, 255, 255});
	}
}

void ClassName::SaveLevel()
{
	if (_levelName != "")
		_currentLevel.SaveLevel();

	// @todo: Save entities that were added to the _currentLevel's collection through the editor onto file.
}

bool ClassName::LoadLevel()
{
	if (_levelName != "") {
		bool result = false;

		result = _currentLevel.LoadLevel();

		if (result)
		{
			//std::cout << "Loaded level " << _levelName << std::endl;
		}
		else
		{
			std::cout << "Failed to load level " << _levelName << std::endl;
			std::cout << "Creating new level '" << _levelName << "'" << std::endl;

		}
		
		return result;
	} else { 
		std::cout << "Error: Cannot load empty level" << std::endl;
		return false; 
	}
}

void ClassName::SetLevel(std::string name)
{
	//std::cout << "Setting editor level to " << name << "..." << std::endl;

	if (name != "") {
		std::string oldLevel = _levelName;

		_currentLevel.SetFileName(name);
		_levelName = name;

		LoadLevel();

		//std::cout << "\tAbout to open level " << _levelName << std::endl;
		//if (!LoadLevel())
		//{
		//	_levelName = oldLevel;
		//}

	} else std::cout << "DEBUG trying to edit blank level" << std::endl;

	//std::cout << "DEBUG Level name: " << _levelName << std::endl;
}

void ClassName::SetLevel(Level* level)
{
	std::cout << "Setting editor level to " << level->GetFileName() << "..." << std::endl;
}

Level* ClassName::GetLevel()
{
	return &_currentLevel;
}

void ClassName::ResetLevel()
{
	_currentLevel.ClearEntities();
}

void ClassName::CreateUI()
{
	Panel* modeSelector = new Panel();
	modeSelector->SetPosition(64, 64);
	modeSelector->title = ("Mode");
	modeSelector->type = PanelType::FOCUS;
	_entities.AddEntity(modeSelector);
}

#ifdef ClassName
#undef ClassName
#endif
