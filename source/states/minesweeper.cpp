#include "states/minesweeper.h"
#include "states/console.h"
#include "engineMethods.h"
#include "globals.h"

#define StateName StateMinesweeper

StateName::~StateName()
{
	Cleanup();
}

void StateName::Initialize()
{
	_mainBoard.SetPosition(32, 32);
	//_mainBoard.InitTestBoard(3, 3, 16, 16);
	//_mainBoard.PrintTestBoard();
	

	//
	// COMMANDS
	//
	//commands["mines"] = [this](sVector args) {
	//	bool showFlags = false;
	//	bool showBombs = false;
	//	bool showClicked = false;

	//	if (args.size() > 0) {
	//		if (args[0] == "all") {
	//			showFlags = true;
	//			showBombs = true;
	//			showClicked = true;
	//		} else if (args[0] == "flags") {
	//			showFlags = true;
	//		} else if (args[0] == "bombs") {
	//			showBombs = true;
	//		} else if (args[0] == "clicked") {
	//			showClicked = true;
	//		} //else StateConsole::Instance()->AddError("No valid argument! Use all, flags, bombs, or clicked");
	//	}

	//	if (showFlags) {
	//		//StateConsole::Instance()->AddOutput("---- List of flag tiles ----");	

	//		for (int j = 0; j < _mainBoard.height(); j++) {
	//			for (int i = 0; i < _mainBoard.width(); i++) {
	//				if (_mainBoard.GetTile(i, j).flagged())
	//					//StateConsole::Instance()->AddOutput("  " + std::to_string(i) + ", " + std::to_string(j));
	//					continue;
	//			}
	//		}
	//	}

	//	if (showBombs) {
	//		//StateConsole::Instance()->AddOutput("---- List of bomb tiles ----");	

	//		for (int j = 0; j < _mainBoard.height(); j++) {
	//			for (int i = 0; i < _mainBoard.width(); i++) {
	//				if (_mainBoard.GetTile(i, j).bomb())
	//					//StateConsole::Instance()->AddOutput("  " + std::to_string(i) + ", " + std::to_string(j));
	//					continue;
	//			}
	//		}
	//	}

	//	if (showClicked) {
	//		//StateConsole::Instance()->AddOutput("---- List of clicked tiles ----");	

	//		for (int j = 0; j < _mainBoard.height(); j++) {
	//			for (int i = 0; i < _mainBoard.width(); i++) {
	//				if (_mainBoard.GetTile(i, j).clicked())
	//					//StateConsole::Instance()->AddOutput("  " + std::to_string(i) + ", " + std::to_string(j));
	//			}
	//		}
	//	}
	//};
}

void StateName::Cleanup()
{

}

KeyEvent StateName::HandleEvents(Event& event)
{
	//_mainBoard.HandleEvents(event);

	if (event.ev.type == SDL_KEYDOWN)
	{
		switch (event.ev.key.keysym.sym)
		{
			case SDLK_r:
				//_mainBoard.InitTestBoard(3, 3, 16, 16);
				_mainBoard.CreateBoard(16, 16);
				break;
		}
	}
	else if (event.ev.type == SDL_MOUSEBUTTONDOWN) 
	{
		// If the game has ended (due to win or loss) don't worry about clicking anything
		if (_mainBoard.ended() == true) return KeyEvent::none;

		int mx, my; 
		SDL_GetMouseState(&mx, &my);

		vec2<int> coords = ScreenToWorld(mx, my);

		mx = coords.x;
		my = coords.y;

		mx -= static_cast<int>(_mainBoard.x);
		my -= static_cast<int>(_mainBoard.y);

		if (mx >= 0 && mx < _mainBoard.width() * 32 && my >= 0 && my < _mainBoard.height() * 32) {
			mx /= 32;
			my /= 32;
		}
		else return KeyEvent::none;

		if (event.ev.button.button == SDL_BUTTON_LEFT)
		{
			if (!_mainBoard.generated()) {
				_mainBoard.GenerateBombs(mx, my);
				_mainBoard.SetTileCounters();
			}

			_mainBoard.ClickTile(mx, my);
		}
		else if (event.ev.button.button == SDL_BUTTON_RIGHT)
		{
			if (_mainBoard.generated()) {
				_mainBoard.FlagTile(mx, my);
			}
		}
	}

	return KeyEvent::none;
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
	_mainBoard.ClearBoard();
	_mainBoard.CreateBoard(sizex, sizey);
}

#ifdef StateName
#undef StateName
#endif

