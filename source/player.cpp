#include "player.h"
#include "constants.h"
#include "engineMethods.h"
#include "globals.h"

#include "states/console.h"

#include <iostream>
#include <math.h>

Player::Player()
{
    LoadImage("images/Player.png");
    image()->SetOrigin(image()->width() / 2, image()->height() / 2);

	image()->SetColor({.5 * 255, .5 * 255, .2 * 255});
	image()->SetBlendMode(BlendMode::BLEND);

	commands["psetc"] = [this](sVector args) {
		if (args.size() == 3) {
			float rgb[3];
			for (int i = 0; i < 3; i++)
				rgb[i] = std::atof(args[i].c_str());

			this->image()->SetColor({rgb[0]*255, rgb[1]*255, rgb[2]*255});
		} else AddError("Need 3 arguments");
	};

	commands["psetm"] = [this](sVector args) {
		if (args.size() == 1) {
			if (args[0] == "none") this->image()->SetBlendMode(BlendMode::NONE);
			if (args[0] == "blend") this->image()->SetBlendMode(BlendMode::BLEND);
			if (args[0] == "add") this->image()->SetBlendMode(BlendMode::ADD);
			if (args[0] == "mod") this->image()->SetBlendMode(BlendMode::MOD);

		} else AddError("Need 1 argument");
	};

	commands["pseta"] = [this](sVector args) {
		if (args.size() == 1)
			image()->SetAlpha(std::atof(args[0].c_str()));
		else AddError("Need 1 argument");
	};

}

void Player::HandleEvents(Event& event)
{
    if (event.ev.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

		// Alter coords based on cam position
		x += globalCam->x();
		y += globalCam->y();

        this->x = (x);
        this->y = (y);
    } 

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	int calcDirection = 0;

	// We use SDL_GetKeyboardState for continuous button presses, not key down events
	// Need to check that actually...
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

	serialize_string += "@Player ";
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
