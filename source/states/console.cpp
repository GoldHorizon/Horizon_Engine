#include "states/console.h"
#include "drawing.h"
#include "globals.h"

#define ClassName StateConsole

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{
	Cleanup();
}

void ClassName::Initialize()
{
	_isOpenBig = false;
	_isOpenSmall = false;

	_consoleColor = {0, 50, 50, 255};
	
	// This is a how open the console is in terms of pixels
	_openHeight = 0;
	// This is a fraction of the screen height;
	_openHeightBig = 0.7;	
	// This is a fraction of openHeight;
	_openHeightSmall = 0.4;
	// This is a fraction of how fast the console opens
	_openRate = 0.01;
}

void ClassName::Cleanup()
{

}

int ClassName::HandleEvents(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			_isOpenBig = false;
			_isOpenSmall = false;
			break;

		case SDLK_BACKQUOTE:
			if (_isOpenBig || _isOpenSmall)
			{
				_isOpenBig = false;
				_isOpenSmall = false;
			}
			else
			{
				Open(event->key.keysym.mod == KMOD_LSHIFT);
				//if (event->key.keysym.mod == KMOD_LSHIFT) {
				//	_isOpenBig = true;
				//	_isOpenSmall = false;
				//} else {
				//	_isOpenSmall = true;
				//	_isOpenBig = false;
				//}
			}
			break;
		}
	}

	if (IsClosed()) return CLOSE_CONSOLE;

	return -1;
}

void ClassName::Update()
{
	if (_isOpenBig || _isOpenSmall)
	{
		_openHeight += (SCREEN_HEIGHT * _openHeightBig) * _openRate;
		if (_isOpenBig)
		{
			if (_openHeight >  SCREEN_HEIGHT * _openHeightBig)
				_openHeight = (SCREEN_HEIGHT * _openHeightBig);
		}
		else if (_isOpenSmall)
		{
			if (_openHeight >  SCREEN_HEIGHT * _openHeightSmall)
				_openHeight = (SCREEN_HEIGHT * _openHeightSmall);
		}
	}
	else if (_openHeight > 0) {
		// Subtract open height until we get to 0.
		_openHeight -= (SCREEN_HEIGHT * _openHeightBig) * _openRate;

		if (_openHeight < 0) _openHeight = 0;
	}
}

void ClassName::Render(float interpolation)
{
	if (_isOpenBig || _isOpenSmall) {
		DrawRect(0, 0, SCREEN_WIDTH, _openHeight, _consoleColor);
	}
}

void ClassName::Open(bool big)
{
	if (big) {
		_isOpenBig = true;
		_isOpenSmall = false;
	} else {
		_isOpenSmall = true;
		_isOpenBig = false;
	}
}

void ClassName::ParseCommand(std::string str)
{
	_history.insert(_history.begin(), str);
}

bool ClassName::IsClosed()
{
	return (_openHeight == 0 && !_isOpenBig && !_isOpenSmall);
}

#ifdef ClassName
#undef ClassName
#endif
