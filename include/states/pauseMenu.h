#pragma once

#include "../gameState.h"

#define ClassName StatePauseMenu

class StatePauseMenu:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected:
    ClassName() {SetType(GameStateType::PAUSE_MENU); Resume();}
public:
    ~StatePauseMenu();
	/*
	 * Class Methods
	 */
    void Initialize();
    void Cleanup();

    int HandleEvents(SDL_Event*);
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
