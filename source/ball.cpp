#include "../include/ball.h"
#include "../include/constants.h"

#include <iostream>
#include <math.h>

Ball::Ball()
{
    LoadFromFile("images/Player.png");
    SetImageOrigin(this->imageWidth() / 2, this->imageHeight() / 2);
}

void Ball::HandleEvents(SDL_Event* event)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_S] ^ state[SDL_SCANCODE_W])
    {
        if (vspeed() > -4)
        {
            SetVSpeed(vspeed() - (0.1 * state[SDL_SCANCODE_S]));
        }
        if (vspeed() < 4)
        {
            SetVSpeed(vspeed() + (0.1 * state[SDL_SCANCODE_W]));
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
}

void Ball::Update()
{
    Entity::Update();

    std::cout << "Speeds:" << std::endl << hspeed() << std::endl << vspeed() << std::endl << speed() << std::endl << direction() << std::endl << std::endl;

}

