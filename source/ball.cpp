#include "ball.h"
#include "constants.h"
#include "engineMethods.h"
#include "inputManager.h"

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
	// No events handled here.
}

void Ball::Update()
{
	Entity::Update();

	bool upPressed = Input::KeyHeld(SDLK_UP);
	bool downPressed = Input::KeyHeld(SDLK_DOWN);
	bool leftPressed = Input::KeyHeld(SDLK_LEFT);
	bool rightPressed = Input::KeyHeld(SDLK_RIGHT);
	bool spacePressed = Input::KeyHeld(SDLK_SPACE);

	// Keys adjusts hspeed/vspeed individually
	//if (upPressed != downPressed)
	//{
	//	if (vspeed() > -4)
	//	{
	//		SetVSpeed(vspeed() - (0.1 * upPressed));
	//	}
	//	if (vspeed() < 4)
	//	{
	//		SetVSpeed(vspeed() + (0.1 * downPressed));
	//	}
	//}
	//if (leftPressed != rightPressed)
	//{
	//	if (hspeed() > -4)
	//	{
	//		SetHSpeed(hspeed() - (0.1 * leftPressed));
	//	}
	//	if (hspeed() < 4)
	//	{
	//		SetHSpeed(hspeed() + (0.1 * rightPressed));
	//	}
	//}

	// Keys "drive" the ball, can turn or speed up/slow down
	if (upPressed)
		SetSpeed(speed() + 0.1);

	if (downPressed)
		SetSpeed(speed() - 0.1);

	if (leftPressed)
		SetDirection(direction() - 2);

	if (rightPressed)
		SetDirection(direction() + 2);


	// Space stops all motion
	if (spacePressed)
	{
		SetSpeed(0);
		SetDirection(0);
	}
}

std::string Ball::Serialize()
{
	std::string serialize_string = Entity::Serialize();

	serialize_string += "@Ball ";
	// @@Future: Add ball's member attributes to string

	return serialize_string;
}

void Ball::Unserialize(std::string str)
{
	Entity::Unserialize(str);
}
