#pragma once

#include "gameState.h"
#include "mineBoard.h"

#define ClassName StateMinesweeper

class StateMinesweeper :
	public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected:
	ClassName() {
		SetType(GameStateType::MINESWEEPER);
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

	void StartGame();
	void ResetBoard(int sizex, int sizey);

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

	MineBoard _mainBoard;
};

#ifdef ClassName
#undef ClassName
#endif
