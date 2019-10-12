#pragma once

#include "gameState.h"
#include "text.h"
#include "event.h"

struct c_line;
enum class c_line_type;

class StateConsole:
	public GameState
{
	/*
	 * Constructors/Destructors
	 */
public:
	StateConsole() {
		Initialize();
		SetType(GameStateType::CONSOLE); 
		Resume();
	}
    ~StateConsole();

	/*
	 * Class Methods
	 */
    void Initialize() override;
    void Cleanup() override;

    KeyEvent HandleEvents(Event&) override;
    void Update() override;
    void Render(float interpolation) override;

	void Open(bool big = false);
	void Close();
	bool IsOpen();
	bool IsClosed();
	
	void SelectLine(int line);
	void ParseCommand(std::string str);

	void AddOutput(std::string str);
	void AddError(std::string str);

private:
	bool _isOpenBig;
	bool _isOpenSmall;
	int _openHeight;
	float _openRate;
	float _openHeightBig;
	float _openHeightSmall;

	unsigned _cursorPosition;

	std::string _currentLine;
	std::string _savedLine;
	int _currentLineSelected;

	SDL_Color _consoleColor;
	SDL_Color _textInputColor;
	SDL_Color _textOutputColor;
	SDL_Color _textErrorColor;

	std::vector<c_line> _history;	// Previous lines
	unsigned _historyLine;			// Saved line being typed
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
