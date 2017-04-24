#pragma once

//#include "header.h"
#include "SDL2/SDL.h"
#include <string>

class Player: public entity
{
public:
	/*
	 * Constructors/Destructors
	 */
	Player();

	/*
	 * Class Methods
	 */
	// Update()			- Updates anything to do with the entity
	void Update();

	// Render()			- Renders the texture to its current position
	//void Render(float interpolation);


private:

};
