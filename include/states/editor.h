#pragma once

#include "gameState.h"
#include "level.h"
#include "text.h"
#include "event.h"

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

	int HandleEvents(Event&);
	void Update();
	void Render(float interpolation);

	void SaveLevel();
	bool LoadLevel();
	void SetLevel(std::string name);
	void SetLevel(Level* level);
	Level* GetLevel();

	void ResetLevel();

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

	Level _currentLevel;

	std::string _levelName;
	// Editing values
	bool _drawGrid;
	int _gridSize;
	EditorEntityType _entityType;
	bool _drawType;

	//Text _textType; // @Todo: may have to replace this

	// If user is creating/deleting any entities
	bool _isCreating;
	bool _isDeleting;

	void CreateUI();

};

#ifdef ClassName
#undef ClassName
#endif
