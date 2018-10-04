#include "states/minesweeper.h"

#define ClassName StateMinesweeper

void ClassName::Initialize()
{
	_mainBoard.SetPosition(32, 32);
	_mainBoard.InitTestBoard(3, 3, 16, 16);
	_mainBoard.PrintTestBoard();
}

void ClassName::Cleanup()
{

}

int ClassName::HandleEvents(SDL_Event* event)
{
	_mainBoard.HandleEvents(event);
}

void ClassName::Update()
{

}

void ClassName::Render(float interpolation)
{
	//_mainBoard.Render(interpolation, -globalCam->x(), -globalCam->y());
	_mainBoard.Render(interpolation);
}

void ClassName::StartGame()
{

}

void ClassName::ResetBoard(int sizex, int sizey)
{

}

#ifdef ClassName
#undef ClassName
#endif

