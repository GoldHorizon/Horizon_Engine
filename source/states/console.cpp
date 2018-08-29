#include "states/console.h"
#include "drawing.h"

#define ClassName StateConsole

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{
	Cleanup();
}

void ClassName::Initialize()
{

}

void ClassName::Cleanup()
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

}


#ifdef ClassName
#undef ClassName
#endif
