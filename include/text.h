#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

#include <string>

class Text
{
	public:
		/*
		 * Constructors/Destructors
		 */
		Text();
		Text(std::string text);
		~Text();

		/*
		 * Class Methods
		 */
		// FreeMemory() 	- Frees the texture memory used
		void FreeMemory();

		// Render()			- Renders the texture to its current position
		void Render();

		/*
		 * Get Methods
		 */
		std::string text() const;
		float x() const;				// Returns the x position
		float y() const;				// Returns the y position
		float depth() const;            // Returns text depth
		float textAlpha() const;		// Returns alpha of text
		double textAngle() const;		// Returns the angle
		SDL_Point textOrigin() const;	// Returns the origin
		int textWidth() const;			// Returns the width of the text
		int textHeight() const;		// Returns the height of the text

		/*
		 * Set Methods
		 */
		void SetText(std::string text);		//
		void SetX(float x);					// Sets the new x position
		void SetY(float y);					// Sets the new y position
		void SetDepth(float depth);         // Sets the text depth
		void SetImageAlpha(float alpha);	// Sets the text alpha
		void SetImageAngle(double angle);	// Sets the angle
		void SetImageOrigin(int x, int y);	// Sets the origin
		void SetImageOrigin(SDL_Point pos);	// Sets the origin

		void SetPosition(float x, float y);	// Shortcut to set position
		void SetPosition(SDL_Point pos);	// Shortcut to set position

	private:

		// _text				- Image stored in the drawable
		std::string _text;
		// _texture				- Texture of the text
		SDL_Texture* _texture;
		

		// _renderer			- Renderer we draw to for this drawable
		SDL_Renderer* _renderer;

		float _x;				// Current x position of text
		float _y;				// Current y position of text
		float _depth;          		// Depth of text (greater value = further back)
		float _textAlpha;		// Alpha of text
		double _textAngle;		// Angle of text
		SDL_Point _textOrigin;		// Origin of text
		int _textWidth;			// Width of the loaded text
		int _textHeight;		// Height of the loaded text

		/*
		 * Operator Overloads
		 */
		friend bool operator<(const Text &el, const Text &er);
		friend bool operator>(const Text &el, const Text &er);
		friend bool operator<=(const Text &el, const Text &er);
		friend bool operator>=(const Text &el, const Text &er);
		friend bool operator==(const Text &el, const Text &er);
		friend bool operator!=(const Text &el, const Text &er);
};

bool operator<(const Text &el, const Text &er);
bool operator>(const Text &el, const Text &er);
bool operator<=(const Text &el, const Text &er);
bool operator>=(const Text &el, const Text &er);
bool operator==(const Text &el, const Text &er);
bool operator!=(const Text &el, const Text &er);
