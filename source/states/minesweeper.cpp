#include "states/minesweeper.h"
#include "engineMethods.h"

#define StateName StateMinesweeper

StateName* StateName::_thisInstance = nullptr;

StateName::~StateName()
{
	Cleanup();
}

void StateName::Initialize()
{
	_mainBoard.SetPosition(32, 32);
	//_mainBoard.InitTestBoard(3, 3, 16, 16);
	//_mainBoard.PrintTestBoard();
}

void StateName::Cleanup()
{

}

int StateName::HandleEvents(SDL_Event* event)
{
	//_mainBoard.HandleEvents(event);

	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
			case SDLK_r:
				//_mainBoard.InitTestBoard(3, 3, 16, 16);
				_mainBoard.CreateBoard(16, 16);
				_mainBoard.SetGenerated(false);
				_mainBoard.SetEnded(false);
				break;
		}
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN) 
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			// If the game has ended (due to win or loss) don't worry about clicking anything
			if (_mainBoard.ended() == true) return -1;

			int mx, my; 
			SDL_GetMouseState(&mx, &my);

			Vec2<int> coords = ScreenToWorld(mx, my);

			mx = coords.x;
			my = coords.y;

			mx -= static_cast<int>(_mainBoard.x());
			my -= static_cast<int>(_mainBoard.y());

			if (mx >= 0 && mx < _mainBoard.width() * 32 && my >= 0 && my < _mainBoard.height() * 32) {
				mx /= 32;
				my /= 32;

				//std::cout << mx << " " << my << std::endl;

				if (!_mainBoard.generated()) {
					_mainBoard.GenerateBombs(mx, my);
					_mainBoard.SetTileCounters();
					_mainBoard.SetGenerated(true);
				}

				_mainBoard.ClickTile(mx, my);
			}
		}
	}

	return -1;
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
	_mainBoard.SetGenerated(false);
	_mainBoard.SetEnded(false);

	_mainBoard.ClearBoard();
	_mainBoard.CreateBoard(sizex, sizey);
}

#ifdef StateName
#undef StateName
#endif

