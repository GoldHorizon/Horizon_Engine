#include "../include/player.h"
#include "../include/constants.h"
#include "engineMethods.h"

#include <iostream>
#include <math.h>

Player::Player()
{
    LoadFromFile("images/Player.png");
    SetImageOrigin(this->imageWidth() / 2, this->imageHeight() / 2);

}

void Player::HandleEvents(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        SetX(x);
        SetY(y);
    } 

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	int calcDirection = 0;

	// We use SDL_GetKeyboardState for continuous button presses, not key down events
	if ((state[SDL_SCANCODE_W] ^ state[SDL_SCANCODE_S]) || (state[SDL_SCANCODE_A] ^ state[SDL_SCANCODE_D]))
	{
		SetSpeed(4);

		calcDirection = ((state[SDL_SCANCODE_D] * 1) +
						 (state[SDL_SCANCODE_S] * 2) +
						 (state[SDL_SCANCODE_A] * 4) +
						 (state[SDL_SCANCODE_W] * 8)) ;

		switch (calcDirection)
		{
			case 1: case 11:
				SetDirection(0);
				break;
			case 2: case 7:
				SetDirection(90);
				break;
			case 4: case 14:
				SetDirection(180);
				break;
			case 8: case 13:
				SetDirection(270);
				break;
			case 3:
				SetDirection(45);
				break;
			case 6:
				SetDirection(135);
				break;
			case 12:
				SetDirection(225);
				break;
			case 9:
				SetDirection(315);
				break;
			default:
				break;
		}
	}
	else
		SetSpeed(0);

// 		If our event is a keyboard button press ???
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
    Entity::Update();
}

Entity* Player::NewInstance()
{
    return new Player();
}

std::string Player::Serialize()
{
	std::string serialize_string = Entity::Serialize();

	serialize_string += "Player ";
	// @@Future: Add player's member attributes to string

	return serialize_string;
}

void Player::Unserialize(std::string str)
{
	Entity::Unserialize(str);

	//std::stringstream stream(str);
	//std::string temp;
	//
	////std::cout << "Back in player" << std::endl;

	//stream >> temp;
	//while (stream)
	//{
	//	//std::cout << temp << std::endl;
	//	stream >> temp;
	//	if (temp == "Player") break;
	//}
}
