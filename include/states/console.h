#pragma once

#include "gameState.h"
#include "text.h"

#define ClassName StateConsole

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

    int HandleEvents(SDL_Event*);
    void Update();
    void Render(float interpolation);

	void Open(bool big = false);
	void Close();
	void ParseCommand(std::string str);
	bool IsClosed();

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

	SDL_Color _consoleColor;

	std::vector<std::string> _history;
};

#ifdef ClassName
#undef ClassName
#endif
