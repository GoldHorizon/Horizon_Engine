#include "../../include/states/pauseMenu.h"
#include "globals.h"
#include "enumerations.h"
#include "constants.h"

#include <iostream>
#include <string>

#define ClassName StatePauseMenu

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

int ClassName::HandleEvents(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		std::cout << std::to_string(event->key.timestamp) << "   " << std::to_string(event->key.repeat) << std::endl;
		switch (event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (event->key.repeat == 0)
				return CLOSE_MENU;
		}
	}
}

void ClassName::Update()
{
//	_entities.UpdateAll();
}

void ClassName::Render(float interpolation)
{
	SDL_Rect* draw_rect = new SDL_Rect;
	draw_rect->x = 128;
	draw_rect->y = 128;
	draw_rect->w = SCREEN_WIDTH - 256;
	draw_rect->h = SCREEN_HEIGHT - 256;
	
	SDL_SetRenderDrawColor(globalRenderer, 0, 80, 80, 200);
	SDL_RenderFillRect(globalRenderer, draw_rect);

	delete draw_rect;
}

#ifdef ClassName
#undef ClassName
#endif
