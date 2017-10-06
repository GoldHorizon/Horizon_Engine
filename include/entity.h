#pragma once

//#include "header.h"
#include "SDL.h"
#include <string>

class Entity
{
public:
	/*
	 * Constructors/Destructors
	 */
	Entity();
	explicit Entity(SDL_Renderer* renderer);
	virtual ~Entity();

	/*
	 * Class Methods
	 */
	// LoadFromFile() 	- Load the texture from a file
	//	file:		string with filepath to image
	void LoadFromFile(const std::string file);

	// FreeMemory() 	- Frees the texture memory used
	void FreeMemory();

    // HandleEvents()   - Handles things such as user input
    virtual void HandleEvents(SDL_Event*);

	// Update()			- Updates anything to do with the entity
	virtual void Update();

	// Render()			- Renders the texture to its current position
	void Render(float interpolation);

	// Render()			- Renders the texture to its current position
	//	clipping:	rectangle the image is clipped to before rendered
	//void Render(SDL_Rect* clipping);

	// Render() 		- Renders the texture to a position
	//	flip:		how to flip the image before it is rendered
	//	clipping:	rectangle the image is clipped to before rendered
	//void Render(SDL_RendererFlip flip, SDL_Rect* clipping = nullptr);

	// Render() 		- Renders the texture to a position
	//	x:			x position of rendering
	//	y:			y position of rendering
	//void Render(float x, float y, float interpolation);

	// Move()			- Moves the image by an offset of x and y coordinates
	//	x:			amount to move in the x direction
	//	y:			amount to move in the y direction
	void Move(float x, float y);

    // NewInstance()    - Returns a new entity of a certain type
    virtual Entity* NewInstance();

	/*
	 * Get Methods
	 */
	int ID() const;					// Returns entity ID
	bool active() const;
	bool visible() const;
	float x() const;				// Returns the x position
	float y() const;				// Returns the y position
	float direction() const;		// Returns movement direction
	float speed() const;			// Returns movement speed
	float imageAlpha() const;		// Returns alpha of image
	double imageAngle() const;		// Returns the angle
	SDL_Point imageOrigin() const;	// Returns the origin
	int imageWidth() const;			// Returns the width of the image
	int imageHeight() const;		// Returns the height of the image

	/*
	 * Set Methods
	 */
	void SetID(int ID);					// Sets entity ID
	void SetActive(bool active);		// Sets if entity is active
	void SetVisible(bool visible);		// Sets if entity is visible
	void SetX(float x);					// Sets the new x position
	void SetY(float y);					// Sets the new y position
	void SetDirection(float direction);	// Sets the movement direction
	void SetSpeed(float speed);			// Sets the movement speed
	void SetImageAlpha(float alpha);	// Sets the image alpha
	void SetImageAngle(double angle);	// Sets the angle
	void SetImageOrigin(int x, int y);	// Sets the origin
	void SetImageOrigin(SDL_Point pos);	// Sets the origin
	void SetPosition(float x, float y);	// Shortcut to set position
	void SetPosition(SDL_Point pos);	// Shortcut to set position

private:

	// _image			- Image stored in the drawable
	SDL_Texture* _image;
	// _renderer		- Renderer we draw to for this drawable
	SDL_Renderer* _renderer;

	int _ID;				// ID of the entity
	bool _active;			// If entity is active or not
	bool _visible;			// If entity's image is visible
	float _x;				// Current x position of image
	float _y;				// Current y position of image
	float _direction;		// Direction the entity is moving
	float _speed;			// Speed the entity is moving at
	float _imageAlpha;		// Alpha of image
	double _imageAngle;		// Angle of image
	SDL_Point _imageOrigin;	// Origin of image
	int _imageWidth;		// Width of the image
	int _imageHeight;		// Height of the image
};
