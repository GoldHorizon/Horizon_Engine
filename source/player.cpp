#include "../player.h"
#include "../constants.h"

#include <math.h>

Player::Player()
{
    LoadFromFile("images/Player.png");
    SetImageOrigin(this->imageWidth() / 2, this->imageHeight() / 2);

}

void Player::HandleEvents(SDL_Event* event)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	// If our event is a keyboard button press ???
//	if (event->type == SDL_KEYDOWN)
//	{
//		switch (event->key.keysym.scancode)
//		{
//			case SDL_SCANCODE_W:
//				SetDirection(270);
//				SetSpeed(4);
//				break;
//
//			case SDL_SCANCODE_S:
//				SetDirection(90);
//				SetSpeed(4);
//				break;
//
//			case SDL_SCANCODE_A:
//				SetDirection(180);
//				SetSpeed(4);
//				break;
//
//			case SDL_SCANCODE_D:
//				SetDirection(0);
//				SetSpeed(4);
//				break;
//
//			default:
//				SetSpeed(0);
//				break;
//		}
//	}
//	else
//	{
//		SetSpeed(0);
//	}
}

void Player::Update()
{
	float xdir = (cos(direction() * PI / 180) * speed());
	float ydir = (sin(direction() * PI / 180) * speed());

	if (x() < 0 || x() > SCREEN_WIDTH)
	{
		SetDirection(180 - direction());
		xdir = -xdir;
		SetSpeed(speed() + 0.1);
	}

	if (y() < 0 || y() > SCREEN_HEIGHT)
	{
		SetDirection(360 - direction());
		ydir = -ydir;
		SetSpeed(speed() + 0.1);
	}

	Move(xdir, ydir);
}

Entity* Player::NewInstance()
{
    return new Player();
}