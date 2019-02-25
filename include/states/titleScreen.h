#pragma once

#include "gameState.h"
#include "event.h"

#define ClassName StateTitleScreen

class StateTitleScreen:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
public:
    ClassName() {
		Initialize();
		SetType(GameStateType::TITLE_SCREEN);
	}
    ~StateTitleScreen();
	/*
	 * Class Methods
	 */
    void Initialize();
    void Cleanup();

    void Pause();
    void Resume();

    KeyEvent HandleEvents(Event&);
    void Update();
    void Render(float interpolation);
};

#ifdef ClassName
#undef ClassName
#endif
