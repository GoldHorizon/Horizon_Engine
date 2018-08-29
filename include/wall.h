#pragma once

#include "entity.h"

class Wall: public Entity
{
public:
	/*
	 * Constructors/Destructors
	 */
	Wall();

	/*
	 * Class Methods
	 */
    // HandleEvents()   - Updates wall based on user input (not needed)
    //void HandleEvents(SDL_Event*);

	// Update()			- Updates anything to do with the entity
	void Update();

    // NewInstance()    - Overrides method from entity to return a wall
    Entity* NewInstance();

	// Render()			- Renders the texture to its current position
	//void Render(float interpolation);
	
	std::string Serialize();

	void Unserialize(std::string);

private:

};
