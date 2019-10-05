#include "../../include/states/pauseMenu.h"
#include "globals.h"
#include "enumerations.h"
#include "constants.h"
#include "drawing.h"

#include <iostream>
#include <string>

#define ClassName StatePauseMenu

ClassName::~ClassName()
{
	Cleanup();
}

void ClassName::Initialize()
{
	for (int i = 0; i < MENU_SIZE; i++)
		_menuList[i] = nullptr;

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

	//Text* menuOptionResume = CreateText("Resume", menuOptionFont, { SCREEN_WIDTH / 2, 320 - 32 }, SDL_Color({255, 255, 255, 255}), ALIGN_CENTER);
	//Text* menuOptionRestart = CreateText("Restart", menuOptionFont, { SCREEN_WIDTH / 2, 320 }, SDL_Color({255, 255, 255, 255}), ALIGN_CENTER);
	//// Dev option: Level editor
	//Text* menuOptionEdit = CreateText("Edit", menuOptionFont, { SCREEN_WIDTH / 2, 320 + 32 }, SDL_Color({255, 255, 255, 255}), ALIGN_CENTER);
	//Text* menuOptionOptions = CreateText("Options", menuOptionFont, { SCREEN_WIDTH / 2, 320 + 64 }, SDL_Color({255, 255, 255, 255}), ALIGN_CENTER);
	//Text* menuOptionQuit = CreateText("Quit", menuOptionFont, { SCREEN_WIDTH / 2, 320 + 96 }, SDL_Color({255, 255, 255, 255}), ALIGN_CENTER);

	//_entities.AddEntity(menuOptionResume);
	//_entities.AddEntity(menuOptionRestart);
	//_entities.AddEntity(menuOptionEdit);
	//_entities.AddEntity(menuOptionOptions);
	//_entities.AddEntity(menuOptionQuit);

	//_menuList[0] = menuOptionResume;
	//_menuList[1] = menuOptionRestart;
	//_menuList[2] = menuOptionEdit;
	//_menuList[3] = menuOptionOptions;
	//_menuList[4] = menuOptionQuit;
	
	auto menuTitle = CreateText("Menu", menuTitleFont, { SCREEN_WIDTH / 2, 160 }, SDL_Color({255, 255, 0, 255}), ALIGN_CENTER);
	auto menuPtr = std::make_unique<Text>(*menuTitle);

	_entities.AddEntity(std::move(menuPtr));

	AddMenuOption("Resume");
	AddMenuOption("Restart");
	AddMenuOption("Edit");
	AddMenuOption("Options");
	AddMenuOption("Quit");

	_menuOptionSelected = 0;
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

KeyEvent ClassName::HandleEvents(Event& event)
{
	if (event.ev.type == SDL_KEYDOWN)
	{
		//std::cout << std::to_string(event.ev.key.timestamp) << "   " << std::to_string(event.ev.key.repeat) << std::endl;
		switch (event.ev.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (event.ev.key.repeat == 0)
				return KeyEvent::close_menu;
			break;

		case SDLK_DOWN:
			_menuOptionSelected++;
			if (_menuOptionSelected >= MENU_SIZE) _menuOptionSelected -= MENU_SIZE;
			while (_menuList[_menuOptionSelected] == nullptr) {
				_menuOptionSelected++;
				if (_menuOptionSelected >= MENU_SIZE) _menuOptionSelected -= MENU_SIZE;
			}
			//std::cout << "Menu Option Selected: " << _menuOptionSelected << std::endl;
			UpdateMenu();
			break;

		case SDLK_UP:
			_menuOptionSelected--;
			if (_menuOptionSelected < 0) _menuOptionSelected += MENU_SIZE;
			while (_menuList[_menuOptionSelected] == nullptr) {
				_menuOptionSelected--;
				if (_menuOptionSelected < 0) _menuOptionSelected += MENU_SIZE;
			}
			//std::cout << "Menu Option Selected: " << _menuOptionSelected << std::endl;
			UpdateMenu();
			break;

		case SDLK_RETURN:
			switch (_menuOptionSelected)
			{
			case 0:
				return KeyEvent::close_menu;
				break;

			case 1:
				// Send signal to game to restart current level
				return KeyEvent::restart;
				break;

			case 2:
				// Send signal to game to open level editor
				if (_menuList[_menuOptionSelected]->text() == "Edit")
					return KeyEvent::level_editor;
				if (_menuList[_menuOptionSelected]->text() == "Play")
					return KeyEvent::play_mode;
				break;

			case 3:
				// Send signal to game to open options menu
				return KeyEvent::options_menu;
				break;

			case 4:
				// Send signal to game to exit the game!
				return KeyEvent::game_quit; 
				break;


			}
		}
	}

	return KeyEvent::none;
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
		if (_menuList[i] == nullptr)
			continue;

		if (_menuOptionSelected == i)
		{
			_menuList[i]->color = (SDL_Color({0, 255, 255, 255}));
			_menuList[i]->UpdateImage();
		}
		else
		{
			_menuList[i]->color = (SDL_Color({255, 255, 255, 255}));
			_menuList[i]->UpdateImage();
		}
	}

	// Debug to show selected option...
	//Text* menuOptionSelected = CreateText("Test", menuTitleFont, { SCREEN_WIDTH / 4, 160 }, SDL_Color({255, 255, 0, 255}));
	//_entities.AddEntity(menuOptionSelected);
	//std::cout << _entities.GetCount() << std::endl;

	//for (int i = 0; i < _entities.GetCount(); i++)
	//{
	//	std::cout << _entities[i] << static_cast<Text*>(_entities[i])->text() << std::endl;
	//}

}

void ClassName::Render(float interpolation)
{
	DrawRect({128, 128, SCREEN_WIDTH - 256, SCREEN_HEIGHT - 256}, {0, 80, 80, 255});

	// For testing
	//DrawRect(0, 0, 32, 32, 255, 0, 0, 255);

    _entities.RenderAll(interpolation);
}

void ClassName::AddMenuOption(std::string option, int pos)
{
	int index = pos;

	if (index == -1)
	{
		index = 0;
		while (_menuList[index] != nullptr && index < MENU_SIZE)
			index++;
	}
	else
	{
		index = pos;
	}

	if (index < 0 || index >= MENU_SIZE)
	{
		std::cout << "Error: invalid index (menu list is full?)" << std::endl;
		return;
	}

	Text* menuOption = CreateText(option, menuOptionFont, { SCREEN_WIDTH / 2, 320 - 32 + (index * 32) }, SDL_Color({255, 255, 255, 255}), ALIGN_CENTER);
	std::unique_ptr<Entity> menuPtr = std::make_unique<Text>(*menuOption);

	//std::cout << "Adding Entity..." << std::endl;
	_entities.AddEntity(std::move(menuPtr));
	//std::cout << "Adding MenuOption " << index << "..." << std::endl;
	_menuList[index] = menuOption;
	//std::cout << "Updating menu..." << std::endl;
	//std::cout << "Updating menu..." << std::endl;

	UpdateMenu();
}

void ClassName::ChangeMenuOption(std::string option, int pos)
{
	if (_menuList[pos] != nullptr && _menuList[pos]->text() == option)
		return;

	RemoveMenuOption(pos);
	AddMenuOption(option, pos);
}

void ClassName::RemoveMenuOption(std::string option)
{

}

void ClassName::RemoveMenuOption(int pos)
{
	if (pos < 0 || pos >= MENU_SIZE)
	{
		std::cout << "Error: Option position (for removal) is invalid!" << std::endl;
		return;
	}

	if (_menuList[pos] != nullptr)
	{
		Text* temp = _menuList[pos];

		//std::cout << "Trying to delete " << temp->text() << std::endl;
		_entities.RemoveByID(temp->ID);
		if (_menuList[pos] != nullptr)
		{
			_menuList[pos] = nullptr;
			//std::cout << "Successfully deleted it!?" << std::endl;

			UpdateMenu();
		}
	}
}

int ClassName::GetSelectedOption()
{
	return _menuOptionSelected;
}

void ClassName::SetSelectedOption(int pos)
{
	if (pos >= 0 && pos < MENU_SIZE) {
		_menuOptionSelected = pos;	
		UpdateMenu();
	}
	else {
		std::cout << "Error: Trying to set pause menu option to invalid option number (out of range)" << std::endl;
	}
}

#ifdef ClassName
#undef ClassName
#endif
