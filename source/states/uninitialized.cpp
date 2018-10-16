#include "states/uninitialized.h"

#define ClassName StateUninitialized

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

int ClassName::HandleEvents(Event& event)
{
	return -1;
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
