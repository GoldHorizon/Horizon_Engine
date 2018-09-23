#pragma once

#include "enumerations.h"

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

	// RefreshTexture()	- Refreshes texture for alpha, color, and blend modes
	void RefreshTexture();

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
	float alpha() const;			// Returns alpha of image
	SDL_Color color() const;		// Returns color modulation, if any
	BlendMode blendMode() const;	// Returns blending mode of texture
	double angle() const;			// Returns the angle
	SDL_Point origin() const;		// Returns the origin
	int width() const;				// Returns the width of the image
	int height() const;				// Returns the height of the image
	int speed() const;				// Returns image speed
	int index() const;				// Returns image index

	// Returns sprite dimensions for sprite sheets
	SDL_Point spriteDimensions() const;

	/*
	 * Set Methods
	 */
	void SetAlpha(float alpha);		// Sets the image alpha
	void SetColor(SDL_Color color);	// Sets color modulation
	void SetBlendMode(BlendMode m); // Sets blend mode
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

	float 	_alpha;					// Image alpha
	SDL_Color _color;				// Image color modulation?
	BlendMode _blendMode;

	double	_angle;					// Image angle/rotation
	SDL_Point 	_origin;			// Image origin to draw from
	int _width;						// Image width
	int _height;					// Image height

	SDL_Point	_dimensions;		// Dimensions of an individual sprite (if using sprite sheet)

	int _speed;						// Image animation speed
	int _index;						// Image animation current index

	int _timer;						// Image timer for animation
	int _lastTime;					// Image time variable for animation
};
