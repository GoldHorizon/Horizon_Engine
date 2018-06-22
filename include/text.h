#pragma once

#include <string>

#include "entity.h"
#include "font.h"

#include "SDL.h"
#include "SDL_ttf.h"

class Text: public Entity
{
	public:
		/*
		 *  Constructors/Destructors
		 */
		Text();
		Text(std::string text, Font* font);
		~Text();

		/*
		 * Class Methods
		 */
		// Render()			- Renders the texture to its current position
		void Render(float interpolation);

		/*
		 * Get Methods
		 */
        Font* font() const;         // Returns the font used
		std::string text() const;       // Returns the text displayed
		float textAlpha() const;		// Returns alpha of text
		double textAngle() const;		// Returns the angle
		SDL_Point textOrigin() const;	// Returns the origin
		int textWidth() const;			// Returns the width of the text
		int textHeight() const;		    // Returns the height of the text
		SDL_Color color() const;		// Returns the color of the text

		/*
		 * Set Methods
		 */
        void SetFont(Font* font);       // Sets the font being used
		void SetText(std::string text);		// Sets the text being displayed
		void SetImageAlpha(float alpha);	// Sets the text alpha
		void SetImageAngle(double angle);	// Sets the angle
		void SetImageOrigin(int x, int y);	// Sets the origin
		void SetImageOrigin(SDL_Point pos);	// Sets the origin
		void SetColor(SDL_Color color);		// Sets the text color

	private:

        // _font                - Font associated with the text
        Font* _font;

		// _text				- Image stored in the drawable
		std::string _text;

		float _textAlpha;		// Alpha of text
		double _textAngle;		// Angle of text
		SDL_Point _textOrigin;		// Origin of text
		SDL_Color _color;		// Color of the text

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
