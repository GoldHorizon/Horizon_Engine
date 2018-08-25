#include "../../include/states/pauseMenu.h"
#include "globals.h"
#include "enumerations.h"
#include "constants.h"
#include "drawing.h"

#include <iostream>
#include <string>

#define ClassName StatePauseMenu

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{
	Cleanup();
}

void ClassName::Initialize()
{
	//Draw menu title
	//Text* menuTitle = new Text("Menu", menuTitleFont);
	//menuTitle->SetPosition({ SCREEN_WIDTH / 2, 160 });
	//menuTitle->SetColor(SDL_Color({255, 255, 0, 255}));
	//menuTitle->SetAlign(ALIGN_CENTER);
	//menuTitle->UpdateImage();

	//Draw menu options
	//Text* menuOptionResume = new Text("Resume", menuOptionFont);
	//menuOptionResume->SetPosition({ SCREEN_WIDTH / 2, 320 });
	//menuOptionResume->SetColor(SDL_Color({255, 255, 255, 255}));
	//menuOptionResume->SetAlign(ALIGN_CENTER);
	//menuOptionResume->UpdateImage();

	Text* menuTitle = CreateText("Menu", menuTitleFont, { SCREEN_WIDTH / 2, 160 }, SDL_Color({255, 255, 0, 255}), ALIGN_CENTER);
	Text* menuOptionResume = CreateText("Resume", menuOptionFont, { SCREEN_WIDTH / 2, 320 - 32 }, SDL_Color({255, 255, 255, 255}), ALIGN_CENTER);
	Text* menuOptionRestart = CreateText("Restart", menuOptionFont, { SCREEN_WIDTH / 2, 320 }, SDL_Color({255, 255, 255, 255}), ALIGN_CENTER);
	// Dev option: Level editor
	Text* menuOptionEdit = CreateText("Edit", menuOptionFont, { SCREEN_WIDTH / 2, 320 + 32 }, SDL_Color({255, 255, 255, 255}), ALIGN_CENTER);
	Text* menuOptionOptions = CreateText("Options", menuOptionFont, { SCREEN_WIDTH / 2, 320 + 64 }, SDL_Color({255, 255, 255, 255}), ALIGN_CENTER);
	Text* menuOptionQuit = CreateText("Quit", menuOptionFont, { SCREEN_WIDTH / 2, 320 + 96 }, SDL_Color({255, 255, 255, 255}), ALIGN_CENTER);

	_entities.AddEntity(menuTitle);
	_entities.AddEntity(menuOptionResume);
	_entities.AddEntity(menuOptionRestart);
	_entities.AddEntity(menuOptionEdit);
	_entities.AddEntity(menuOptionOptions);
	_entities.AddEntity(menuOptionQuit);
	
	_menuOptionSelected = 0;

	_menuList[0] = menuOptionResume;
	_menuList[1] = menuOptionRestart;
	_menuList[2] = menuOptionEdit;
	_menuList[3] = menuOptionOptions;
	_menuList[4] = menuOptionQuit;

	UpdateMenu();
}

void ClassName::Cleanup()
{
	while (_entities.GetCount() > 0)
	{
		_entities.RemoveByIndex(0);
	}
//  NOT NEEDED: the above takes care of all entities, INCLUDING items in the menu
//	for (int i = 0; i < MENU_SIZE; i++)
//		if (_menuList[i] != nullptr) delete _menuList[i];
}

int ClassName::HandleEvents(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		//std::cout << std::to_string(event->key.timestamp) << "   " << std::to_string(event->key.repeat) << std::endl;
		switch (event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (event->key.repeat == 0)
				return CLOSE_MENU;
			break;

		case SDLK_DOWN:
			_menuOptionSelected++;
			if (_menuOptionSelected >= MENU_SIZE) _menuOptionSelected -= MENU_SIZE;
			//std::cout << "Menu Option Selected: " << _menuOptionSelected << std::endl;
			UpdateMenu();
			break;

		case SDLK_UP:
			_menuOptionSelected--;
			if (_menuOptionSelected < 0) _menuOptionSelected += MENU_SIZE;
			//std::cout << "Menu Option Selected: " << _menuOptionSelected << std::endl;
			UpdateMenu();
			break;

		case SDLK_RETURN:
			switch (_menuOptionSelected)
			{
			case 0:
				return CLOSE_MENU;
				break;

			case 1:
				// Send signal to game to restart current level
				break;

			case 2:
				// Send signal to game to open level editor
				break;

			case 3:
				// Send signal to game to open options menu
				break;

			case 4:
				// Send signal to game to exit the game!
				return GAME_QUIT; 
				break;
			}
		}
	}

	return -1;
}

void ClassName::Update()
{
	if (!IsPaused())
		_entities.UpdateAll();
}

void ClassName::UpdateMenu()
{
	for (int i = 0; i < MENU_SIZE; i++)
	{
		if (_menuOptionSelected == i)
		{
			_menuList[i]->SetColor(SDL_Color({0, 255, 255, 255}));
			_menuList[i]->UpdateImage();
		}
		else
		{
			_menuList[i]->SetColor(SDL_Color({255, 255, 255, 255}));
			_menuList[i]->UpdateImage();
		}
	}
}

void ClassName::Render(float interpolation)
{
	DrawRect({128, 128, SCREEN_WIDTH - 256, SCREEN_HEIGHT - 256}, {0, 80, 80, 255});

	// For testing
	//DrawRect(0, 0, 32, 32, 255, 0, 0, 255);

    _entities.RenderAll(interpolation);
}

#ifdef ClassName
#undef ClassName
#endif
