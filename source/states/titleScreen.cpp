#include "../../include/states/titleScreen.h"
#include "../../include/globals.h"

#define ClassName StateTitleScreen

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{

}

void ClassName::Initialize()
{
    
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

int ClassName::HandleEvents(SDL_Event*)
{

}

void ClassName::Update()
{

}

void ClassName::Render(float interpolation)
{
    int mx;
    int my;

    SDL_GetMouseState(&mx, &my);

    SDL_SetRenderDrawColor(globalRenderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(globalRenderer, 0, 0, mx, my);
}

#ifdef ClassName
#undef ClassName
#endif
