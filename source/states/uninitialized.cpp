#include "states/uninitialized.h"

#define ClassName StateUninitialized

ClassName::~ClassName()
{

}

void ClassName::Initialize()
{
    
}

void ClassName::Cleanup()
{

}

KeyEvent ClassName::HandleEvents(Event& event)
{
	return KeyEvent::none;
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
