#pragma once

#include "entity.h"

class Ball:
		public Entity
{
public:
	Ball();

    void HandleEvents(SDL_Event*);
	void Update();
};
