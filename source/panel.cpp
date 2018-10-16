#include "panel.h"
#include "drawing.h"
#include "globals.h"
#include "engineMethods.h"

#include <iostream>

Panel::Panel()
{
	title = "Title";
	type = PanelType::STATIC;
	bgColor = {0, .2, .2, .9};
	barColor = {0, .6, .6, .9};
	locked = false;

	_size = {196, 512};
	_barHeight = 24;
	_focus = 1;
	_grabbed = false;
	_screenBound = true;
	_followCamera = true;

	depth = 1000;
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

				if (type == PanelType::FOCUS)
				{
					// If we press left mb and the panel is not locked in place...
					if (event.ev.button.button == SDL_BUTTON_LEFT && !locked) {
						if (InTitleBar({mx, my})) {
							// Grab the panel and set the offset for where the mouse is
							_grabbed = true;
							_offset = {(int)(event.ev.button.x - this->x), (int)(event.ev.button.y - this->y)};
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
			if (type == PanelType::FOCUS)
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
					else if (this->x + _size.x >= SCREEN_WIDTH) this->x = (SCREEN_WIDTH - _size.x);
					if (this->y < 0) this->y = (0);
					else if (this->y + _size.y >= SCREEN_HEIGHT) this->y = (SCREEN_HEIGHT - _size.y);
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

	if (_focus == 0 || type == PanelType::STATIC) {
		titleAlpha = 1;

		DrawRect(drawX, drawY, _size.x, _size.y, bgColor);
		DrawRect(drawX, drawY, _size.x, _barHeight, barColor);
	} else {
		vec4<float> bgTemp = bgColor;
		vec4<float> barTemp = barColor;

		bgTemp.w = .2;
		barTemp.w = .2;
		titleAlpha = .2;

		DrawRect(drawX, drawY, _size.x, _size.y, bgTemp);
		DrawRect(drawX, drawY, _size.x, _barHeight, barTemp);
	}
	
	// Draw title text
	if (title != "") {
		DrawSmoothText(title, consoleFont, (drawX + _size.x / 2) + 1, (drawY + (_barHeight - 20) / 2) + 1, TextAlignment::ALIGN_CENTER, {0, 0, 0, titleAlpha});
		DrawSmoothText(title, consoleFont, drawX + _size.x / 2, drawY + (_barHeight - 20) / 2, TextAlignment::ALIGN_CENTER, {1, 1, 1, titleAlpha});
	}
}

bool Panel::InWindow(vec2<int> pos)
{
	if (_followCamera) {
		if (pos.x >= this->x 
			&& pos.x < this->x + _size.x 
			&& pos.y >= this->y 
			&& pos.y < this->y + _size.y)
			return true;
	} else {
		if (pos.x >= this->x - globalCam->x() 
			&& pos.x < this->x - globalCam->x() + _size.x 
			&& pos.y >= this->y - globalCam->y() 
			&& pos.y < this->y - globalCam->y() + _size.y) 
			return true;
	}
	return false;
}

bool Panel::InTitleBar(vec2<int> pos)
{
	if (_followCamera) {
		if (pos.x >= this->x 
			&& pos.x < this->x + _size.x 
			&& pos.y >= this->y 
			&& pos.y < this->y + _barHeight)
			return true;
	} else {
		if (pos.x >= this->x - globalCam->x()
			&& pos.x < this->x - globalCam->x() + _size.x 
			&& pos.y >= this->y - globalCam->y() 
			&& pos.y < this->y - globalCam->y() + _barHeight) 
			return true;
	}
	return false;
}

void Panel::Focus()
{
	if (type == PanelType::FOCUS)
	{
		if (_focus > 0) {
			_focus = 0;
			this->depth = (1000);
		}
	}
	//else if (type == PanelType::STATIC)
}

void Panel::Unfocus()
{
	if (type == PanelType::FOCUS)
	{
		_focus++;
		this->depth = (this->depth + 1);
	}
	//else if (type == PanelType::STATIC)
}

vec2<int> Panel::size()
{
	return _size;
}

bool Panel::focus()
{
	return _focus;
}

bool Panel::grabbed()
{
	return _grabbed;
}

bool Panel::followCamera()
{
	return _followCamera;
}

void Panel::SetSize(vec2<int> size)
{
	_size = size;

	// May add more here later, so if we resize a panel at the
	// edge of the screen and it needs to stay on screen, it
	// can jump to the correct location.
}

void Panel::SetScreenBound(bool screenBound)
{
	_screenBound = screenBound;
	
	if (_screenBound) {
		if (this->x < 0) this->x = (0);
		else if (this->x + _size.x >= SCREEN_WIDTH) this->x = (SCREEN_WIDTH - _size.x);
		if (this->y < 0) this->y = (0);
		else if (this->y + _size.y >= SCREEN_HEIGHT) this->y = (SCREEN_HEIGHT - _size.y);
	}
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
			else if (this->x + _size.x >= SCREEN_WIDTH) this->x = (SCREEN_WIDTH - _size.x);
			if (this->y < 0) this->y = (0);
			else if (this->y + _size.y >= SCREEN_HEIGHT) this->y = (SCREEN_HEIGHT - _size.y);
		}
	}
}
