#pragma once

#include "gameState.h"
#include "text.h"
#include "event.h"

#define ClassName StateConsole

struct c_line;
enum class c_line_type;

class StateConsole:
	public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected:
    ClassName() {
		SetType(GameStateType::CONSOLE); 
		Resume();
	}
public:
    ~ClassName();

	/*
	 * Class Methods
	 */
    void Initialize();
    void Cleanup();

    int HandleEvents(Event&);
    void Update();
    void Render(float interpolation);

	void Open(bool big = false);
	void Close();
	bool IsOpen();
	bool IsClosed();
	
	void SelectLine(int line);
	void ParseCommand(std::string str);

	void AddOutput(std::string str);
	void AddError(std::string str);

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

	bool _isOpenBig;
	bool _isOpenSmall;
	int _openHeight;
	float _openRate;
	float _openHeightBig;
	float _openHeightSmall;

	unsigned int _cursorPosition;

	std::string _currentLine;
	std::string _savedLine;
	int _currentLineSelected;

	SDL_Color _consoleColor;
	SDL_Color _textInputColor;
	SDL_Color _textOutputColor;
	SDL_Color _textErrorColor;

	std::vector<c_line> _history;
	unsigned int _historyLine;
};

struct c_line
{
	c_line(std::string s, c_line_type t);

	std::string text;
	c_line_type type;
};

enum class c_line_type
{
	INPUT,
	OUTPUT,
	ERROR	
};

#ifdef ClassName
#undef ClassName
#endif
