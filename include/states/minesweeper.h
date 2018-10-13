#pragma once

#include "gameState.h"
#include "mineBoard.h"

#define StateName StateMinesweeper

class StateMinesweeper :
	public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected:
	StateName() {
		SetType(GameStateType::MINESWEEPER);
		Resume();
	}
public:
	~StateName();

	/*
	 * Class Methods
	 */
    void Initialize();
    void Cleanup();

    int HandleEvents(SDL_Event*);
    void Update();
    void Render(float interpolation);

	void StartGame(int startx, int starty);
	void ResetBoard(int sizex, int sizey);

    static StateName* Instance()
    {
        if (_thisInstance == nullptr)
        {
            _thisInstance = new StateName;
        	_thisInstance->Initialize();
        }
        return _thisInstance;
    }

private:
    static StateName* _thisInstance;

	MineBoard _mainBoard;
};

#ifdef StateName
#undef StateName
#endif
