#pragma once

#include "gameState.h"
#include "level.h"

#define ClassName StateEditor

class StateEditor : public GameState
{
	/*
	 * Constructors/Destructors
	 */
protected:
	ClassName() {SetType(GameStateType::LEVEL_EDITOR); Resume(); }
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

	void SaveLevel();
	bool LoadLevel();
	void SetLevel(std::string name);

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

	//std::vector<Level*> _levelList;
	Level _currentLevel;

	std::string _levelName;
	// Editing values
	bool _drawGrid;
	int _gridSize;
};

#ifdef ClassName
#undef ClassName
#endif
