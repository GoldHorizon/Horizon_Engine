#include "../include/text.h"
#include "../include/constants.h"
#include "engineMethods.h"
#include "globals.h"

#include <iostream>

#include "SDL_ttf.h"

Text::Text() : Text("", nullptr)
{
	
}

Text::Text(std::string text, Font* font) :
	color(DEFAULT_COLOR),
	maxWidth(0),
	wrap(false),
	align(ALIGN_LEFT),
	_font(font),
	_text(text)
{
	if (_font != nullptr)
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
*/

//void Text::Update()
//{
//	// Test wrapping
//	//SetText(text() + "a ");
//}

void Text::UpdateImage()
{
	//std::cout << "DEBUG: Updating image" << std::endl;
	if (_font == nullptr)
	{
		std::cerr << "Cannot change text, no font specified!" << std::endl;
		return;
	}

	SDL_Surface* tempSurface;

	if (wrap)
		tempSurface = TTF_RenderText_Blended_Wrapped(_font->font(), _text.c_str(), color, maxWidth);
	else
		tempSurface = TTF_RenderText_Solid(_font->font(), _text.c_str(), color);

	if (align != ALIGN_LEFT)
	{
		if (align == ALIGN_CENTER)
			image()->origin = {tempSurface->w/2, 0};
		else if (align == ALIGN_RIGHT)
			image()->origin = {tempSurface->w, 0};
	}

	if (tempSurface != nullptr)
	{
		LoadImage(tempSurface);
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

void Text::SetFont(Font* font)
{
    _font = font;

	UpdateImage();
}

void Text::SetText(std::string text)
{
	_text = text;

	UpdateImage();
}

std::string Text::Serialize()
{
	std::string serialize_string = Entity::Serialize();

	serialize_string += "@Text ";

	serialize_string += "\"" + _text + "\"" + " "
		+ std::to_string(color.r) + " "
		+ std::to_string(color.g) + " "
		+ std::to_string(color.b) + " "
		+ std::to_string(color.a) + " "
		+ std::to_string(maxWidth) + " "
		+ std::to_string(wrap) + " "
		+ std::to_string(static_cast<int>(align));

	//serialize_string += " " + _font->Serialize();
	serialize_string += " \"" + _font->name() + "\"";

	return serialize_string;
}

void Text::Unserialize(std::string str)
{
	Entity::Unserialize(str);

	sVector* list = ParseSerializedString(str);

	int index = 0;

	while ((*list)[index] != "@Text" && index < list->size())
		index++;

	if ((*list)[index++] == "@Text")
	{
		_text		= (*list)[index++];
		color.r		= stoi((*list)[index++]);
		color.g		= stoi((*list)[index++]);
		color.b		= stoi((*list)[index++]);
		color.a		= stoi((*list)[index++]);
		maxWidth	= stoi((*list)[index++]);
		wrap		= (*list)[index++] == "1" ? true : false;
		int a		= stoi((*list)[index++]);
		align = static_cast<TextAlignment>(a);

		std::string f	= (*list)[index++];

		if (_font != nullptr) { 
			delete _font;
			_font = nullptr;
		}

		for (int i = 0; i < FONT_COUNT; i++)
		{
			if (f == fontList[i]->name()) {
				_font = fontList[i];
				//std::cout << "Found font with name " + f << std::endl;
				break;
			}
		}

		if (_font == nullptr)
			std::cout << "Error: Could not deserialize to a global font" << std::endl;

		UpdateImage();
		//_font->Unserialize(str);
	}
			
	delete list;
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
