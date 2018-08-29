#pragma once

#include "entity.h"

#include <string>

class Ball:
		public Entity
{
public:
	Ball();

    void HandleEvents(SDL_Event*);
	void Update();

	std::string Serialize();
	void Unserialize(std::string str);
};
