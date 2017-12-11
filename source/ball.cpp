#include "../include/ball.h"
#include "../include/constants.h"

#include <iostream>
#include <math.h>

Ball::Ball()
{
    LoadFromFile("images/shrinking_circle.png", 32, 32);
    SetImageOrigin(16, 16);

	SetImageIndex(0);
	SetImageSpeed(75);
}

void Ball::HandleEvents(SDL_Event* event)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_W] ^ state[SDL_SCANCODE_S])
	{
		if (vspeed() > -4)
		{
			SetVSpeed(vspeed() - (0.1 * state[SDL_SCANCODE_W]));
		}
		if (vspeed() < 4)
		{
			SetVSpeed(vspeed() + (0.1 * state[SDL_SCANCODE_S]));
		}
	}

	if (state[SDL_SCANCODE_A] ^ state[SDL_SCANCODE_D])
	{
		if (hspeed() > -4)
		{
			SetHSpeed(hspeed() - (0.1 * state[SDL_SCANCODE_A]));
		}
		if (hspeed() < 4)
		{
			SetHSpeed(hspeed() + (0.1 * state[SDL_SCANCODE_D]));
		}
	}

	if (state[SDL_SCANCODE_UP])
		SetSpeed(speed() + 0.1);

	if (state[SDL_SCANCODE_DOWN])
		SetSpeed(speed() - 0.1);

	if (state[SDL_SCANCODE_LEFT])
		SetDirection(direction() - 2);

	if (state[SDL_SCANCODE_RIGHT])
		SetDirection(direction() + 2);

	if (state[SDL_SCANCODE_SPACE])
	{
		SetSpeed(0);
		SetDirection(0);
	}
}

void Ball::Update()
{
    Entity::Update();

	// DEBUG
	/*
    std::cout << "Speeds:" << std::endl 
		<< hspeed() << std::endl 
		<< vspeed() << std::endl 
		<< speed() << std::endl 
		<< direction() << std::endl 
		<< atan(vspeed() / hspeed()) / PI * 180 << std::endl;
	*/
}

