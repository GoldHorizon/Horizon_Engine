#include "states/console.h"
#include "drawing.h"
#include "globals.h"
#include "engineMethods.h"

#include <iostream>

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
	_openHeightBig = 0.75;	
	// This is a fraction of openHeight;
	_openHeightSmall = 0.3;
	// This is a fraction of how fast the console opens
	_openRate = 0.04;
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
			Close();
			break;

		case SDLK_BACKQUOTE:
			//std::cout << "CONSOLE DETECTED BACKQUOTE" << std::endl;
			bool lshift = event->key.keysym.mod & KMOD_LSHIFT;

			if (_isOpenBig)
			{
				if (lshift) Close();
				else Open(false);
			}
			else if (_isOpenSmall)
			{
				if (!lshift) Close();
				else Open(true);
			}
			else
			{
				Open(event->key.keysym.mod & KMOD_LSHIFT);
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
	int rate = SCREEN_HEIGHT * _openHeightBig * _openRate;

	if (_isOpenBig || _isOpenSmall)
	{
		if (_isOpenBig)
		{
			int maxHeight = SCREEN_HEIGHT * _openHeightBig;
			Lerp<int>(_openHeight, maxHeight, rate);
		}
		else if (_isOpenSmall)
		{
			int maxHeight = SCREEN_HEIGHT * _openHeightSmall;
			Lerp<int>(_openHeight, maxHeight, rate);
		}
	}
	else if (_openHeight > 0) {
		Lerp<int>(_openHeight, 0, rate);
	}

	if (IsClosed()) 
	{
		// @todo: Find way to signal to game to close the console from there...?	
		
	}
}

void ClassName::Render(float interpolation)
{
	if (_openHeight > 0) {
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

	_openHeight += (SCREEN_HEIGHT * _openHeightBig) * _openRate;
}

void ClassName::Close()
{
	_isOpenSmall = false;
	_isOpenBig = false;
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
