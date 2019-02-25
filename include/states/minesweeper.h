#pragma once

#include "gameState.h"
#include "mineBoard.h"

#define StateName StateMinesweeper

class StateMinesweeper :
	public GameState
{
public:
	/*
	 * Constructors/Destructors
	 */
	StateName() {
		SetType(GameStateType::MINESWEEPER);
		Resume();
	}
	~StateName();

	/*
	 * Class Methods
	 */
    void Initialize();
    void Cleanup();

    KeyEvent HandleEvents(Event&);
    void Update();
    void Render(float interpolation);

	void StartGame(int startx, int starty);
	void ResetBoard(int sizex, int sizey);

private:
	MineBoard _mainBoard;
};

#ifdef StateName
#undef StateName
#endif
