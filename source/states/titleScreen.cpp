#include "../../globals.h"

#include "../../states/titleScreen.h"

StateTitleScreen* StateTitleScreen::_thisInstance = nullptr;

StateTitleScreen::~StateTitleScreen()
{

}

void StateTitleScreen::Initialize()
{
    
}

void StateTitleScreen::Cleanup()
{

}

void StateTitleScreen::Pause()
{

}

void StateTitleScreen::Resume()
{

}

void StateTitleScreen::HandleEvents()
{

}

void StateTitleScreen::Update()
{

}

void StateTitleScreen::Render(float interpolation)
{
    int mx;
    int my;

    SDL_GetGlobalMouseState(&mx, &my);

    SDL_RenderDrawLine(globalRenderer, 0, 0, mx, my);
}