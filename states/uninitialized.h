#pragma once

#include "../gameState.h"

class StateUninitialized:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected: 
    StateUninitialized() {}
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
    void Draw();

    static StateUninitialized* Instance()
    {
        if (_uninitializedInstance == nullptr)
        {
            _uninitializedInstance = new StateUninitialized;
        }
        return _uninitializedInstance;
    }

private:
    static StateUninitialized* _uninitializedInstance;
};
