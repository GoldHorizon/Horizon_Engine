#pragma once

#include "SDL.h"
#include "entity.h"
#include "event.h"

#include <string>
#include <sstream>

class Player: public Entity
{
public:
	/*
	 * Constructors/Destructors
	 */
	Player();

	/*
	 * Class Methods
	 */
    // HandleEvents()   - Updates player based on user input
    void HandleEvents(Event&);

	// Update()			- Updates anything to do with the entity
	void Update();

    // NewInstance()    - Overrides method from entity to return a player
    Entity* NewInstance();

	// Render()			- Renders the texture to its current position
	//void Render(float interpolation);
	
	std::string Serialize();

	void Unserialize(std::string);

private:

};
