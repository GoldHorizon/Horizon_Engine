#pragma once

#include "../gameState.h"

class StateUninitialized:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected: 
    StateUninitialized() {SetType(GameStateType::UNINITIALIZED);}
public:
    ~StateUninitialized();
	/*
	 * Class Methods
	 */
    void Initialize();
    void Cleanup();

    void Pause();
    void Resume();

    void HandleEvents();
    void Update();
    void Render(float interpolation);

    static StateUninitialized* Instance()
    {
        if (_thisInstance == nullptr)
        {
            _thisInstance = new StateUninitialized;
        }
        _thisInstance->Initialize();
        return _thisInstance;
    }

private:
    static StateUninitialized* _thisInstance;
};
