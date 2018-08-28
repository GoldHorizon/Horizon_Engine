#pragma once

#include "../gameState.h"
#include "level.h"

#include <vector>

#define ClassName StatePlaying

class StatePlaying:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected:
    ClassName() {
		SetType(GameStateType::PLAYING_GAME); 
		Resume(); 
	}
public:
    ~StatePlaying();
	/*
	 * Class Methods
	 */
    void Initialize();
    void Cleanup();

    int HandleEvents(SDL_Event*);
    void Update();
    void Render(float interpolation);

	void AddLevel(std::string name);
	void AddLevel(Level* level);

	void ChangeLevel(std::string name);
	
	Level* GetLevel();

	void Restart();

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

	std::vector<Level*> _levelList;
};

#ifdef ClassName
#undef ClassName
#endif
