#include "../include/text.h"
#include "../include/globals.h"
#include "../include/constants.h"

#include <iostream>

#include "SDL_ttf.h"

Text::Text(): Text("", nullptr)
{
	
}

Text::Text(std::string text, Font* font) :
	_font(font),
	_text(text),
	_textAlpha(1),
	_textAngle(0),
	_textOrigin({ 0, 0 }),
	_color(DEFAULT_COLOR)
{
	SetText(text);
}

Text::~Text()
{
	FreeMemory();
}

void Text::Render(float interpolation)
{
	Entity::Render(interpolation);

	std::cout << spriteDimensions().x << ", " << spriteDimensions().y << std::endl;

	/*
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
	*/
}

void Text::Update()
{
	SetText(text() + "a");
}

Font* Text::font() const
{
    return _font;
}

std::string Text::text() const
{
    return _text;
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

SDL_Color Text::color() const
{
	return _color;
}

void Text::SetFont(Font* font)
{
    _font = font;
}

void Text::SetText(std::string text)
{
	_text = text;

	if (_font == nullptr)
	{
		std::cerr << "Cannot change text, no font specified!" << std::endl;
		return;
	}
	
	SDL_Surface* tempSurface = TTF_RenderText_Solid(_font->font(), _text.c_str(), _color);

	if (tempSurface != nullptr)
	{
		LoadFromSurface(tempSurface);
		SDL_FreeSurface(tempSurface);
	}
	else
	{
		std::cerr << TTF_GetError() << std::endl;
	}
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

void Text::SetColor(SDL_Color color)	// Sets the color of the text
{
	_color = color;
}
