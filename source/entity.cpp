#include "../include/entity.h"
#include "../include/globals.h"
#include "../include/constants.h"

#include <iostream>
#include <math.h>
//#include <filesystem>

#include "SDL_image.h"

Entity::Entity() :
	_image(nullptr),
	_renderer(globalRenderer),
	_ID(0),
	_active(true),
	_visible(true),
	_x(0),
	_y(0),
	_direction(0),
	_speed(0),
    _hspeed(0),
    _vspeed(0),
	_imageAlpha(1),
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
	_active(true),
	_visible(true),
	_x(0),
	_y(0),
	_direction(0),
	_speed(0),
    _hspeed(0),
    _vspeed(0),
	_imageAlpha(1),
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
	float xdir = (cos(direction() * PI / 180) * speed());
	float ydir = (sin(direction() * PI / 180) * speed());

	Move(xdir, ydir);
}

void Entity::Render(float interpolation)
{
	// Only attempt to render if we have successfully loaded an image and it is visible
	if (_image != nullptr && _visible)
	{
		// Create a set of ints to use for drawing position (use interpolation to predict movement)
		int xx = static_cast<int>(_x) - _imageOrigin.x
			   + static_cast<int>(cos(_direction * PI / 180) * _speed * (_active * interpolation));
		int yy = static_cast<int>(_y) - _imageOrigin.y
			   + static_cast<int>(sin(_direction * PI / 180) * _speed * (_active * interpolation));

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
bool Entity::active() const
{
	return _active;
}
bool Entity::visible() const
{
	return _visible;
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
float Entity::hspeed() const
{
	return _hspeed;
}
float Entity::vspeed() const
{
	return _vspeed;
}
float Entity::imageAlpha() const
{
	return _imageAlpha;
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
void Entity::SetActive(bool active)
{
	_active = active;
}
void Entity::SetVisible(bool visible)
{
	_visible = visible;
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
    
    while(_direction >= 360)
    {
        _direction -= 360;
    }
    while(_direction < 0)
    {
        _direction += 360;
    }
    
    // Change hspeed/vspeed
    _hspeed = cos(_direction * PI / 180) * _speed;
    _vspeed = sin(_direction * PI / 180) * _speed;
}
void Entity::SetSpeed(float speed)
{
    float diff = speed / _speed;
	_speed = speed;

    // Change hspeed/vspeed
    _hspeed *= diff;
    _vspeed *= diff;
}
void Entity::SetHSpeed(float hspeed)
{
	_hspeed = hspeed;

    // Change speed/direction
    if (_hspeed != 0)
    {
        _direction = atan(_vspeed / _hspeed) / PI * 180;
        if (_hspeed < 0)
        {
            _direction = 180 - _direction;
        }
    }
    else
    {
        if (_vspeed > 0)
        {
            _direction = 90;
        }
        else if (_vspeed < 0)
        {
            _direction = 270;
        }
    }

    _speed = sqrt(pow(_hspeed, 2) + pow(_vspeed, 2));
}
void Entity::SetVSpeed(float vspeed)
{
	_vspeed = vspeed;

    // Change speed/direction
    if (_hspeed != 0)
    {
        _direction = atan(_vspeed / _hspeed) / PI * 180;
        if (_hspeed < 0)
        {
            _direction = 180 - _direction;
        }
    }
    else
    {
        if (_vspeed > 0)
        {
            _direction = 90;
        }
        else if (_vspeed < 0)
        {
            _direction = 270;
        }
    }

    _speed = sqrt(pow(_hspeed, 2) + pow(_vspeed, 2));
}
void Entity::SetImageAlpha(float alpha)
{
	_imageAlpha = alpha;
	if (SDL_SetTextureAlphaMod(_image, (int)(_imageAlpha * 255)) != 0)
	{
		std::cout << IMG_GetError() << std::endl;
	}
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

