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

void Image::Update()
{
	if (_dimensions.x != 0)
	{
		AdvanceImage();
	}
}

void Image::AdvanceImage()
{
	_timer += SDL_GetTicks() - _lastTime;

	_lastTime = SDL_GetTicks();

	// If imageSpeed is positive, we progress forwards through animation
	if (_speed > 0)
	{
		if (_timer > _speed)
		{
			//_timer -= _speed;
			_timer %= _speed;
			_index++;
		}
	}
	// If imageSpeed is negative, we step backwards through animation
	else if (_speed < 0)
	{
		if (_timer > abs(_speed))
		{
			//_timer -= abs(_speed);
			_timer %= abs(_speed);
			_index--;
		}
	}
	// If imageSpeed is 0 reset timer and do nothing
	else
	{
		_timer = 0;
	}

	// If we overflow on imageIndex, go back to beginning
	while (_index >= (_width / _dimensions.x))
	{
		_index -= (_width / _dimensions.x);
	}
	// If we underflow imageIndex, go to end
	while (_index < 0)
	{
		_index += (_width / _dimensions.x);
	}

	// DEBUG
	//std::cout << _timer << std::endl;
}

SDL_Texture* Image::image() const
{
	return _texture;
}

float Image::alpha() const
{
	return _alpha;
}

double Image::angle() const
{
	return _angle;
}

SDL_Point Image::origin() const
{
	return _origin;
}

int Image::width() const
{
	return _width;
}

int Image::height() const
{
	return _height;
}

int Image::speed() const
{
	return _speed;
}

int Image::index() const
{
	return _index;
}

void Image::SetAlpha(float alpha)
{
	_alpha = alpha;
}

void Image::SetAngle(double angle)
{
	_angle = angle;
}

void Image::SetOrigin(int x, int y)
{
	_origin = {x, y};
}

void Image::SetOrigin(SDL_Point pos)
{
	_origin = pos;
}

void Image::SetSpeed(int speed)
{
	_speed = speed;
}

void Image::SetIndex(int index)
{
	_index = index;
}

