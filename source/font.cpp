#include "../include/font.h"
#include "../include/constants.h"

#include <iostream>

Font::Font(std::string name) : Font(name, DEFAULT_FONT_SIZE)
{

}

Font::Font(std::string name, int size)
{
	_sdl_font = nullptr;

	SetName(name);
	SetSize(size);
}

Font::~Font()
{
	if (_sdl_font != nullptr)
	{
		FreeFont();
	}
}

void Font::LoadFont(std::string file)
{
	LoadFont(file, _size);

	/*
	if (_sdl_font != nullptr)
	{
		FreeFont();
	}

	_file = file;
	const char* fileCString = file.c_str();

	_sdl_font = TTF_OpenFont(fileCString, _size);

	if (!_sdl_font)
	{
		std::cerr << "Could not load font: " << TTF_GetError() << std::endl;
	}
	*/
}

void Font::LoadFont(std::string file, int size)
{
	if (_sdl_font != nullptr)
	{
		FreeFont();
	}

	_file = file;
	const char* fileCString = file.c_str();

	_sdl_font = TTF_OpenFont(fileCString, size);

	if (!_sdl_font)
	{
		std::cerr << "Could not load font: " << TTF_GetError() << std::endl;
	}
}

bool Font::FreeFont()
{
	if (_sdl_font != nullptr)
	{
		TTF_CloseFont(_sdl_font);
		return true;
	}
	
	std::cout << "Warning: Font already freed or did not exist!" << std::endl;
	return false;
}

int Font::size() const
{
	return _size;
}

std::string Font::name() const
{
	return _name;
}

TTF_Font* Font::font() const
{
	return _sdl_font;
}

void Font::SetSize(int size)
{
	_size = size;

	if (_file != "")
	{
		LoadFont(_file, _size);
	}
}

void Font::SetName(std::string name)
{
	_name = name;
}