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
#include <cassert>

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
	_isSelecting = false;

	_drawType = true;
	//_textType.SetFont(defaultFont);
	//_textType.SetPosition(8, 8);
	//Entities().AddEntity(&_textType);

	_selectionTimer = 200;
	
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
			break;

		case SDLK_F2:
			std::cout << "Loading level..." << std::endl;
			LoadLevel();
			break;

		case SDLK_F3:
			std::cout << "Switching to play mode..." << std::endl;
			//@todo
			break;

		}
	}

	else if (!event.blocked()) {
		if (event.ev.type == SDL_MOUSEBUTTONDOWN &&
			event.ev.button.clicks == 1)
		{
			if (event.ev.button.button == SDL_BUTTON_LEFT) {
				if (!_isDeleting) {
					_isSelecting = true;

					int mx, my;
					SDL_GetMouseState(&mx, &my);

					vec2<int> real = ScreenToWorld(mx, my);

					_selectionStart = { real.x, real.y };
				}
			}
			else if (event.ev.button.button == SDL_BUTTON_RIGHT) {
				if (!_isSelecting)
					_isDeleting = true;
			}
		}
		else if (event.ev.type == SDL_MOUSEBUTTONUP &&
			event.ev.button.clicks == 1)
		{
			if (event.ev.button.button == SDL_BUTTON_LEFT) {
				if (!_isDeleting)
					_isSelecting = false;

					int mx, my;
					SDL_GetMouseState(&mx, &my);

					SelectEntities(_selectionStart.x, _selectionStart.y, mx - _selectionStart.x, my - _selectionStart.y);
			}
			else if (event.ev.button.button == SDL_BUTTON_RIGHT) {
				if (!_isSelecting)
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

		if (_isCreating || _isDeleting || _isSelecting) {
			int mx, my;

			SDL_GetMouseState(&mx, &my);

			vec2<int> temp = ScreenToWorld(mx, my);

			if (_isCreating) {

				// For creating we will put the object on the grid 
				// (eventually check if we have grid turned on or not)
				mx = temp.x - (temp.x % _gridSize);
				my = temp.y - (temp.y % _gridSize);

				if (temp.x < 0) mx -= _gridSize;
				if (temp.y < 0) my -= _gridSize;

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

					default:
						std::cout << "Error: Trying to add entity to level of invalid type (not in enum class)" << std::endl;
				}

				if (obj == nullptr) return;

				obj->SetPosition(mx + obj->image()->origin.x, my + obj->image()->origin.y);

				// Breaks if we add to our own entity list, then try to load
				if (_levelName != "")
				{
					_currentLevel.AddEntity(obj);
				}

				// Temporary, just to practice creation
				_isCreating = false; // @todo fix this stuff
			}

			else if (_isDeleting) {
				// @Cleanup Seems to be working, but may need to be checked on or refactored
				auto iter = _levelEntities.begin();

				while (iter != _levelEntities.end()) {
					Entity* ep = (*iter).entPtr;
					if (ep->ImageContainsPoint(vec2<int>{mx, my})) {
						//std::cout << "MARKED FOR DELETION" << std::endl;
						//delete (*iter).entPtr; // @Cleanup Shouldn't this be outside of RemoveEntity??
						_currentLevel.RemoveEntity((*iter).entPtr);
						iter = _levelEntities.erase(iter);
					}
					else
						iter++;
				}

				//_currentLevel.RemoveEntities(mx, my);
			}

			// Don't need this, we don't actually do anything while selecting except draw the rectangle
			//else if (_isSelecting) {
			//	// @todo
			//}
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

	// Draw level entities, without updating them
	//_currentLevel.RenderAll(interpolation, -globalCam->x(), -globalCam->y());

	// Temp render code, testing
	//auto iter = _levelEntities.begin();

	//while (iter != _levelEntities.end()) {
	//	// Make sure we draw selected objects differently
	//	if ((*iter).entPtr != nullptr && !((*iter)._selected)) {
	//		(*iter).entPtr->Render(interpolation, -globalCam->x(), -globalCam->y());
	//	}
	//	if ((*iter)._selected) {
	//		DrawRect((*iter)
	//	}

	//	iter++;
	//}

	for (auto it : _levelEntities) {
		Entity *temp = it.entPtr;

		if (it._hidden) continue;

		if (temp != nullptr)
			temp->Render(interpolation, -globalCam->x(), -globalCam->y());
	
		if (it._selected)
			DrawRect(temp->x - temp->image()->origin.x, temp->y - temp->image()->origin.y, 
					 temp->image()->width(), temp->image()->height(), 
					 SDL_Color { 255, 255, 255, static_cast<Uint8>(_selectionTimer) });

	}

	// Render editor objects (like panels)
	_entities.RenderAll(interpolation, -globalCam->x(), -globalCam->y());

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

	// Draw selection boundaries
	if (_isSelecting) {
		int mx, my;

		SDL_GetMouseState(&mx, &my);
		vec2<int> real = ScreenToWorld(mx, my);
		DrawRect(_selectionStart.x, _selectionStart.y, real.x - _selectionStart.x, real.y - _selectionStart.y, SDL_Color{ 255, 0, 0, 255 }, false);
	}
}

void ClassName::SaveLevel()
{
	if (_levelName != "")
		_currentLevel.SaveLevel();
}

bool ClassName::LoadLevel()
{
	if (_levelName != "") {
		bool result = false;

		result = _currentLevel.LoadLevel();

		if (result)
		{
			//while (_levelEntities.size > 0) {
			//	_levelEntities.pop_back();
			//}

			//auto iter = _currentLevel.collection().begin();

			//while (iter != _currentLevel.collection().end()) {
			//	assert((*iter) != nullptr);

			//	_levelEntities.push_back(EditorEnt(*iter));
			//	iter++;
			//}
		}
		else
		{
			std::cout << "Couldn't load level... Creating new level '" << _levelName << "'" << std::endl;
			//AddOutput("Couldn't load  level, creating new one...");

		}

		while (_levelEntities.size() > 0) {
			_levelEntities.pop_back();
		}

		auto iter = _currentLevel.collection().begin();

		while (iter != _currentLevel.collection().end()) {
			assert((*iter) != nullptr);

			_levelEntities.push_back(EditorEnt(*iter));
			iter++;
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
	for (auto it = _levelEntities.begin(); it != _levelEntities.end(); it = _levelEntities.erase(it));

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

void ClassName::SelectEntities(int x, int y, int w, int h)
{
	int tx, ty, tw, th;

	// If we select in opposite direction, account for that
	if (w >= 0) {
		tx = x;
		tw = w;
	} else {
		tx = (x + w);
		tw = (w * -1);
	}

	if (h >= 0) {
		ty = y;
		th = h;
	} else {
		ty = (y + h);
		th = (h * -1);
	}

	// Loop through all entities, figure out which ones fall in this rectangle
	bool big_box = (tw > 3 || th > 3);

	for (EditorEnt &it : _levelEntities) {
		Entity *temp = it.entPtr;
		
		// Get entities real position/size due to offset
		int ox, oy, ow, oh;
		ox = static_cast<int>(temp->x - temp->image()->origin.x);
		oy = static_cast<int>(temp->y - temp->image()->origin.y);
		ow = temp->image()->width();
		oh = temp->image()->height();


		if ((big_box && ox >= tx
			&& oy >= ty
			&& (ox + ow) <= (tx + tw)
			&& (oy + oh) <= (ty + th))
			||
			(!big_box && ContainsPoint({ ox, oy }, { ow, oh }, { tx, ty })))
		{
			it._selected = true;
		} else {
			it._selected = false;
		}
	}
}

#ifdef ClassName
#undef ClassName
#endif
