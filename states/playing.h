#pragma once

#include "../gameState.h"

class StatePlaying:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected: 
    StatePlaying() {}
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
    void Draw();

    static StatePlaying* Instance()
    {
        if (_thisInstance == nullptr)
        {
            _thisInstance = new StatePlaying;
        }
        return _thisInstance;
    }

private:
    static StatePlaying* _thisInstance;
};

