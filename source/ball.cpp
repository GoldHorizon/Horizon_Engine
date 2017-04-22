#include "../ball.h"
#include "../constants.h"

#include <math.h>

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

//	while (direction() > 360)
//	{
//		SetDirection(direction() - 360);
//	}
//  while (direction() < 0)
//  {
//      SetDirection(direction() + 360);
//  }

	SetImageAngle(imageAngle() + 1);

//	while (imageAngle() > 360)
//	{
//		SetDirection(imageAngle() - 360);
//	}
//    while (imageAngle() < 0)
//    {
//        SetDirection(imageAngle() + 360);
//    }

	Move(xdir, ydir);
}
