#pragma once

#include "../gameState.h"

class StatePlaying:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected: 
    StatePlaying() {SetType(GameStateType::PLAYING_GAME);}
public:
    ~StatePlaying();
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

    static StatePlaying* Instance()
    {
        if (_thisInstance == nullptr)
        {
            _thisInstance = new StatePlaying;
        }
        _thisInstance->Initialize();
        return _thisInstance;
    }

private:
    static StatePlaying* _thisInstance;
};

