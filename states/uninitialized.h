#pragma once

#include "../gameState.h"

class StateUndef:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected: 
    StateUndef() {}
public:
    ~StateUndef();
	/*
	 * Class Methods
	 */
    void Initialize();
    void Cleanup();

    void Pause();
    void Resume();

    void HandleEvents();
    void Update();
    void Render();

    static StateUndef* Instance()
    {
        if (_uninitializedInstance == nullptr)
        {
            _uninitializedInstance = new StateUndef;
        }
        return _uninitializedInstance;
    }

private:
    static StateUndef* _uninitializedInstance;
};
