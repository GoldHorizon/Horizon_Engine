#include "../include/text.h"
#include "../include/globals.h"
#include "../include/constants.h"

#include <iostream>

#include "SDL_ttf.h"

Text::Text(): Text("")
{
	
}

Text::Text(std::string text):
    _font(nullptr),
	_text(text),
	_renderer(globalRenderer),
	_x(0),
	_y(0),
	_depth(0),
	_textAlpha(1),
	_textAngle(0),
	_textOrigin({0, 0}),
	_textWidth(0),
	_textHeight(0)
{
	SetText(text);
}

Text::~Text()
{
	FreeMemory();
}

void Text::FreeMemory()
{
	if (_texture != nullptr)
	{
		SDL_DestroyTexture(_texture);
		_textWidth = 0;
		_textHeight = 0;
		_text = "";
	}
}

void Text::Render()
{
	if (_texture != nullptr)
	{
		int xx = static_cast<int>(_x) - _textOrigin.x;
		int yy = static_cast<int>(_y) - _textOrigin.y;

		SDL_Rect* sourceImage = nullptr;
		SDL_Rect* displayImage = nullptr;

		sourceImage = new SDL_Rect { 0, 0, _textWidth, _textHeight };
		displayImage = new SDL_Rect { xx, yy, _textWidth, _textHeight };

		SDL_RenderCopyEx(_renderer, _texture, sourceImage, displayImage, _textAngle, &_textOrigin, SDL_FLIP_NONE);

		if (sourceImage != nullptr)
				delete sourceImage;
		delete displayImage;
	}
}

TTF_Font* Text::font() const
{
    return _font;
}

std::string Text::text() const
{
    return _text;
}

float Text::x() const
{
    return _x;
}   

float Text::y() const
{
    return _y;
}

float Text::depth() const
{
    return _depth;
}

float Text::textAlpha() const
{
    return _textAlpha;
}

double Text::textAngle() const
{
    return _textAngle;
}

SDL_Point Text::textOrigin() const
{
    return _textOrigin;
}

int Text::textWidth() const
{
    return _textWidth;
}

int Text::textHeight() const
{
    return _textHeight;
}

void Text::SetFont(TTF_Font* font)
{
    _font = font;
}

void Text::SetText(std::string text)
{
	_text = text;	
}

void Text::SetX(float x)					// Sets the new x position
{
    _x = x;
}

void Text::SetY(float y)					// Sets the new y position
{
    _y = y;
}

void Text::SetDepth(float depth)          // Sets the text depth
{
    _depth = depth;
}

void Text::SetImageAlpha(float alpha) 	// Sets the text alpha
{
    _textAlpha = alpha;
}

void Text::SetImageAngle(double angle)	// Sets the angle
{
    _textAngle = angle;
}

void Text::SetImageOrigin(int x, int y)	// Sets the origin
{
    _textOrigin = {x, y};
}

void Text::SetImageOrigin(SDL_Point pos)	// Sets the origin
{
    _textOrigin = pos;
}

void Text::SetPosition(float x, float y)	// Shortcut to set position
{
    _x = x;
    _y = y;
}

void Text::SetPosition(SDL_Point pos) 	// Shortcut to set position
{
    _x = pos.x;
    _y = pos.y;
}


