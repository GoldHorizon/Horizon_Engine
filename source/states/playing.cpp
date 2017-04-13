#include "../../states/playing.h"
#include "../../TEMPball.h"

StatePlaying* StatePlaying::_thisInstance = nullptr;

StatePlaying::~StatePlaying()
{

}

void StatePlaying::Initialize()
{
    Ball* playingBall = new Ball();
    playingBall->SetDirection(15);
    playingBall->LoadFromFile("images/Paddle.png");
    _entities.AddEntity("PlayingBall", playingBall);
}

void StatePlaying::Cleanup()
{

}

void StatePlaying::Pause()
{

}

void StatePlaying::Resume()
{

}

void StatePlaying::HandleEvents()
{

}

void StatePlaying::Update()
{
    _entities.UpdateAll();
}

void StatePlaying::Render(float interpolation)
{
    _entities.RenderAll(interpolation);
}
