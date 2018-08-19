#pragma once

#include "game.h"
#include "enumerations.h"

// Inspired by Game Dev Geek
// http://gamedevgeek.com/tutorials/managing-game-states-in-c/ 
// and
// https://sourcemaking.com/design_patterns/singleton/cpp/1 

class GameState
{
	/*
	 * Constructors/Destructors
	 */
protected:
    GameState() {}
public:
    virtual ~GameState();
	/*
	 * Class Methods
	 */
    virtual void Initialize() = 0;
    virtual void Cleanup() = 0;

    virtual int HandleEvents(SDL_Event*) = 0;
    virtual void Update() = 0;
    virtual void Render(float interpolation) = 0;

    void ChangeState(Game* gameReference, GameState* nextState);

    // NOTE: Goes in all inherited states
    // static GameState* Instance()
    //{
    //    if (_thisInstance == nullptr)
    //    {
    //        _thisInstance = new GameState;
    //    }
    //    return _thisInstance;
    //}

    // GetType()            - Returns the state type
    GameStateType GetType();

    // Entities()			- Returns entity collection
    EntityCollection& Entities();

    void Pause();
    void Resume();
    bool IsPaused();

private:
    // NOTE: Goes in all inherited states
    //static GameState* _thisInstance;

    GameStateType _type;
    bool _paused;

protected:
    void SetType(GameStateType type);
    EntityCollection _entities;
};

// NOTE: Goes in all inherited states
// Initiate global instance to nullptr
//GameState* GameState::_thisInstance = nullptr;
