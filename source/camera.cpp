#include "camera.h"
#include "globals.h"

Camera::Camera()
{
	_origin = Align::TOP_L;
	_x = 0;
	_y = 0;
	_w = SCREEN_WIDTH;
	_h = SCREEN_HEIGHT;
}

Camera::~Camera()
{

}

/*
 * Get Methods
 */
int Camera::x() const
{
	return _x;
}
int Camera::y() const
{
	return _y;
}
int Camera::w() const
{
	return _w;
}
int Camera::h() const
{
	return _h;
}
Vec2<int> Camera::position() const
{
	return Vec2<int> (_x, _y);
}

Vec2<int> Camera::dimensions() const
{
	return Vec2<int> (_w, _h);
}

/*
 * Set Methods
 */
void Camera::SetX(int x)
{
	_x = x;
}

void Camera::SetY(int y)
{
	_y = y;
}

void Camera::SetW(int w)
{
	_w = w;
}

void Camera::SetH(int h)
{
	_h = h;
}

void Camera::SetPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void Camera::SetPosition(Vec2<int> pos)
{
	_x = pos.x;
	_y = pos.y;
}

void Camera::SetDimensions(int w, int h)
{
	_w = w;
	_h = h;
}

void Camera::SetDimensions(Vec2<int> dim)
{
	_w = dim.x;
	_h = dim.y;
}

