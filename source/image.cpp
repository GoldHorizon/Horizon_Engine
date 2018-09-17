#include "image.h"
#include "globals.h"

#include "SDL_image.h"

#include <iostream>

Image::Image() : Image("")
{

}

Image::Image(std::string file, int spriteWidth, int spriteHeight) :
	_texture(nullptr),
	_filePath(file),
	_renderer(globalRenderer),
	_alpha(1),
	_angle(0),
	_origin({0, 0}),
	_width(0),
	_height(0),
	_dimensions({0, 0}),
	_speed(0),
	_timer(0),
	_lastTime(0),
	_index(0)
{
	if (file != "")
		LoadFromFile(file, spriteWidth, spriteHeight);

}

Image::~Image()
{

}

void Image::LoadFromFile(const std::string file, int spriteWidth, int spriteHeight)
{
	// Create a temporary surface to load our image onto
	SDL_Surface* tempSurface;
	tempSurface = IMG_Load(file.c_str());

	if (tempSurface != nullptr)
	{
		// Set our attributes to match image properties
		_texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);

		_width = tempSurface->w;
		_height = tempSurface->h;

		// If what we are loading in is not a sprite sheet:
		if (spriteWidth != 0 && spriteHeight != 0)
		{
			_dimensions.x = spriteWidth;
			_dimensions.y = spriteHeight;
		}

		// Free up our surface when we're done
		SDL_FreeSurface(tempSurface);

		_filePath = file;

		// DEBUG
		//std::cout << _imageWidth << std::endl
		//	<< _imageHeight << std::endl
		//	<< _spriteDimensions.x << std::endl
		//	<< _spriteDimensions.y << std::endl << std::endl;
	}
	else
	{
		//std::cout << "Error loading file: " + fullPath << std::endl;
		std::cout << IMG_GetError() << std::endl;
	}
}

void Image::LoadFromSurface(SDL_Surface* surface)
{
	if (surface != nullptr)
	{
		if (_texture != nullptr)
			FreeMemory();

		_texture = SDL_CreateTextureFromSurface(_renderer, surface);
		_filePath = "nopath";

		_width = surface->w;
		_height = surface->h;

		//std::cout << "Surface dimensions: " << surface->w << ", " << surface->h << std::endl;
	}
	else
	{
		std::cerr << "Error loading null surface." << std::endl;
	}
}

void Image::FreeMemory()
{
	if (_texture != nullptr)
	{
		SDL_DestroyTexture(_texture);
		_width = 0;
		_height = 0;
	}
}

