#pragma once

#include "../gameState.h"

class StateTitleScreen:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected:
    StateTitleScreen() {SetType(GameStateType::TITLE_SCREEN);}
public:
    ~StateTitleScreen();
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

    static StateTitleScreen* Instance()
    {
        if (_thisInstance == nullptr)
        {
            _thisInstance = new StateTitleScreen;
        }
        _thisInstance->Initialize();
        return _thisInstance;
    }

private:
    static StateTitleScreen* _thisInstance;
};
