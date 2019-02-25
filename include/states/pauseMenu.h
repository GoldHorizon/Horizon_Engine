#pragma once

#include "gameState.h"
#include "text.h"
#include "event.h"

#define ClassName StatePauseMenu

const int MENU_SIZE = 5;

class StatePauseMenu:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
public:
    ClassName() {
		Initialize();
		SetType(GameStateType::PAUSE_MENU); 
		Resume();
	}
    ~StatePauseMenu();
	/*
	 * Class Methods
	 */
    void Initialize();
    void Cleanup();

    KeyEvent HandleEvents(Event&);
    void Update();
	void UpdateMenu();
    void Render(float interpolation);

	void AddMenuOption(std::string option, int pos = -1);
	void ChangeMenuOption(std::string option, int pos);
	void RemoveMenuOption(std::string option);
	void RemoveMenuOption(int pos);

	int GetSelectedOption();
	void SetSelectedOption(int pos);

private:
	Text* _menuList[MENU_SIZE];
	int _menuOptionSelected;

};

#ifdef ClassName
#undef ClassName
#endif
