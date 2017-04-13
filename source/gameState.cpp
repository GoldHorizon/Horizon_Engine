//#include <entities.h>
#include "../gameState.h"

GameState::~GameState()
{

}

void GameState::ChangeState (Game* gameReference, GameState* nextState)
{
    gameReference->ChangeState(nextState);
}

GameStateType GameState::GetType()
{
    return _type;
}

EntityCollection& GameState::Entities()
{
    return _entities;
}
