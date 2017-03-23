#include "../entity.h"
#include "../globals.h"
#include <iostream>
#include "SDL2/SDL_image.h"

Entity::Entity():
	_image(nullptr),
	_renderer(globalRenderer),
	_ID(0),
	_x(0),
	_y(0),
	_angle(0),
	_width(0),
	_height(0)
{
	_origin = {0, 0};

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
	_angle(0),
	_width(0),
	_height(0)
{
	_origin = {0, 0};

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
	// Create a temporary surface to load our image onto
	SDL_Surface* tempSurface;
	tempSurface = IMG_Load(file.c_str());

	if (tempSurface != nullptr)
	{
		// Set our attributes to match image properties
		_image = SDL_CreateTextureFromSurface(_renderer, tempSurface);
		_width = tempSurface->w;
		_height = tempSurface->h;

		// Free up our surface when we're done
		SDL_FreeSurface(tempSurface);
	}
	else
	{
		std::cout << "Error loading file: " + file << std::endl;
	}//	else
	//	{
	//		//std::cout << "Error: _image not found..." << std::endl;
	//	}
}

void Entity::FreeMemory()
{
	if (_image != nullptr)
	{
		SDL_DestroyTexture(_image);
		_width = 0;
		_height = 0;
	}
}

void Entity::Update()
{

}

void Entity::Render()
{
	if (_image != nullptr)
	{
		// Create a set of ints to use for drawing position
		int xx = static_cast<int>(_x) - _origin.x;
		int yy = static_cast<int>(_y) - _origin.y;

		// Create a rectangle to put on display
		SDL_Rect displayImage = {xx, yy, _width, _height};

		SDL_RenderCopyEx(_renderer, _image, nullptr, &displayImage, _angle, &_origin, SDL_FLIP_NONE);
	}
}

void Entity::Render(SDL_Rect* clipping)
{
	if (_image != nullptr)
	{
		// Create a set of ints to use for drawing position
		int xx = static_cast<int>(_x) - _origin.x;
		int yy = static_cast<int>(_y) - _origin.y;

		// Create a rectangle to put on display
		SDL_Rect displayImage = {xx, yy, _width, _height};

		// If we are clipping the sprite, adjust it
		if (clipping != nullptr)
		{
			displayImage.w = clipping->w;
			displayImage.h = clipping->h;
		}

		SDL_RenderCopyEx(_renderer, _image, clipping, &displayImage, _angle, &_origin, SDL_FLIP_NONE);
	}
//	else
//	{
//		//std::cout << "Error: _image not found..." << std::endl;
//	}
}

void Entity::Render(SDL_RendererFlip flip, SDL_Rect* clipping)
{
	if (_image != nullptr)
	{
		// Create a set of ints to use for drawing position
		int xx = static_cast<int>(_x) - _origin.x;
		int yy = static_cast<int>(_y) - _origin.y;

		// Create a rectangle to put on display
		SDL_Rect displayImage = {xx, yy, _width, _height};

		// If we are clipping the sprite, adjust it
		if (clipping != nullptr)
		{
			displayImage.w = clipping->w;
			displayImage.h = clipping->h;
		}

		SDL_RenderCopyEx(_renderer, _image, clipping, &displayImage, _angle, &_origin, flip);
//		SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
//		SDL_RenderDrawRect(_renderer, &displayImage);
	}
//	else
//	{
//		//std::cout << "Error: _image not found..." << std::endl;
//	}
}

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

double Entity::angle() const
{
	return _angle;
}

SDL_Point Entity::origin() const
{
	return _origin;
}

int Entity::width() const
{
	return _width;
}

int Entity::height() const
{
	return _height;
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

void Entity::SetAngle(double angle)
{
	_angle = angle;
}

void Entity::SetOrigin(int x, int y)
{
	_origin.x = x;
	_origin.y = y;
}

void Entity::SetOrigin(SDL_Point pos)
{
	_origin.x = pos.x;
	_origin.y = pos.y;
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

