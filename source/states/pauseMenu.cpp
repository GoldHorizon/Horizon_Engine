#include "../../include/states/pauseMenu.h"
#include "globals.h"
#include "enumerations.h"
#include "constants.h"
#include "drawing.h"

#include <iostream>
#include <string>

#define ClassName StatePauseMenu

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{
	Cleanup();
}

void ClassName::Initialize()
{
	//Draw menu title
	Text* menuTitle = new Text("Menu", menuTitleFont);
	menuTitle->SetPosition({ SCREEN_WIDTH / 2, 160 });
	menuTitle->SetColor(SDL_Color({255, 255, 0, 255}));
	menuTitle->SetAlign(ALIGN_CENTER);
	menuTitle->UpdateImage();

	//Draw menu options
	Text* menuOptionResume = new Text("Resume", menuOptionFont);
	menuOptionResume->SetPosition({ SCREEN_WIDTH / 2, 320 });
	menuOptionResume->SetColor(SDL_Color({255, 255, 255, 255}));
	menuOptionResume->SetAlign(ALIGN_CENTER);
	menuOptionResume->UpdateImage();

	_entities.AddEntity(menuTitle);
	_entities.AddEntity(menuOptionResume);
}

void ClassName::Cleanup()
{
	while (_entities.GetCount() > 0)
	{
		_entities.RemoveByIndex(0);
	}
}

int ClassName::HandleEvents(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		//std::cout << std::to_string(event->key.timestamp) << "   " << std::to_string(event->key.repeat) << std::endl;
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
	if (!IsPaused())
		_entities.UpdateAll();
}

void ClassName::Render(float interpolation)
{
	//SDL_Rect* draw_rect = new SDL_Rect;
	//draw_rect->x = 128;
	//draw_rect->y = 128;
	//draw_rect->w = SCREEN_WIDTH - 256;
	//draw_rect->h = SCREEN_HEIGHT - 256;
	
	//SDL_SetRenderDrawColor(globalRenderer, 0, 80, 80, 200);
	//SDL_RenderFillRect(globalRenderer, draw_rect);

	//delete draw_rect;
	
	DrawRect({128, 128, SCREEN_WIDTH - 256, SCREEN_HEIGHT - 256}, {0, 80, 80, 255});
	// For testing
	//DrawRect(0, 0, 32, 32, 255, 0, 0, 255);

    _entities.RenderAll(interpolation);
}

#ifdef ClassName
#undef ClassName
#endif
