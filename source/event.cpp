#include "event.h"

Event::Event()
{
	_blocked = false;
}

Event::~Event()
{

}

void Event::Reset()
{
	_blocked = false;
}

void Event::Block()
{
	_blocked = true;
}

bool Event::blocked()
{
	return _blocked;
}

