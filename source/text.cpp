#include "../include/text.h"
#include "../include/constants.h"

#include <iostream>

#include "SDL_ttf.h"

Text::Text(): Text("", nullptr)
{
	
}

Text::Text(std::string text, Font* font) :
	_font(font),
	_text(text),
	_color(DEFAULT_COLOR),
	_maxWidth(0),
	_wrap(false)
{
	SetText(text);
}

Text::~Text()
{
	FreeMemory();
}

/*
void Text::Render(float interpolation)
{
	Entity::Render(interpolation);

	//std::cout << spriteDimensions().x << ", " << spriteDimensions().y << std::endl;

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
	* /
}
*/

//void Text::Update()
//{
//	// Test wrapping
//	//SetText(text() + "a ");
//}

void Text::UpdateImage()
{
	if (_font == nullptr)
	{
		std::cerr << "Cannot change text, no font specified!" << std::endl;
		return;
	}

	SDL_Surface* tempSurface;

	if (_wrap)
		tempSurface = TTF_RenderText_Blended_Wrapped(_font->font(), _text.c_str(), _color, _maxWidth);
	else
		tempSurface = TTF_RenderText_Solid(_font->font(), _text.c_str(), _color);

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

Font* Text::font() const
{
    return _font;
}

std::string Text::text() const
{
    return _text;
}

SDL_Color Text::color() const
{
	return _color;
}

int Text::maxWidth() const
{
	return _maxWidth;
}

bool Text::wrap() const
{
	return _wrap;
}

void Text::SetFont(Font* font)
{
    _font = font;
}

void Text::SetText(std::string text)
{
	_text = text;

	UpdateImage();
}

void Text::SetColor(SDL_Color color)	// Sets the color of the text
{
	_color = color;
}

void Text::SetMaxWidth(int maxWidth)
{
	_maxWidth = maxWidth;
}

void Text::SetWrap(bool wrap)
{
	_wrap = wrap;
}

bool operator<(const Text &el, const Text &er)
{
	return (el.text() < er.text());
}
bool operator>(const Text &el, const Text &er)
{
	return (el.text() > er.text());
}
bool operator<=(const Text &el, const Text &er)
{
	return (el.text() <= er.text());
}
bool operator>=(const Text &el, const Text &er)
{
	return (el.text() >= er.text());
}
bool operator==(const Text &el, const Text &er)
{
	return (el.text() == er.text());
}
bool operator!=(const Text &el, const Text &er)
{
	return (el.text() != er.text());
}