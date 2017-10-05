#include "../../states/playing.h"
#include "../../ball.h"
#include "../../player.h"

#define ClassName StatePlaying

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{

}

void ClassName::Initialize()
{
    Player* mainPlayer = new Player();
    _entities.AddEntity("MainPlayer", mainPlayer);

    Ball* playingBall = new Ball();
    playingBall->SetDirection(15);
    playingBall->LoadFromFile("images/Paddle.png");
    _entities.AddEntity("PlayingBall", playingBall);
}

void ClassName::Cleanup()
{

}

void ClassName::Pause()
{

}

void ClassName::Resume()
{

}

void ClassName::HandleEvents(SDL_Event* event)
{
    _entities.HandleAllEvents(event);
}

void ClassName::Update()
{
    _entities.UpdateAll();
}

void ClassName::Render(float interpolation)
{
    _entities.RenderAll(interpolation);
}

#ifdef ClassName
#undef ClassName
#endif