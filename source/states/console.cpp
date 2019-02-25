#include "states/console.h"
#include "drawing.h"
#include "globals.h"
#include "engineMethods.h"
#include "enumerations.h"
#include "types.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>

#define ClassName StateConsole

ClassName::~ClassName()
{
	Cleanup();
}

void ClassName::Initialize()
{
	// 
	// VARIABLES
	//
	_isOpenBig = false;
	_isOpenSmall = false;

	_consoleColor = {0, 50, 50, 240};
	_textInputColor = {255, 255, 255, 255};
	_textOutputColor = {255, 0, 255, 255};
	_textErrorColor = {255, 30, 40, 255};
	
	// This is how open the console is in terms of pixels
	_openHeight = 0;
	// This is a fraction of the screen height;
	_openHeightBig = 0.75;	
	// This is a fraction of openHeight;
	_openHeightSmall = 0.3;
	// This is a fraction of how fast the console opens
	_openRate = 0.04;

	_currentLine = "";
	_savedLine = "";
	_currentLineSelected = -1;

	_cursorPosition = 0;
	_historyLine = 0;

	// 
	// COMMANDS
	//
	// Test command!
	auto test_func = [this](sVector args) {
		//std::cout << "Argument count: " << args.size() << std::endl;
		//std::for_each (args.begin(), args.end(), [](std::string s) { std::cout << "\t" << s << std::endl; });
		AddOutput("Argument count: " + std::to_string(args.size()));
	};
	commands["test"] = test_func;

	// List command
	auto help_command = [this](sVector args) {
		std::string list;
		std::map<std::string, std::function<void(sVector)>>::iterator it = commands.begin();

		list += it->first;

		while (++it != commands.end())
		{
			list += ", ";

			list += it->first;
		}

		AddOutput(list);
	};

	commands["help"] = help_command;

	//AddCommand("help", list_command, 0, 0);
}

void ClassName::Cleanup()
{

}

KeyEvent ClassName::HandleEvents(Event& event)
{
	if (event.ev.type == SDL_KEYDOWN)
	{
		switch (event.ev.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			Close();
			break;

		case SDLK_BACKQUOTE:
			{
				//std::cout << "CONSOLE DETECTED BACKQUOTE" << std::endl;
				bool lshift = event.ev.key.keysym.mod & KMOD_LSHIFT;

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
					Open(event.ev.key.keysym.mod & KMOD_LSHIFT);
				}
			}
			break;

		case SDLK_DELETE:
			{
				if (event.ev.key.keysym.mod & KMOD_CTRL)
				{
					if (_cursorPosition == 0 && _currentLine.size() > 0)
					{
						// Delete any space in front of the last word
						while (_currentLine.size() > 0 && _currentLine.front() == ' ')
							_currentLine = _currentLine.substr(1, std::string::npos);

						// Delete the first word on the line
						while (_currentLine.size() > 0 && _currentLine.front() != ' ')
							_currentLine = _currentLine.substr(1, std::string::npos);

						// Delete any spaces after the first word
						while (_currentLine.size() > 0 && _currentLine.front() == ' ')
							_currentLine = _currentLine.substr(1, std::string::npos);
					}
					else if (_cursorPosition != _currentLine.size())
					{
						std::string lh, rh;
						lh = _currentLine.substr(0, _cursorPosition);
						rh = _currentLine.substr(_cursorPosition, std::string::npos);

						// Delete any space in front of the last word
						while (rh.size() > 0 && rh.front() == ' ')
							rh = rh.substr(1, std::string::npos);

						// Delete the first word on the line
						while (rh.size() > 0 && rh.front() != ' ')
							rh = rh.substr(1, std::string::npos);

						// Delete any spaces after the first word
						while (rh.size() > 0 && rh.front() == ' ')
							rh = rh.substr(1, std::string::npos);

						_currentLine = lh + rh;
						_cursorPosition = lh.size();
					}
				}
				else
				{
					if (_cursorPosition == 0 && _currentLine.size() > 0)
					{
						_currentLine = _currentLine.substr(1, std::string::npos);
					}
					else if (_cursorPosition != _currentLine.size())
					{
						std::string lh, rh;
						lh = _currentLine.substr(0, _cursorPosition);
						rh = _currentLine.substr(_cursorPosition + 1, std::string::npos);

						_currentLine = lh + rh;
					}
				}
			}
			break;

		case SDLK_BACKSPACE:
			{
				if (event.ev.key.keysym.mod & KMOD_CTRL)
				{
					if (_cursorPosition == _currentLine.size()) {
						// Delete any space behind the last word
						while (_currentLine.size() > 0 && _currentLine.back() == ' ')
							_currentLine.pop_back();

						// Delete the last word on the line
						while (_currentLine.size() > 0 && _currentLine.back() != ' ')
							_currentLine.pop_back();

						// Delete any spaces before the last word
						while (_currentLine.size() > 0 && _currentLine.back() == ' ')
							_currentLine.pop_back();

						_cursorPosition = _currentLine.size();
					} else if (_cursorPosition != 0) {

						std::string lh, rh;
						lh = _currentLine.substr(0, _cursorPosition);
						rh = _currentLine.substr(_cursorPosition, std::string::npos);

						// Delete any space behind the last word
						while (lh.size() > 0 && lh.back() == ' ')
							lh.pop_back();

						// Delete the last word on the line
						while (lh.size() > 0 && lh.back() != ' ')
							lh.pop_back();

						// Delete any spaces before the last word
						while (lh.size() > 0 && lh.back() == ' ')
							lh.pop_back();

						_currentLine = lh + rh;
						_cursorPosition = lh.size();
					}	
				}
				else
				{
					if (_cursorPosition == _currentLine.size() && _currentLine.size() > 0) {
						// Delete last character
						if (_currentLine.size() > 0)
							_currentLine.pop_back();

						_cursorPosition--;

						if (_cursorPosition < 0) _cursorPosition = 0;
					} else if (_cursorPosition != 0) {
						std::string lh, rh;
						lh = _currentLine.substr(0, _cursorPosition);
						rh = _currentLine.substr(_cursorPosition, std::string::npos);

						lh.pop_back();

						_currentLine = lh + rh;
						_cursorPosition = lh.size();
					}	

					assert (_cursorPosition >= 0 && "Console cursor position less than 0");
				}
			}
			break;

		case SDLK_UP:
			{
				size_t i = _currentLineSelected + 1;
				while (i < _history.size()
						&& _history[i].type != c_line_type::INPUT) {
					i++;
				}
				SelectLine(i);
				_cursorPosition = _currentLine.size();
			}
			break;

		case SDLK_DOWN:
			{
				int i = _currentLineSelected - 1;
				while (i >= 0
						&& _history[i].type != c_line_type::INPUT) {
					i--;
				}
				SelectLine(i);
				_cursorPosition = _currentLine.size();
			}
			break;

		case SDLK_LEFT:
			{
				if (_cursorPosition > 0) {
					if (event.ev.key.keysym.mod & KMOD_LCTRL) {
						if (_currentLine[_cursorPosition] != ' ' && _currentLine[_cursorPosition - 1] == ' ')
							_cursorPosition--;

						while (_cursorPosition > 0 && _currentLine[_cursorPosition] == ' ')
							_cursorPosition--;
						while (_cursorPosition > 0 && _currentLine[_cursorPosition] != ' ' && _currentLine[_cursorPosition - 1] != ' ')
							_cursorPosition--;

						//if (_currentLine[_cursorPosition] == ' ' && _currentLine[_cursorPosition + 1] != ' ')
						//	_cursorPosition++;
					} else _cursorPosition--;
				}
			}
			break;

		case SDLK_RIGHT:
			{
				if (_cursorPosition < _currentLine.size()) {
					if (event.ev.key.keysym.mod & KMOD_LCTRL) {
						while (_cursorPosition < _currentLine.size() && _currentLine[_cursorPosition] != ' ')
							_cursorPosition++;

						while (_cursorPosition < _currentLine.size() && _currentLine[_cursorPosition] == ' ')
							_cursorPosition++;
					}
					else _cursorPosition++;
				}
			}
			break;

		case SDLK_HOME:
			{
				_cursorPosition = 0;
			}
			break;

		case SDLK_END:
			{
				_cursorPosition = _currentLine.size();
			}
			break;

		case SDLK_RETURN:
			{
				if (_currentLine.size() > 0) {
					ParseCommand(_currentLine);
					_currentLine = "";
				
					_currentLineSelected = -1;
					_cursorPosition = 0;

					_historyLine = 0;
				}
			}
			break;
		}
	}
	else if (event.ev.type == SDL_TEXTINPUT) // Normal typing
	{
		char c = event.ev.text.text[0];
		if (c != '`' && c != '~') {
			if (_cursorPosition == _currentLine.size())
				_currentLine += event.ev.text.text;
			else if (_cursorPosition == 0)
				_currentLine = event.ev.text.text + _currentLine;
			else
				_currentLine = _currentLine.substr(0, _cursorPosition) 
								+ event.ev.text.text 
								+ _currentLine.substr(_cursorPosition, std::string::npos);

			_cursorPosition++;
		}
	}
	else if (event.ev.type == SDL_MOUSEWHEEL) // Scroll through history
	{
		int n = event.ev.wheel.y;
		//std::cout << "DEBUG mousewheel event" << std::endl;
		
		while (n < 0) {
			if (_historyLine > 0) _historyLine--;
			n++;
		} 

		while (n > 0) {
			if (_historyLine < _history.size() - 1) _historyLine++;
			n--;
		}
	}

	return KeyEvent::none;
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

	if (IsOpen())
	{
		SDL_StartTextInput();
	}
}

void ClassName::Render(float interpolation)
{
	if (_openHeight > 0) {
		// Draw console window
		DrawRect(0, 0, SCREEN_WIDTH, _openHeight, _consoleColor);
		DrawLine(0, _openHeight - 40, SCREEN_WIDTH, _openHeight - 40, SDL_Color {255, 255, 255, 255});
		DrawLine(0, _openHeight - 39, SCREEN_WIDTH, _openHeight - 39, SDL_Color {0, 0, 0, 255});
	}

	// Draw history lines 
	for (size_t i = _historyLine; i < _history.size(); i++)
	{
		int drawHeight = (_openHeight - 64 - (16 * i) + (_historyLine * 16));

		// If trying to draw above the screen, we can stop drawing to save render time
		if (drawHeight < -16) {
			//std::cout << "DEBUG drawing above screen, i = " << i << std::endl;
			break;
		}

		// First drop shadow, then text
		DrawText(_history[i].text, TextQuality::BLENDED, consoleFont, 8 + 1, drawHeight + 1, ALIGN_LEFT, {0, 0, 0, 255});

		// Decide text color based on text type
		SDL_Color *text_c;
		switch (_history[i].type)
		{
			case c_line_type::INPUT:
				text_c = &_textInputColor;
				break;

			case c_line_type::OUTPUT:
				text_c = &_textOutputColor;
				break;

			case c_line_type::ERROR:
				text_c = &_textErrorColor;
				break;
		}
		DrawText(_history[i].text, TextQuality::BLENDED, consoleFont, 8, drawHeight, ALIGN_LEFT, *text_c);
	}

	// Draw the cursor
	DrawRect((_cursorPosition * 10) + 9, static_cast<int>(_openHeight - 32), 10, 20, SDL_Color {180, 0, 0, 255});

	// Also draw current line being typed
	if (_currentLine != "") {
		DrawText(_currentLine, TextQuality::BLENDED, consoleFont, 8 + 1, _openHeight - 32 + 1, ALIGN_LEFT, {0, 0, 0, 255});
		DrawText(_currentLine, TextQuality::BLENDED, consoleFont, 8, _openHeight - 32, ALIGN_LEFT, _textInputColor);
	}

    //_entities.RenderAll(interpolation);
}

void ClassName::Open(bool big)
{
	if (IsClosed()) {
		_currentLine = "";
		_currentLineSelected = -1;
		_cursorPosition = 0;
	}

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

	if (line >= 0 && line < (int)(_history.size())) {
		if (_history[line].type == c_line_type::INPUT) {
			_currentLineSelected = line;
			_currentLine = _history[line].text;
		}
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
		_history.insert(_history.begin(), c_line(str, c_line_type::INPUT));

		std::stringstream stream(str);
		std::string command;
		std::string next_arg;

		stream >> command;
		//std::cout << "Command:\t\t" << next_arg << std::endl;

		sVector args;

		stream >> next_arg;
		while (stream) {
			//std::cout << "\tArgument:\t" << next_arg << std::endl;	
			args.push_back(next_arg);
			stream >> next_arg;
		}

		if (commands.find(command) != commands.end())
		{
			// Execute command with arg list given
			commands[command](args);
		}
		else
		{
			//std::cout << "Error: Could not find command " << command << "!" << std::endl;
			AddError("Error: Could not find command " + command);
		}
	}
}

void ClassName::AddOutput(std::string str)
{
	_history.insert(_history.begin(), c_line(str, c_line_type::OUTPUT));
}

void ClassName::AddError(std::string str)
{
	_history.insert(_history.begin(), c_line(str, c_line_type::ERROR));
}

c_line::c_line(std::string s, c_line_type t) :
	text(s),
	type(t) {}

#ifdef ClassName
#undef ClassName
#endif
