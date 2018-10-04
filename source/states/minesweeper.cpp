#include "states/minesweeper.h"

#define StateName StateMinesweeper

void StateName::Initialize()
{
	_mainBoard.SetPosition(32, 32);
	_mainBoard.InitTestBoard(3, 3, 16, 16);
	_mainBoard.PrintTestBoard();
}

void StateName::Cleanup()
{

}

int StateName::HandleEvents(SDL_Event* event)
{
	_mainBoard.HandleEvents(event);

	if (event->type == SDL_KEYDOWN)
	{

	}
}

void StateName::Update()
{

}

void StateName::Render(float interpolation)
{
	//_mainBoard.Render(interpolation, -globalCam->x(), -globalCam->y());
	_mainBoard.Render(interpolation);
}

void StateName::StartGame(int startx, int starty)
{

}

void StateName::ResetBoard(int sizex, int sizey)
{

}

#ifdef StateName
#undef StateName
#endif

