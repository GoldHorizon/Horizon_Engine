#pragma once

#include "event.h"
#include "gameState.h"

#define ClassName StateOptions

class StateOptions:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
public:
    ClassName() {
		Initialize();
		SetType(GameStateType::OPTIONS);
	}
    ~StateOptions();
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
