#include "states/console.h"
#include "drawing.h"
#include "globals.h"
#include "engineMethods.h"
#include "enumerations.h"

#include <iostream>
#include <sstream>

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
	_textColor = {255, 255, 255, 255};
	
	// This is how open the console is in terms of pixels
	_openHeight = 0;
	// This is a fraction of the screen height;
	_openHeightBig = 0.75;	
	// This is a fraction of openHeight;
	_openHeightSmall = 0.3;
	// This is a fraction of how fast the console opens
	_openRate = 0.04;

	//ParseCommand("This is a nice test string! abcdefghijklmnopqrstuvwxyz");
	//ParseCommand("Second test");
	//ParseCommand("Third, final test");

	_currentLine = "";
	_savedLine = "";
	_currentLineSelected = -1;

	_cursorPosition = 0;
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
			{
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
				}
			}
			break;

		case SDLK_BACKSPACE:
			{
				if (event->key.keysym.mod & KMOD_CTRL)
				{
					// Delete any space behind the last word
					while (_currentLine.size() > 0 && _currentLine.back() == ' ')
						_currentLine.pop_back();

					// Delete the last word on the line
					if (_currentLine.size() == 0) break;
					while (_currentLine.size() > 0 && _currentLine.back() != ' ')
						_currentLine.pop_back();

					// Delete any spaces before the last word
					while (_currentLine.size() > 0 && _currentLine.back() == ' ')
						_currentLine.pop_back();

					_cursorPosition = _currentLine.size();
				}
				else
				{
					// Delete last character
					if (_currentLine.size() > 0)
						_currentLine.pop_back();

					_cursorPosition--;

					if (_cursorPosition < 0) _cursorPosition = 0;
				}
			}
			break;

		case SDLK_UP:
			SelectLine(_currentLineSelected + 1);
			_cursorPosition = _currentLine.size();
			break;

		case SDLK_DOWN:
			SelectLine(_currentLineSelected - 1);
			_cursorPosition = _currentLine.size();
			break;

		case SDLK_RETURN:
			{
				if (_currentLine.size() > 0)
					ParseCommand(_currentLine);
					_currentLine = "";
				
				_currentLineSelected = -1;
				_cursorPosition = 0;
			}
			break;
		}
	}
	else if (event->type == SDL_TEXTINPUT)
	{
		char c = event->text.text[0];
		if (c != '`' && c != '~') {
			_currentLine += event->text.text;
			_cursorPosition++;
		}
	}
	else if (event->type == SDL_TEXTEDITING)
	{
		std::cout << "DEBUG testin editing input?" << std::endl;
	}

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

	if (/*!SDL_IsTextInputActive() && */IsOpen())
	{
		//std::cout << "Starting text input..." << std::endl;
		SDL_StartTextInput();
	}
}

void ClassName::Render(float interpolation)
{
	if (_openHeight > 0) {
		DrawRect(0, 0, SCREEN_WIDTH, _openHeight, _consoleColor);
		DrawLine(0, _openHeight - 40, SCREEN_WIDTH, _openHeight - 40, SDL_Color {255, 255, 255, 255});
		DrawLine(0, _openHeight - 39, SCREEN_WIDTH, _openHeight - 39, SDL_Color {0, 0, 0, 255});
	}

	for (int i = 0; i < _history.size(); i++)
	{
		// First drop shadow, then text
		DrawText(_history[i], consoleFont, 8 + 1, _openHeight - 64 - (16 * i) + 1, ALIGN_LEFT, {0, 0, 0, 255});
		DrawText(_history[i], consoleFont, 8, _openHeight - 64 - (16 * i), ALIGN_LEFT, _textColor);
	}

	// Draw the cursor
	DrawRect((_cursorPosition * 8) + 9, static_cast<int>(_openHeight - 32), 10, 20, SDL_Color {180, 0, 0, 255});

	// Also draw current line being typed
	if (_currentLine != "") {
		DrawText(_currentLine, consoleFont, 8 + 1, _openHeight - 32 + 1, ALIGN_LEFT, {0, 0, 0, 255});
		DrawText(_currentLine, consoleFont, 8, _openHeight - 32, ALIGN_LEFT, _textColor);
	}

    //_entities.RenderAll(interpolation);
}

void ClassName::Open(bool big)
{
	if (IsClosed())
		_currentLine = "";

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

	SDL_StopTextInput();
}

bool ClassName::IsOpen()
{
	//std::cout << "_openHeight\t\t" << _openHeight << std::endl;
	//std::cout << "_openHeightSmall\t\t" << SCREEN_HEIGHT * _openHeightSmall << std::endl;
	//std::cout << "_openHeightBig\t\t" << SCREEN_HEIGHT * _openHeightBig << std::endl;
	if (_isOpenSmall && _openHeight == static_cast<int>(SCREEN_HEIGHT * _openHeightSmall)) 
	{
		//std::cout << "IsOpenSmall" << std::endl;
		return true;
	}
   	if (_isOpenBig && _openHeight == static_cast<int>(SCREEN_HEIGHT * _openHeightBig))
	{
		//std::cout << "IsOpenBig" << std::endl;
		return true;
	}

	return false;
}

bool ClassName::IsClosed()
{
	return (_openHeight == 0 && !_isOpenBig && !_isOpenSmall);
}

void ClassName::SelectLine(int line)
{
	if (_currentLineSelected == -1 && line >= 0) {
		_savedLine = _currentLine;	
	}

	if (line >= 0 && line < _history.size()) {
		_currentLineSelected = line;
		_currentLine = _history[line];
	}
	else if (line == -1) {
		_currentLine = _savedLine;
		_currentLineSelected = line;
	}
}

void ClassName::ParseCommand(std::string str)
{
	if (str.size() > 0)
	{
		//std::cout << str.trim() << std::endl;
		_history.insert(_history.begin(), str);

		std::stringstream stream(str);
		std::string next;

		//stream >> next;
		//std::cout << "Command:\t\t" << next << std::endl;
		//stream >> next;
		//while (stream) {
		//	std::cout << "\tArgument:\t" << next << std::endl;	
		//	stream >> next;
		//}
	}
}

#ifdef ClassName
#undef ClassName
#endif
