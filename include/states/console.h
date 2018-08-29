#pragma once

#include "gameState.h"
#include "text.h"

#define ClassName StateConsole

class StateConsole:
	public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected:
    ClassName() {
		SetType(GameStateType::CONSOLE); 
		Resume();
	}
public:
    ~ClassName();

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
        	_thisInstance->Initialize();
        }
        return _thisInstance;
    }

private:
    static ClassName* _thisInstance;

};

#ifdef ClassName
#undef ClassName
#endif
