#pragma once

#include "enumerations.h"
#include "event.h"
#include "entityCollection.h"

#include "SDL.h"

// Inspired by Game Dev Geek
// http://gamedevgeek.com/tutorials/managing-game-states-in-c/ 
// and
// https://sourcemaking.com/design_patterns/singleton/cpp/1 

// Removing singleton design pattern

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

    virtual KeyEvent HandleEvents(Event&) = 0;
    virtual void Update() = 0;
    virtual void Render(float interpolation) = 0;

    // GetType()            - Returns the state type
    GameStateType GetType();

    // Entities()			- Returns entity collection
    EntityCollection& Entities();

    void Pause();
    void Resume();
    bool IsPaused();

protected:
	/*
	 * Protected Methods
	 */
    void SetType(GameStateType type);

	/*
	 * Protected Attributes
	 */
    EntityCollection _entities;

private:
    GameStateType _type;
    bool _paused;
};
