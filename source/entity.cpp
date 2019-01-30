#include "entity.h"
//#include "types.h"
#include "globals.h"
#include "constants.h"
#include "engineMethods.h"

#include <iostream>
#include <math.h>
//#include <filesystem>

#include "SDL_image.h"

Entity::Entity() :
	ID(0),
	active(true),
	visible(true),
	x(0),
	y(0),
	depth(0),
	_name("noname"),
	_direction(0),
	_speed(0),
	_hspeed(0),
	_vspeed(0)
{
}

Entity::~Entity()
{
	FreeMemory();
}

void Entity::LoadImage(const std::string file, int spriteWidth, int spriteHeight)
{
	_image.LoadFromFile(file, spriteWidth, spriteHeight);
}

void Entity::LoadImage(SDL_Surface* surface)
{
	_image.LoadFromSurface(surface);
}

void Entity::FreeMemory()
{
	_image.FreeMemory();
}

void Entity::HandleEvents(Event& event)
{

}

void Entity::Update()
{
	float xdir = (cos(direction() * PI / 180) * speed());
	float ydir = (sin(direction() * PI / 180) * speed());

	Move(xdir, ydir);

	_image.Update();
}

void Entity::Render(float interpolation, int xOffset, int yOffset)
{
	// Only attempt to render if we have successfully loaded an image and it is visible
	if (this->visible)
	{
		// @Todo: Make it stop drawing if entity is off the screen (maybe still use render custom though?)
		// Create a set of ints to use for drawing position (use interpolation to predict movement)
		// @Todo: Need to give camera a speed so it can draw the entity properly.
		int xx = static_cast<int>(this->x) + (xOffset)
			+ static_cast<int>(cos(_direction * PI / 180) * _speed * (this->active * interpolation));
		int yy = static_cast<int>(this->y) + (yOffset)
			+ static_cast<int>(sin(_direction * PI / 180) * _speed * (this->active * interpolation));

		_image.Draw(xx, yy);

		RenderCustom(interpolation, xOffset, yOffset);
	}
}

void Entity::Move(float x, float y)
{
	this->x += x;
	this->y += y;
}

Entity* Entity::NewInstance()
{
	return nullptr;
}

bool Entity::ImageContainsPoint(vec2<int> &pt)
{
	if (image() == nullptr) return false;

	return (image() != nullptr && 
			ContainsPoint(vec2<int> {static_cast<int>(x - image()->origin.x), static_cast<int>(y - image()->origin.y)}, 
						  vec2<int> {(image()->width()), (image()->height())}, 
						  pt));
}

std::string Entity::Serialize()
{
	std::string serialize_string;

	serialize_string = "@Entity ";
	serialize_string += "\"" + _name + "\"" + " "
		+ std::to_string(active) + " "
		+ std::to_string(visible) + " "
		+ std::to_string(x) + " "
		+ std::to_string(y) + " "
		+ std::to_string(depth) + " "
		+ std::to_string(_direction) + " "
		+ std::to_string(_speed) + " "
		+ std::to_string(_hspeed) + " "
		+ std::to_string(_vspeed) + " ";

	return serialize_string;
}

void Entity::Unserialize(std::string str)
{
	sVector* list = ParseSerializedString(str);

	size_t index = 0;

	while ((*list)[index] != "@Entity" && index < list->size())
		index++;

	if ((*list)[index++] == "@Entity")
	{
		//_imagePath 			= (*list)[index++];
		_name 				= (*list)[index++];
		active 				= (*list)[index++] == "1" ? true : false;	
		visible 			= (*list)[index++] == "1" ? true : false;	
		x					= std::stof((*list)[index++]);	
		y					= std::stof((*list)[index++]);
		depth 				= std::stof((*list)[index++]);
		_direction 			= std::stof((*list)[index++]);
		_speed 				= std::stof((*list)[index++]);
		_hspeed 			= std::stof((*list)[index++]);
		_vspeed 			= std::stof((*list)[index++]);
	}

	delete list;
}

std::string Entity::SerializeFile()
{
	return Serialize();
}

void Entity::DeserializeFile(std::string str)
{
	Unserialize(str);
}

/*
 * Get Methods
 */
Image* Entity::image()
{
	return &_image;
}

//SDL_Renderer* Entity::renderer() const
//{
//	return _renderer;
//}

std::string Entity::name() const
{
	return _name;
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
//float Entity::imageAlpha() const
//{
//	return _imageAlpha;
//}
//double Entity::imageAngle() const
//{
//	return _imageAngle;
//}
//SDL_Point Entity::imageOrigin() const
//{
//	return _imageOrigin;
//}
//int Entity::imageWidth() const
//{
//	return _imageWidth;
//}
//int Entity::imageHeight() const
//{
//	return _imageHeight;
//}
//int Entity::imageSpeed() const
//{
//	return _imageSpeed;
//}
//int Entity::imageIndex() const
//{
//	return _imageIndex;
//}
//SDL_Point Entity::spriteDimensions() const
//{
//	return _spriteDimensions;
//}

/*
 * Set Methods
 */
void Entity::SetName(std::string name)
{
	if (name != "")
	{
		_name = name;
	}
	else
	{
		_name = "NoName";
	}
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
	if (_speed != 0)
	{
		float diff = speed / _speed;

		// Change hspeed/vspeed
		_hspeed *= diff;
		_vspeed *= diff;
	}
	else
	{
		_hspeed = cos(_direction * PI / 180) * speed;
		_vspeed = sin(_direction * PI / 180) * speed;
	}

	_speed = speed;
}
void Entity::SetHSpeed(float hspeed)
{
	_hspeed = hspeed;

	// Change speed/direction
	CalculateSpeedDir();
}
void Entity::SetVSpeed(float vspeed)
{
	_vspeed = vspeed;

	// Change speed/direction
	CalculateSpeedDir();
}
//void Entity::SetImageAlpha(float alpha)
//{
//	_imageAlpha = alpha;
//	if (SDL_SetTextureAlphaMod(_image, (int)(_imageAlpha * 255)) != 0)
//	{
//		std::cout << IMG_GetError() << std::endl;
//	}
//}
//void Entity::SetImageAngle(double angle)
//{
//	_imageAngle = angle;
//}
//void Entity::SetImageOrigin(int x, int y)
//{
//	_imageOrigin.x = x;
//	_imageOrigin.y = y;
//}
//void Entity::SetImageOrigin(SDL_Point pos)
//{
//	_imageOrigin.x = pos.x;
//	_imageOrigin.y = pos.y;
//}
//void Entity::SetImageSpeed(int speed)
//{
//	_imageSpeed = speed;
//}
//void Entity::SetImageIndex(int index)
//{
//	_imageIndex = index;
//}

void Entity::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}
void Entity::SetPosition(SDL_Point pos)
{
	this->x = pos.x;
	this->y = pos.y;
}

void Entity::CalculateSpeedDir()
{
	// Change speed/direction
	if (_hspeed != 0)
	{
		_direction = atan(_vspeed / _hspeed) / PI * 180;
		if (_hspeed > 0)
		{
			//_direction = 180 - _direction;
		}
		else
		{
			_direction = 180 + _direction;
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

	while (_direction >= 360)
	{
		_direction -= 360;
	}
	while (_direction < 0)
	{
		_direction += 360;
	}

	_speed = sqrt(pow(_hspeed, 2) + pow(_vspeed, 2));
}

bool operator<(const Entity &el, const Entity &er)
{
	return el.depth < er.depth;
}
bool operator>(const Entity &el, const Entity &er)
{
	return el.depth > er.depth;
}
bool operator<=(const Entity &el, const Entity &er)
{
	return el.depth <= er.depth;
}
bool operator>=(const Entity &el, const Entity &er)
{
	return el.depth >= er.depth;
}
bool operator==(const Entity &el, const Entity &er)
{
	return el.depth == er.depth;
}
bool operator!=(const Entity &el, const Entity &er)
{
	return el.depth != er.depth;
}
