#include "../include/text.h"
#include "../include/constants.h"
#include "engineMethods.h"

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
	_wrap(false),
	_align(ALIGN_LEFT)
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

	if (_align != ALIGN_LEFT)
	{
		if (_align == ALIGN_CENTER)
			SetImageOrigin(tempSurface->w/2, 0);
		else if (_align == ALIGN_RIGHT)
			SetImageOrigin(tempSurface->w, 0);
	}

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

TextAlignment Text::align() const
{
	return _align;
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

void Text::SetAlign(TextAlignment align)
{
	_align = align;
}

std::string Text::Serialize()
{
	std::string serialize_string = Entity::Serialize();

	serialize_string += "Text ";

	serialize_string += "\"" + _text + "\"" + " "
		+ std::to_string(_color.r) + " "
		+ std::to_string(_color.g) + " "
		+ std::to_string(_color.b) + " "
		+ std::to_string(_color.a) + " "
		+ std::to_string(_maxWidth) + " "
		+ std::to_string(_wrap) + " "
		+ std::to_string(static_cast<int>(_align));

	serialize_string += " " + _font->Serialize();

	return serialize_string;
}

void Text::Unserialize(std::string str)
{
	Entity::Unserialize(str);

	sVector* list = ParseSerializedString(str);

	int index = 0;

	while ((*list)[index] != "Text" && index < list->size())
		index++;

	if ((*list)[index++] == "Text")
	{
		_text			= (*list)[index++];
		_color.r		= stoi((*list)[index++]);
		_color.g		= stoi((*list)[index++]);
		_color.b		= stoi((*list)[index++]);
		_color.a		= stoi((*list)[index++]);
		_maxWidth		= stoi((*list)[index++]);
		_wrap			= (*list)[index++] == "1" ? true : false;
		int a;
		a				= stoi((*list)[index++]);
		_align = static_cast<TextAlignment>(a);

		UpdateImage();

		_font->Unserialize(str);
	}
			
	delete list;

	//std::stringstream stream(str);
	//std::string temp;

	//stream >> temp;
	//while (stream)
	//{
	//	//std::cout << temp << std::endl;
	//	if (temp == "Text") 
	//	{
	//		stream >> _text;
	//		stream >> _color.r;
	//		stream >> _color.g;
	//		stream >> _color.b;
	//		stream >> _color.a;
	//		stream >> _maxWidth;
	//		stream >> _wrap;
	//		int a;
	//		stream >> a;
	//		_align = static_cast<TextAlignment>(a);

	//		UpdateImage();

	//		_font->Unserialize(str);

	//		break;
	//	}

	//	stream >> temp;
	//}
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
