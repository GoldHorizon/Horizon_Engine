#include "panel.h"
#include "drawing.h"
#include "globals.h"
#include "engineMethods.h"

#include <iostream>

Panel::Panel()
{
	_title = "Title";
	_dim = {128, 512};
	_barHeight = 24;

	_bgColor = {0, .2, .2, .9};
	_barColor = {0, .6, .6, .9};

	_focused = false;
	_grabbed = false;
	_locked = false;
	_screenBound = true;
	_followCamera = true;
}

Panel::~Panel()
{

}

void Panel::HandleEvents(SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			// If we press left mb and the panel is not locked in place...
			if (event->button.button == SDL_BUTTON_LEFT && !_locked) {
				int mx, my;
				mx = event->button.x;
				my = event->button.y;

				if (_followCamera) {
					if (mx >= x() && mx < x() + _dim.x && my >= y() && my < y() + _barHeight && !_grabbed) {
						// Grab the panel and set the offset for where the mouse is
						_grabbed = true;
						_offset = {event->button.x - x(), event->button.y - y()};
						//std::cout << "Grabbed!" << std::endl;
					}
				} else {
					if (mx >= x() - globalCam->x() && mx < x() - globalCam->x() + _dim.x && my >= y() - globalCam->y() && my < y() - globalCam->y() + _barHeight && !_grabbed) {
						// Grab the panel and set the offset for where the mouse is
						_grabbed = true;
						_offset = {event->button.x - x(), event->button.y - y()};
						//std::cout << "Grabbed!" << std::endl;
					}
				}
			}
			// If we press right mb, toggle if the panel is locked
			else if (event->button.button == SDL_BUTTON_RIGHT) {
				int mx, my;
				mx = event->button.x;
				my = event->button.y;

				if (_followCamera) {
					if (mx >= x() && mx < x() + _dim.x && my >= y() && my < y() + _barHeight) {
						_locked = !_locked;	

						//vec2<int> newPos;
						//newPos = ScreenToWorld(x(), y());
						//SetPosition(newPos.x, newPos.y);
					}
				} else {
					if (mx >= x() - globalCam->x() && mx < x() - globalCam->x() + _dim.x && my >= y() - globalCam->y() && my < y() - globalCam->y() + _barHeight) {
						_locked = !_locked;	

						//vec2<int> newPos;
						//newPos = WorldToScreen(x(), y());
						//SetPosition(newPos.x, newPos.y);
					}
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			// Let go if we release the mouse button
			if (event->button.button == SDL_BUTTON_LEFT) {
				if (_grabbed) {
					_grabbed = false;
					//std::cout << "Let go!" << std::endl;
				}
			}
			break;

		case SDL_MOUSEMOTION:
			if (_grabbed) {
				//SetPosition(x() + event->motion.xrel, y() + event->motion.yrel);

				SetPosition(event->motion.x - _offset.x, event->motion.y - _offset.y);

				if (_screenBound && _followCamera) {
					if (x() < 0) SetX(0);
					else if (x() + _dim.x >= SCREEN_WIDTH) SetX(SCREEN_WIDTH - _dim.x);
					if (y() < 0) SetY(0);
					else if (y() + _dim.y >= SCREEN_HEIGHT) SetY(SCREEN_HEIGHT - _dim.y);
				}
			}
	}
}

void Panel::Update()
{

}

void Panel::Render(float interpolation, int xOffset, int yOffset)
{

}

void Panel::RenderCustom(float interpolation, int xOffset, int yOffset)
{
	int drawX = this->x();
	int drawY = this->y();

	if (!_followCamera) {
		drawX += xOffset;
		drawY += yOffset;
	}

	DrawRect(drawX, drawY, _dim.x, _dim.y, _bgColor);
	DrawRect(drawX, drawY, _dim.x, _barHeight, _barColor);
	
	// Draw title text
	DrawSmoothText(_title, consoleFont, (drawX + _dim.x / 2) + 1, (drawY + (_barHeight - 20) / 2) + 1, TextAlignment::ALIGN_CENTER, {0, 0, 0, 1});
	DrawSmoothText(_title, consoleFont, drawX + _dim.x / 2, drawY + (_barHeight - 20) / 2, TextAlignment::ALIGN_CENTER, {1, 1, 1, 1});
}

std::string Panel::title()
{
	return _title;
}

vec2<int> Panel::dim()
{
	return _dim;
}

vec4<float> Panel::bgColor()
{
	return _bgColor;
}

vec4<float> Panel::barColor()
{
	return _barColor;
}

bool Panel::focused()
{
	return _focused;
}

bool Panel::grabbed()
{
	return _grabbed;
}

bool Panel::locked()
{
	return _locked;
}

bool Panel::screenBound()
{
	return _screenBound;
}

bool Panel::followCamera()
{
	return _followCamera;
}

void Panel::SetTitle(std::string title)
{
	_title = title;
}

void Panel::SetPos(vec2<int> dim)
{
	_dim = dim;
}

void Panel::SetBgColor(vec4<float> color)
{
	_bgColor = color;
}

void Panel::SetBarColor(vec4<float> color)
{
	_barColor = color;
}

void Panel::SetLocked(bool locked)
{
	_locked = locked;
}

void Panel::SetScreenBound(bool screenBound)
{
	_screenBound = screenBound;
}

void Panel::SetFollowCamera(bool followCamera)
{
	_followCamera = followCamera;
}
