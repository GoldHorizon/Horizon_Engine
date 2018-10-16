//#include <entities.h>
#include "../include/gameState.h"

GameState::~GameState()
{

}

GameStateType GameState::GetType()
{
    return _type;
}

void GameState::SetType(GameStateType type)
{
    _type = type;
}

EntityCollection& GameState::Entities()
{
    return _entities;
}

void GameState::Pause()
{
	_paused = true;
}

void GameState::Resume()
{
	_paused = false;
}

bool GameState::IsPaused()
{
	return _paused;
}
