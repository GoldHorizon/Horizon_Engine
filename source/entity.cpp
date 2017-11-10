#include "../include/entity.h"
#include "../include/globals.h"
#include "../include/constants.h"

#include <iostream>
#include <math.h>
#include <filesystem>

#include "SDL_image.h"

Entity::Entity():
	_image(nullptr),
	_renderer(globalRenderer),
	_ID(0),
	_x(0),
	_y(0),
	_direction(0),
	_speed(0),
	_imageAngle(0),
	_imageWidth(0),
	_imageHeight(0)
{
	_imageOrigin = {0, 0};

	if (globalRenderer == nullptr)
	{
		std::cerr << "Error: Cannot instantiate object - globalRenderer not set!" << std::endl;
	}
}

Entity::Entity(SDL_Renderer* renderer):
	_image(nullptr),
	_renderer(renderer),
	_ID(0),
	_x(0),
	_y(0),
	_direction(0),
	_speed(0),
	_imageAngle(0),
	_imageWidth(0),
	_imageHeight(0)
{
	_imageOrigin = {0, 0};

	if (renderer == nullptr)
	{
		std::cerr << "Error: Cannot instantiate object - globalRenderer not set!" << std::endl;
	}
}

Entity::~Entity()
{
	FreeMemory();
}

void Entity::LoadFromFile(const std::string file)
{
	//std::string fullPath = std::experimental::filesystem::current_path().string() + "\\" + file;
	
	// Create a temporary surface to load our image onto
	SDL_Surface* tempSurface;
	tempSurface = IMG_Load(file.c_str());

	if (tempSurface != nullptr)
	{
		// Set our attributes to match image properties
		_image = SDL_CreateTextureFromSurface(_renderer, tempSurface);
		_imageWidth = tempSurface->w;
		_imageHeight = tempSurface->h;

		// Free up our surface when we're done
		SDL_FreeSurface(tempSurface);
	}
	else
	{
		//std::cout << "Error loading file: " + fullPath << std::endl;
		std::cout << IMG_GetError() << std::endl;
	}
}

void Entity::FreeMemory()
{
	if (_image != nullptr)
	{
		SDL_DestroyTexture(_image);
		_imageWidth = 0;
		_imageHeight = 0;
	}
}

void Entity::HandleEvents(SDL_Event*)
{

}

void Entity::Update()
{

}

void Entity::Render(float interpolation)
{
	// Only attempt to render if we have successfully loaded an image
	if (_image != nullptr)
	{
		// Create a set of ints to use for drawing position (use interpolation to predict movement)
		int xx = static_cast<int>(_x) - _imageOrigin.x
			   + static_cast<int>(cos(_direction * PI / 180) * _speed * interpolation);
		int yy = static_cast<int>(_y) - _imageOrigin.y
			   + static_cast<int>(sin(_direction * PI / 180) * _speed * interpolation);

		// Create a rectangle to put on display
		SDL_Rect displayImage = {xx, yy, _imageWidth, _imageHeight};

		SDL_RenderCopyEx(_renderer, _image, nullptr, &displayImage, _imageAngle, &_imageOrigin, SDL_FLIP_NONE);
	}
}

//void Entity::Render(SDL_Rect* clipping)
//{
//	if (_image != nullptr)
//	{
//		// Create a set of ints to use for drawing position
//		int xx = static_cast<int>(_x) - _imageOrigin.x;
//		int yy = static_cast<int>(_y) - _imageOrigin.y;
//
//		// Create a rectangle to put on display
//		SDL_Rect displayImage = {xx, yy, _imageWidth, _imageHeight};
//
//		// If we are clipping the sprite, adjust it
//		if (clipping != nullptr)
//		{
//			displayImage.w = clipping->w;
//			displayImage.h = clipping->h;
//		}
//
//		SDL_RenderCopyEx(_renderer, _image, clipping, &displayImage, _imageAngle, &_imageOrigin, SDL_FLIP_NONE);
//	}
////	else
////	{
////		//std::cout << "Error: _image not found..." << std::endl;
////	}
//}

//void Entity::Render(SDL_RendererFlip flip, SDL_Rect* clipping)
//{
//	if (_image != nullptr)
//	{
//		// Create a set of ints to use for drawing position
//		int xx = static_cast<int>(_x) - _imageOrigin.x;
//		int yy = static_cast<int>(_y) - _imageOrigin.y;
//
//		// Create a rectangle to put on display
//		SDL_Rect displayImage = {xx, yy, _imageWidth, _imageHeight};
//
//		// If we are clipping the sprite, adjust it
//		if (clipping != nullptr)
//		{
//			displayImage.w = clipping->w;
//			displayImage.h = clipping->h;
//		}
//
//		SDL_RenderCopyEx(_renderer, _image, clipping, &displayImage, _imageAngle, &_imageOrigin, flip);
////		SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
////		SDL_RenderDrawRect(_renderer, &displayImage);
//	}
////	else
////	{
////		//std::cout << "Error: _image not found..." << std::endl;
////	}
//}

//void Drawable::Render(float x, float y, double angle, SDL_Point* origin, SDL_RendererFlip flip, SDL_Rect* clipping)
//{
//	// Set our member variables to the new drawing position
//	_x = x;
//	_y = y;
//
//	if (_image != nullptr)
//	{
//		// Create a set of ints to use for drawing position
//		int xx = static_cast<int>(x);
//		int yy = static_cast<int>(y);
//
//		// Create a rectangle to put on display
//		SDL_Rect displayImage = {xx, yy, _width, _height};
//		//std::cout << clipping->x << " " << clipping->y << " " << clipping->w << " " << clipping->h << " " << std::endl;
//
//		// If we are clipping the sprite, adjust it
//		if (clipping != nullptr)
//		{
//			displayImage.w = clipping->w;
//			displayImage.h = clipping->h;
//		}
//
//		SDL_RenderCopyEx(_renderer, _image, clipping, &displayImage, angle, origin, flip);
//	}
////	else
////	{
////		//std::cout << "Error: _image not found..." << std::endl;
////	}
//}

void Entity::Move(float x, float y)
{
	_x += x;
	_y += y;
}

Entity* Entity::NewInstance()
{
	return nullptr;
}

/*
 * Get Methods
 */
int Entity::ID() const
{
	return _ID;
}

float Entity::x() const
{
	return _x;
}

float Entity::y() const
{
	return _y;
}

float Entity::direction() const
{
	return _direction;
}

float Entity::speed() const
{
	return _speed;
}

double Entity::imageAngle() const
{
	return _imageAngle;
}

SDL_Point Entity::imageOrigin() const
{
	return _imageOrigin;
}

int Entity::imageWidth() const
{
	return _imageWidth;
}

int Entity::imageHeight() const
{
	return _imageHeight;
}

/*
 * Set Methods
 */
void Entity::SetID(int ID)
{
	_ID = ID;
}

void Entity::SetX(float x)
{
	_x = x;
}

void Entity::SetY(float y)
{
	_y = y;
}

void Entity::SetDirection(float direction)
{
	_direction = direction;
}

void Entity::SetSpeed(float speed)
{
	_speed = speed;
}

void Entity::SetImageAngle(double angle)
{
	_imageAngle = angle;
}

void Entity::SetImageOrigin(int x, int y)
{
	_imageOrigin.x = x;
	_imageOrigin.y = y;
}

void Entity::SetImageOrigin(SDL_Point pos)
{
	_imageOrigin.x = pos.x;
	_imageOrigin.y = pos.y;
}

void Entity::SetPosition(float x, float y)
{
	_x = x;
	_y = y;
}

void Entity::SetPosition(SDL_Point pos)
{
	_x = pos.x;
	_y = pos.y;
}

