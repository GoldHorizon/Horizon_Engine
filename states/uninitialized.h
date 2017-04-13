#pragma once

#include "../gameState.h"

class StateUndef:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected: 
    StateUndef() {SetType(GameStateType::UNINITIALIZED);}
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
    void Render(float interpolation);

    static StateUndef* Instance()
    {
        if (_thisInstance == nullptr)
        {
            _thisInstance = new StateUndef;
        }
        _thisInstance->Initialize();
        return _thisInstance;
    }

private:
    static StateUndef* _thisInstance;
};
