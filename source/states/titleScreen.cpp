#include "states/titleScreen.h"
#include "globals.h"

#define ClassName StateTitleScreen

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

KeyEvent ClassName::HandleEvents(Event&)
{
	return KeyEvent::none;
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
