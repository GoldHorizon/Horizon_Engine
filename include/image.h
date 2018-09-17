#pragma once

#include "SDL.h"

#include <string>

class Image
{
public:
	/*
	 * Constructors/Destructors
	 */
	Image();
	Image(std::string file, int spriteWidth = 0, int spriteHeight = 0);
	~Image();

	/*
	 * Class Methods
	 */
	// LoadFromFile() 	- Load the texture from a file
	//	file:			string with filepath to image
	//	spriteWidth:	width of individual sprites if loading sprite sheet
	//	spriteHeight:	height of individual sprites if loading sprite sheet
	void LoadFromFile(const std::string file, int spriteWidth = 0, int spriteHeight = 0);

	// LoadFromSurface()	- Load an existing image in code into entity
	//	surface:				preexisting texture to use
	void LoadFromSurface(SDL_Surface* surface);

	// FreeMemory() 	- Frees the texture memory used
	void FreeMemory();

	// AdvanceImage()	- Adjust image index using image speed
	void AdvanceImage();

private:
	SDL_Texture* 	_texture;	// SDL texture data stored in the image
	std::string	 	_filePath;		// File path to the image

	SDL_Renderer*	_renderer;		// Target renderer to draw to

	float 	_alpha;
	double	_angle;
	SDL_Point 	_origin;
	int _width;
	int _height;

	SDL_Point	_dimensions;

	int _speed;
	int _timer;
	int _lastTime;
	int _index;
};
