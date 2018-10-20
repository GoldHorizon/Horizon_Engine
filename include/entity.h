#pragma once

#include "image.h"
#include "event.h"

#include "SDL.h"

#include <string>
#include <sstream>

class Entity
{
	public:
		/*
		 * Constructors/Destructors
		 */
		Entity();
		virtual ~Entity();

		/*
		 * Class Methods
		 */
		// LoadImage() 		- Load the entity's image from a file
		//	file:			string with filepath to image
		//	spriteWidth:	width of individual sprites if loading sprite sheet
		//	spriteHeight:	height of individual sprites if loading sprite sheet
		void LoadImage(const std::string file, int spriteWidth = 0, int spriteHeight = 0);

		// LoadImage()		- Load an existing image in code into entity
		//	surface:		preexisting surface to use
		void LoadImage(SDL_Surface* surface);

		// FreeMemory() 	- Frees the texture memory used
		void FreeMemory();

		// HandleEvents()   - Handles things such as user input
		virtual void HandleEvents(Event&);

		// Update()			- Updates anything to do with the entity
		virtual void Update();

		// Render()			- Renders the texture to its current position
		void Render(float interpolation, int xOffset = 0, int yOffset = 0);

		// RenderCustom()	- Extra custom rendering for entities if they desire more drawing
		virtual void RenderCustom(float interpolation, int xOffset = 0, int yOffset = 0) {}

		// Move()			- Moves the image by an offset of x and y coordinates
		//	x:				amount to move in the x direction
		//	y:				amount to move in the y direction
		void Move(float x, float y);

		// NewInstance()    - Returns a new entity of a certain type
		virtual Entity* NewInstance();

		/*
		 * Serialization
		 */
		virtual std::string Serialize();
		virtual void Unserialize(std::string);

		virtual std::string SerializeFile(); 			// NEW Serialization
		virtual void DeserializeFile(std::string str); 	// NEW deserialization

		/*
		 * Get Methods
		 */
		Image* image();
		//SDL_Renderer* renderer() const;

		std::string name() const;			// Returns name of entity
		float direction() const;			// Returns movement direction
		float speed() const;				// Returns movement speed
		float hspeed() const;           	// Returns horizontal speed
		float vspeed() const;           	// Returns verticcal speed

		/*
		 * Set Methods
		 */
		void SetName(std::string name);		// Sets entity name
		void SetDirection(float direction);	// Sets the movement direction
		void SetSpeed(float speed);			// Sets the movement speed
		void SetHSpeed(float hspeed);		// Sets the movement hspeed
		void SetVSpeed(float vspeed);		// Sets the movement vspeed

		void SetPosition(float x, float y);	// Shortcut to set position
		void SetPosition(SDL_Point pos);	// Shortcut to set position

		/*
		 * Public Attributes
		 */
		int ID;					// ID of the entity
		bool active;			// If entity is active or not
		bool visible;			// If entity's image is visible
		float x;				// Current x position of image
		float y;				// Current y position of image
		float depth;			// Depth of image (greater value = further back)

	private:

		/*
		 * Public Attributes
		 */
		Image _image;			// Image stored in the entity

		std::string _name;		// Name of entity
		float _direction;		// Direction the entity is moving
		float _speed;			// Speed the entity is moving at
		float _hspeed;          // Horizontal speed of entity
		float _vspeed;          // Vertical speed of entity

		void CalculateSpeedDir();	// Calculates speed and direction based on hspeed and vspeed

		/*
		 * Operator Overloads
		 */
		friend bool operator<(const Entity &el, const Entity &er);
		friend bool operator>(const Entity &el, const Entity &er);
		friend bool operator<=(const Entity &el, const Entity &er);
		friend bool operator>=(const Entity &el, const Entity &er);
		friend bool operator==(const Entity &el, const Entity &er);
		friend bool operator!=(const Entity &el, const Entity &er);
};

bool operator<(const Entity &el, const Entity &er);
bool operator>(const Entity &el, const Entity &er);
bool operator<=(const Entity &el, const Entity &er);
bool operator>=(const Entity &el, const Entity &er);
bool operator==(const Entity &el, const Entity &er);
bool operator!=(const Entity &el, const Entity &er);
