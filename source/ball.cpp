#include "../include/ball.h"
#include "../include/constants.h"
#include "engineMethods.h"

#include <iostream>
#include <math.h>

Ball::Ball()
{
	const int WIDTH = 32;
	// Load sprite sheet, setting individual sprite (frame) size to 32x32
	LoadImage("images/shrinking_circle.png", WIDTH, WIDTH);

	// Set image origin to be center of sprite (NOT loaded image)
	image()->SetOrigin(WIDTH / 2, WIDTH / 2);

	// Set image speed in ms 
	//SetImageIndex(0);
	image()->SetSpeed(100);

	// Temporary Alpha Testing
	image()->SetAlpha(.5);
}

void Ball::HandleEvents(SDL_Event* event)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	// WASD adjusts hspeed/vspeed individually
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

	// Directional Keys "drive" the ball, can turn or speed up/slow down
	if (state[SDL_SCANCODE_UP])
		SetSpeed(speed() + 0.1);

	if (state[SDL_SCANCODE_DOWN])
		SetSpeed(speed() - 0.1);

	if (state[SDL_SCANCODE_LEFT])
		SetDirection(direction() - 2);

	if (state[SDL_SCANCODE_RIGHT])
		SetDirection(direction() + 2);

	// Space stops all motion
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

std::string Ball::Serialize()
{
	std::string serialize_string = Entity::Serialize();

	serialize_string += "@Ball ";
	// @@Future: Add player's member attributes to string

	return serialize_string;
}

void Ball::Unserialize(std::string str)
{
	Entity::Unserialize(str);
}
