#pragma once

#include "entity.h"
#include "event.h"

#include <string>

class Ball:
		public Entity
{
public:
	Ball();

    void HandleEvents(Event&);
	void Update();

	std::string Serialize();
	void Unserialize(std::string str);
};
