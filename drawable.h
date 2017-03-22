#pragma once

#include "header.h"

class Drawable
{
public:
	/*
	 * Constructors/Destructors
	 */
	Drawable();
	explicit Drawable(SDL_Renderer* renderer);
	virtual ~Drawable();

	/*
	 * Class Methods
	 */

	// LoadFromFile() 	- Load the texture from a file
	//	file:		string with filepath to image
	void LoadFromFile(const std::string file);

	// FreeMemory() 	- Frees the texture memory used
	void FreeMemory();

	// Render() 		- Renders the texture to a position
	//	x:			x position of rendering
	//	y:			y position of rendering
	//	clipping:	rectangle the image is clipped to before rendered
	virtual void Render(float x, float y, SDL_Rect* clipping = nullptr);

	// Render() 		- Renders the texture to a position
	//	x:			x position of rendering
	//	y:			y position of rendering
	//	clipping:	rectangle the image is clipped to before rendered
	//	angle:		angle with which the image is rotated when drawing
	//	origin:		origin of rotation (BUT NOT PLACEMENT)
	//	flip:		if image is flipped (see SDL_RendererFlip enum);
	virtual void Render(float x, float y, double angle, SDL_Point* origin, SDL_RendererFlip flip, SDL_Rect* clipping = nullptr);

	// Move()			- Moves the image by an offset of x and y coordinates
	//	x:			amount to move in the x direction
	//	y:			amount to move in the y direction
	void Move(float x, float y);


	/*
	 * Get Methods
	 */
	float x() const;		// Returns the x position
	float y() const;		// Returns the y position
	int width() const;	// Returns the width of the image
	int height() const;	// Returns the height of the image

	/*
	 * Set Methods
	 */
	void SetX(float x);	// Sets the new x position
	void SetY(float y);	// Sets the new y position
	void SetPos(float x, float y);
	void SetPos(SDL_Point pos);	// Shortcut to set position

private:

	// _image			- Image stored in the drawable
	SDL_Texture* _image;
	// _renderer		- Renderer we draw to for this drawable
	SDL_Renderer* _renderer;

	float _x;			// Current x position of image
	float _y;			// Current y position of image
	int _width;			// Width of the image
	int _height;		// Height of the image
};
