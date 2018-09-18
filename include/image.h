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

	// Update()			- Updates the image
	void Update();

	// Draw()			- Draws the image at the specified coordinates
	void Draw(int x, int y);

	/*
	 * Get Methods
	 */
	SDL_Texture* image() const;
	float alpha() const;		// Returns alpha of image
	double angle() const;		// Returns the angle
	SDL_Point origin() const;	// Returns the origin
	int width() const;			// Returns the width of the image
	int height() const;			// Returns the height of the image
	int speed() const;			// Returns image speed
	int index() const;			// Returns image index

	// Returns sprite dimensions for sprite sheets
	SDL_Point spriteDimensions() const;

	/*
	 * Set Methods
	 */
	void SetAlpha(float alpha);		// Sets the image alpha
	void SetAngle(double angle);	// Sets the angle
	void SetOrigin(int x, int y);	// Sets the origin
	void SetOrigin(SDL_Point pos);	// Sets the origin
	void SetSpeed(int speed);		// Sets image speed in ms
	void SetIndex(int index);		// Sets image index

private:
	/*
	 * Private Methods
	 */
	// Advance()	- Adjust image index using image speed
	void Advance();

	/*
	 * Attributes
	 */
	SDL_Texture* 	_texture;		// SDL texture data stored in the image
	std::string	 	_filePath;		// File path to the image

	SDL_Renderer*	_renderer;		// Target renderer to draw to

	float 	_alpha;
	double	_angle;
	SDL_Point 	_origin;
	int _width;
	int _height;

	SDL_Point	_dimensions;

	int _speed;
	int _index;

	int _timer;
	int _lastTime;
};
