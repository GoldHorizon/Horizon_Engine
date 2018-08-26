#include "states/editor.h"

#define ClassName StateEditor

ClassName::~ClassName()
{

}

void ClassName::Initialize()
{

}

void ClassName::Cleanup()
{

}

int ClassName::HandleEvents(SDL_Event* event)
{
	// We don't want to update the objects we are editing

	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (event->key.repeat == 0)
				return OPEN_MENU;
		}
	}

	return -1;
}

void ClassName::Update()
{
	if (!IsPaused())
	{
		_entities.UpdateAll();
	}
}

void ClassName::Render(float interpolation)
{
	// We will render objects, but not update them
    _entities.RenderAll(interpolation);
}

#ifdef ClassName
#undef ClassName
#endif
