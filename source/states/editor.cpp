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

	_drawType = true;

	_selectionTimer = 200;
	
	CreateUI();
}

void ClassName::Cleanup()
{

}

KeyEvent ClassName::HandleEvents(Event& event)
{
	// We don't want to update the objects we are editing
	_entities.HandleAllEvents(event);

	if (event.ev.type == SDL_KEYDOWN)
	{
		switch (event.ev.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (event.ev.key.repeat == 0)
				return KeyEvent::open_menu;
			break;

		// Mode Changing:
		case SDLK_q:
			if (!_primaryActive && !_secondaryActive)
				if (!Input::KeyHeld(SDLK_LSHIFT))
					_primaryMode = EditMode::CREATING;
				else
					_secondaryMode = EditMode::CREATING;
			break;

		case SDLK_w:
			if (!_primaryActive && !_secondaryActive)
				if (!Input::KeyHeld(SDLK_LSHIFT))
					_primaryMode = EditMode::DELETING;
				else
					_secondaryMode = EditMode::DELETING;
			break;

		case SDLK_e:
			if (!_primaryActive && !_secondaryActive)
				if (!Input::KeyHeld(SDLK_LSHIFT))
					_primaryMode = EditMode::MOVING;
				else
					_secondaryMode = EditMode::MOVING;
			break;

		case SDLK_r:
			if (!_primaryActive && !_secondaryActive)
				if (!Input::KeyHeld(SDLK_LSHIFT))
					_primaryMode = EditMode::SELECTING;
				else
					_secondaryMode = EditMode::SELECTING;
			break;

		// Show/hide grid (Maybe group with HUD one day)
		case SDLK_g:
			_drawGrid = !_drawGrid;
			break;

		// Show/hide HUD
		case SDLK_h:
			_drawHUD = !_drawHUD;
			break;

		case SDLK_DELETE:
			// Delete selected entities. Use while in case for breaks from deletions
		{
			auto iter = _levelEntities.begin();

			while (iter != _levelEntities.end()) {
				if (iter->_selected) {
					_currentLevel.RemoveEntity((*iter).entPtr);
					iter = _levelEntities.erase(iter);
				}
				else iter++; // Only increment in else, because deletion causes iter to go to next element anyways, possibly OOB
			}
		}
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
			(event.ev.button.clicks == 1 || event.ev.button.button == SDL_BUTTON_MIDDLE))
		{
			EditMode mode;
			bool valid = false;

			if (event.ev.button.button == SDL_BUTTON_LEFT && !_secondaryActive && !_cameraActive) {
				mode = _primaryMode;
				_primaryActive = true;
				valid = true;
			} 
			else if (event.ev.button.button == SDL_BUTTON_RIGHT && !_primaryActive && !_cameraActive) {
				mode = _secondaryMode;
				_secondaryActive = true;
				valid = true;
			}
			else if (event.ev.button.button == SDL_BUTTON_MIDDLE && !_primaryActive && !_secondaryActive) {
				_cameraActive = true;
				SDL_GetRelativeMouseState(nullptr, nullptr); // To reset the relative mouse values
			}

			if (valid) {
				switch (mode) {
				case EditMode::CREATING:
					_isCreating = true;
					break;

				case EditMode::DELETING:
					_isDeleting = true;
					break;

				case EditMode::MOVING:
					_isMoving = true;
					SDL_GetRelativeMouseState(nullptr, nullptr);
					_moveDiffx = 0;
					_moveDiffy = 0;
					break;

				case EditMode::SELECTING:
					_isSelecting = true;

					int mx, my;
					SDL_GetMouseState(&mx, &my);
					_selectionStart = ScreenToWorld(mx, my);
					break;
				}
			}
		}
		else if (event.ev.type == SDL_MOUSEBUTTONUP &&
			(event.ev.button.clicks == 1 || event.ev.button.button == SDL_BUTTON_MIDDLE))
		{
			EditMode *mode;
			bool valid = false;

			if (event.ev.button.button == SDL_BUTTON_LEFT && _primaryActive) {
				mode = &_primaryMode;
				_primaryActive = false;
				valid = true;
			}
			else if (event.ev.button.button == SDL_BUTTON_RIGHT && _secondaryActive) {
				mode = &_secondaryMode;
				_secondaryActive = false;
				valid = true;
			}
			else if (event.ev.button.button == SDL_BUTTON_MIDDLE && _cameraActive) {
				_cameraActive = false;
			}

			if (valid) {
				switch (*mode) {
				case EditMode::CREATING:
					_isCreating = false;
					break;

				case EditMode::DELETING:
					_isDeleting = false;
					break;

				case EditMode::MOVING:
					_isMoving = false;
					break;

				case EditMode::SELECTING:
					_isSelecting = false;

					int mx, my;
					SDL_GetMouseState(&mx, &my);

					vec2<int> real = ScreenToWorld(mx, my);

					SelectEntities(_selectionStart.x, _selectionStart.y, real.x - _selectionStart.x, real.y - _selectionStart.y);
					break;
				}
			}
		}
		else if (event.ev.type == SDL_MOUSEWHEEL)
		{
			// Currently using mousewheel to cycle entities for creation, but may be changed
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

	return KeyEvent::none;
}

void ClassName::Update()
{
	if (!IsPaused())
	{
		// Only updates entities local to editor, NOT _currentLevel's entities
		_entities.UpdateAll();

		if (_primaryActive || _secondaryActive) {
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
					EditorEnt editor_obj(obj);
					_currentLevel.AddEntity(obj);
					_levelEntities.push_back(editor_obj);
				}

				// Temporary, just to practice creation
				_isCreating = false; // @todo fix this stuff
			}

			else if (_isDeleting) {
				// @Cleanup Seems to be working, but may need to be checked on or refactored
				auto iter = _levelEntities.begin();

				while (iter != _levelEntities.end()) {
					Entity* ep = (*iter).entPtr;
					if (ep->ImageContainsPoint(vec2<int>{temp.x, temp.y})) {
						_currentLevel.RemoveEntity((*iter).entPtr);
						iter = _levelEntities.erase(iter);
					}
					else
						iter++;
				}
			}

			else if (_isMoving) {
				int mx, my;
				SDL_GetRelativeMouseState(&mx, &my);

				_moveDiffx += mx;
				_moveDiffy += my;

				int diff_amount_x = _moveDiffx / _gridSize;
				int diff_amount_y = _moveDiffy / _gridSize;

				if (diff_amount_x > 0 || diff_amount_x < 0 || diff_amount_y > 0 || diff_amount_y < 0) {
					for (auto it : _levelEntities) {
						if (it._selected) {
							it.entPtr->x += _gridSize * diff_amount_x;
							it.entPtr->y += _gridSize * diff_amount_y;
						}
					}

					_moveDiffx %= _gridSize;
					_moveDiffy %= _gridSize;
				}
			}
		}
		else if (_cameraActive) {
			int mx, my;
			SDL_GetRelativeMouseState(&mx, &my);

			globalCam->Move(-mx, -my);
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

	// Draw level entities that aren't hidden
	for (auto it : _levelEntities) {
		Entity *temp = it.entPtr;

		if (it._hidden) continue;

		if (temp != nullptr)
			temp->Render(interpolation, -globalCam->x(), -globalCam->y());
	
		if (it._selected)
			DrawRect(temp->x - temp->image()->origin.x - globalCam->x(), temp->y - temp->image()->origin.y - globalCam->y(), 
					 temp->image()->width(), temp->image()->height(), 
					 SDL_Color { 255, 255, 255, static_cast<Uint8>(_selectionTimer) });

	}

	// Render editor objects (like panels)
	if (_drawHUD)
		_entities.RenderAll(interpolation, -globalCam->x(), -globalCam->y());

	// Draw object type
	if (_drawHUD && _drawType)
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
		DrawRect(_selectionStart.x - globalCam->x(), _selectionStart.y - globalCam->y(), real.x - _selectionStart.x, real.y - _selectionStart.y, SDL_Color{ 255, 0, 0, 255 }, false);
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

		if (!result)
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
	std::cout << "Setting editor level to " << level->GetFileName() << "... (NOT IMPLEMENTED)" << std::endl;
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
	// Variables for accurate entity selection boxes
	int tx, ty, tw, th;

	// This is used to add to a selection (possible remove from later)
	bool add_to_selection		= Input::KeyHeld(SDLK_LSHIFT);
	bool remove_from_selection	= Input::KeyHeld(SDLK_LCTRL);

	// If we do a click-select, we only want to select a single entity under the mouse cursor
	bool found_one = false;

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
			(!big_box && ContainsPoint({ ox, oy }, { ow, oh }, { tx, ty }) && !found_one && it._selected == remove_from_selection))
		{
			// If we're removing, make sure we get this object out of selection
			if (remove_from_selection)
				it._selected = false;
			else
				it._selected = true;

			found_one = true;

		} else if (!add_to_selection && !remove_from_selection) {
			it._selected = false;
		}
	}
}

#ifdef ClassName
#undef ClassName
#endif
