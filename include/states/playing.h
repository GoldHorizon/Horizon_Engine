#pragma once

#include <vector>

#include "gameState.h"
#include "level.h"
#include "camera.h"
#include "event.h"

#define ClassName StatePlaying

class StatePlaying:
    public GameState
{
	/*
	 * Constructors/Destructors
	 */
public:
    ClassName() {
		Initialize();
		SetType(GameStateType::PLAYING_GAME); 
		Resume(); 
	}
    ~StatePlaying();
	/*
	 * Class Methods
	 */
    void Initialize();
    void Cleanup();

    KeyEvent HandleEvents(Event&);
    void Update();
    void Render(float interpolation);

	void AddLevel(std::string name);
	void AddLevel(Level* level);

	void ChangeLevel(std::string name);
	
	Level* GetLevel();

	void Restart();

private:
	Level * _level;
};

#ifdef ClassName
#undef ClassName
#endif
