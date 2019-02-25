#pragma once

#include "gameState.h"
#include "event.h"

#define ClassName StateUninitialized

class StateUninitialized:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
public:
    ClassName() {
		Initialize();
		SetType(GameStateType::UNINITIALIZED); 
		Resume();
	}
    ~StateUninitialized();
	/*
	 * Class Methods
	 */
    void Initialize();
    void Cleanup();

    KeyEvent HandleEvents(Event&);
    void Update();
    void Render(float interpolation);
};

#ifdef ClassName
#undef ClassName
#endif
