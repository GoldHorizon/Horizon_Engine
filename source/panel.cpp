#include "panel.h"
#include "drawing.h"
#include "globals.h"
#include "engineMethods.h"

#include <iostream>

Panel::Panel()
{
	_type = PanelType::STATIC;
	_title = "Title";
	_dim = {196, 512};
	_barHeight = 24;

	_bgColor = {0, .2, .2, .9};
	_barColor = {0, .6, .6, .9};

	_focus = 1;
	_grabbed = false;
	_locked = false;
	_screenBound = true;
	_followCamera = true;

	depth = (1000);
}

Panel::~Panel()
{

}

void Panel::HandleEvents(Event& event)
{
	switch (event.ev.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			{
				int mx, my;
				mx = event.ev.button.x;
				my = event.ev.button.y;

				// Focus window if we are clicking inside of it somewhere
				if (InWindow({mx, my})) {
					event.Block();					
					Focus();
				} else {
					Unfocus();
				}

				if (_type == PanelType::FOCUS)
				{
					// If we press left mb and the panel is not locked in place...
					if (event.ev.button.button == SDL_BUTTON_LEFT && !_locked) {
						if (InTitleBar({mx, my})) {
							// Grab the panel and set the offset for where the mouse is
							_grabbed = true;
							_offset = {event.ev.button.x - this->x, event.ev.button.y - this->y};
							//std::cout << "Grabbed!" << std::endl;
						}
					}
					// If we press right mb, toggle if the panel is locked
					else if (event.ev.button.button == SDL_BUTTON_RIGHT) {
						if (InTitleBar({mx, my}) && !_grabbed) {
							SetFollowCamera(!_followCamera);
						}
					}
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (_type == PanelType::FOCUS)
			{
				// Let go if we release the mouse button
				if (event.ev.button.button == SDL_BUTTON_LEFT) {
					if (_grabbed) {
						_grabbed = false;
						//std::cout << "Let go!" << std::endl;
					}
				}
			}
			break;

		case SDL_MOUSEMOTION:
			if (_grabbed) {

				SetPosition(event.ev.motion.x - _offset.x, event.ev.motion.y - _offset.y);

				if (_screenBound && _followCamera) {
					if (this->x < 0) this->x = (0);
					else if (this->x + _dim.x >= SCREEN_WIDTH) this->x = (SCREEN_WIDTH - _dim.x);
					if (this->y < 0) this->y = (0);
					else if (this->y + _dim.y >= SCREEN_HEIGHT) this->y = (SCREEN_HEIGHT - _dim.y);
				}
			}
	}
}

void Panel::Update()
{

}

void Panel::RenderCustom(float interpolation, int xOffset, int yOffset)
{
	int drawX = this->x;
	int drawY = this->y;

	if (!_followCamera) {
		drawX += xOffset;
		drawY += yOffset;
	}

	float titleAlpha;

	if (_focus == 0 || _type == PanelType::STATIC) {
		titleAlpha = 1;

		DrawRect(drawX, drawY, _dim.x, _dim.y, _bgColor);
		DrawRect(drawX, drawY, _dim.x, _barHeight, _barColor);
	} else {
		vec4<float> bgTemp = _bgColor;
		vec4<float> barTemp = _barColor;

		bgTemp.w = .2;
		barTemp.w = .2;
		titleAlpha = .2;

		DrawRect(drawX, drawY, _dim.x, _dim.y, bgTemp);
		DrawRect(drawX, drawY, _dim.x, _barHeight, barTemp);
	}
	
	// Draw title text
	DrawSmoothText(_title, consoleFont, (drawX + _dim.x / 2) + 1, (drawY + (_barHeight - 20) / 2) + 1, TextAlignment::ALIGN_CENTER, {0, 0, 0, titleAlpha});
	DrawSmoothText(_title, consoleFont, drawX + _dim.x / 2, drawY + (_barHeight - 20) / 2, TextAlignment::ALIGN_CENTER, {1, 1, 1, titleAlpha});
}

bool Panel::InWindow(vec2<int> pos)
{
	if (_followCamera) {
		if (pos.x >= this->x 
			&& pos.x < this->x + _dim.x 
			&& pos.y >= this->y 
			&& pos.y < this->y + _dim.y)
			return true;
	} else {
		if (pos.x >= this->x - globalCam->x() 
			&& pos.x < this->x - globalCam->x() + _dim.x 
			&& pos.y >= this->y - globalCam->y() 
			&& pos.y < this->y - globalCam->y() + _dim.y) 
			return true;
	}
	return false;
}

bool Panel::InTitleBar(vec2<int> pos)
{
	if (_followCamera) {
		if (pos.x >= this->x 
			&& pos.x < this->x + _dim.x 
			&& pos.y >= this->y 
			&& pos.y < this->y + _barHeight)
			return true;
	} else {
		if (pos.x >= this->x - globalCam->x()
			&& pos.x < this->x - globalCam->x() + _dim.x 
			&& pos.y >= this->y - globalCam->y() 
			&& pos.y < this->y - globalCam->y() + _barHeight) 
			return true;
	}
	return false;
}

void Panel::Focus()
{
	if (_type == PanelType::FOCUS)
	{
		if (_focus > 0) {
			_focus = 0;
			this->depth = (1000);
		}
	}
}

void Panel::Unfocus()
{
	if (_type == PanelType::FOCUS)
	{
		_focus++;
		this->depth = (this->depth + 1);
	}
	//else if (_type == PanelType::STATIC)
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

bool Panel::focus()
{
	return _focus;
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
	if (_followCamera && !followCamera) {
		_followCamera = false;

		vec2<int> newPos;
		newPos = ScreenToWorld(this->x, this->y);
		SetPosition(newPos.x, newPos.y);
	} else if (!_followCamera && followCamera) {
		_followCamera = true;

		vec2<int> newPos;
		newPos = WorldToScreen(this->x, this->y);
		SetPosition(newPos.x, newPos.y);

		if (_screenBound) {
			if (this->x < 0) this->x = (0);
			else if (this->x + _dim.x >= SCREEN_WIDTH) this->x = (SCREEN_WIDTH - _dim.x);
			if (this->y < 0) this->y = (0);
			else if (this->y + _dim.y >= SCREEN_HEIGHT) this->y = (SCREEN_HEIGHT - _dim.y);
		}
	}
}
