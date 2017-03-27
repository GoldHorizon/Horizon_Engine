#include "../TEMPball.h"
#include "../constants.h"

Ball::Ball()
{
	SetDirection(0);
	SetSpeed(10);
}

void Ball::Update()
{
	float xdir = (cos(direction() * PI / 180) * speed());
	float ydir = (sin(direction() * PI / 180) * speed());

	if (x() < 0 || x() > SCREEN_WIDTH)
	{
		SetDirection(direction() + 180);
		xdir = -xdir;
	}

	while (direction() > 360)
	{
		SetDirection(direction() - 360);
	}

	SetImageAngle(imageAngle() + 1);

	while (imageAngle() > 360)
	{
		SetDirection(imageAngle() - 360);
	}

	Move(xdir, ydir);
}
