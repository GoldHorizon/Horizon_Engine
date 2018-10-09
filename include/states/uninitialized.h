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
protected:
    ClassName() {SetType(GameStateType::UNINITIALIZED); Resume();}
public:
    ~StateUninitialized();
	/*
	 * Class Methods
	 */
    void Initialize();
    void Cleanup();

    int HandleEvents(Event&);
    void Update();
    void Render(float interpolation);

    static ClassName* Instance()
    {
        if (_thisInstance == nullptr)
        {
            _thisInstance = new ClassName;
        }
        _thisInstance->Initialize();
        return _thisInstance;
    }

private:
    static ClassName* _thisInstance;
};

#ifdef ClassName
#undef ClassName
#endif
