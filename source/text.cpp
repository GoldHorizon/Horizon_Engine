#include "../include/text.h"
#include "../include/globals.h"
#include "../include/constants.h"

#include <iostream>

#include "SDL_ttf.h"

Text::Text()
{
	
}

Text::Text(std::string text):
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

void Text::SetText(std::string text)
{
	_text = text;	
}
