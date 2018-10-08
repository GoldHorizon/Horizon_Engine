#include "event.h"

Event::Event()
{
	_event = nullptr;
	_blocked = false;
}

Event::~Event()
{

}

void Event::Reset()
{
	_event = nullptr;
	_blocked = false;
}

SDL_Event* Event::event()
{
	return _event;
}

bool Event::blocked()
{
	return _blocked;
}

void Event::SetEvent(SDL_Event* event)
{
	_event = event;
}

void Event::SetBlocked(bool blocked)
{
	_blocked = blocked;
}

