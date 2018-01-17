#include "../../include/states/playing.h"
#include "../../include/ball.h"
#include "../../include/player.h"

#define ClassName StatePlaying

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{

}

void ClassName::Initialize()
{
    Player* mainPlayer = new Player();
    mainPlayer->SetName("MainPlayer");
    _entities.AddEntity(mainPlayer);

    Ball* testBall = new Ball();
    testBall->SetPosition(128, 128);
    testBall->SetDepth(-10);
    testBall->SetName("TestBall");
    _entities.AddEntity(testBall);

    Ball* testBall2 = new Ball();
    testBall2->SetPosition(256, 512);
    testBall2->SetDepth(10);
    testBall2->SetName("TestBall2");
    _entities.AddEntity(testBall2);
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
