#include "camera.h"
#include "globals.h"

Camera::Camera()
{
	origin = Align::TOP_L;
	w = SCREEN_WIDTH;
	h = SCREEN_HEIGHT;
	_x = 0;
	_y = 0;

	_moveToTarget = false;
	_targetObj = nullptr;
	_targetPos = {0, 0};
}

Camera::~Camera()
{

}

/*
 * Class Methods
 */
void Camera::Move(int x, int y)
{
	if (!_moveToTarget) {
		_x += x;
		_y += y;
	//} else {
	//	_targetPos.x += x;
	//	_targetPos.y += y;
	}
}

void Camera::Move(vec2<int> pos)
{
	if (!_moveToTarget) {
		_x += pos.x;
		_y += pos.y;
	//} else {
	//	_targetPos += pos;
	}
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
vec2<int> Camera::position() const
{
	return vec2<int> (_x, _y);
}

vec2<int> Camera::dimensions() const
{
	return vec2<int> (w, h);
}

/*
 * Set Methods
 */
void Camera::SetX(int x)
{
	if (origin == Align::TOP_L || origin == Align::MID_L || origin == Align::BOT_L)
		_x = x;

	if (origin == Align::TOP_C || origin == Align::MID_C || origin == Align::BOT_C)
		_x = x - (w / 2);

	if (origin == Align::TOP_R || origin == Align::MID_R || origin == Align::BOT_R)
		_x = x - w;
}

void Camera::SetY(int y)
{
	if (origin == Align::TOP_L || origin == Align::TOP_C || origin == Align::TOP_R)
		_y = y;

	if (origin == Align::MID_L || origin == Align::MID_C || origin == Align::MID_R)
		_y = y - (h / 2);

	if (origin == Align::BOT_L || origin == Align::BOT_C || origin == Align::BOT_R)
		_y = y - h;
}

void Camera::SetPosition(int x, int y)
{
	if (!_moveToTarget) {
		SetX(x);
		SetY(y);
	//} else {
	//	_targetPos.x = x;
	//	_targetPos.y = y;
	}
}

void Camera::SetPosition(vec2<int> pos)
{
	if (!_moveToTarget) {
		SetX(pos.x);
		SetY(pos.y);
	//} else {
	//	_targetPos.x = pos.x;
	//	_targetPos.y = pos.y;
	}
}

void Camera::SetDimensions(int w, int h)
{
	this->w = w;
	this->h = h;
}

void Camera::SetDimensions(vec2<int> dim)
{
	this->w = dim.x;
	this->h = dim.y;
}

