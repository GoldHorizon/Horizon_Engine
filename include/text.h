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
		//void Render(float interpolation);

		// Update()
		void Update() = 0;

		// UpdateImage()	- Update the text image based on text/font/wrap
		void UpdateImage();

		/*
		 * Get Methods
		 */
        Font* font() const;         // Returns the font used
		std::string text() const;       // Returns the text displayed
		SDL_Color color() const;		// Returns the color of the text
		int maxWidth() const;
		bool wrap() const;

		/*
		 * Set Methods
		 */
        void SetFont(Font* font);       // Sets the font being used
		void SetText(std::string text);		// Sets the text being displayed
		void SetColor(SDL_Color color);		// Sets the text color
		void SetMaxWidth(int maxWidth);
		void SetWrap(bool wrap);

	private:

        // _font                - Font associated with the text
        Font* _font;

		// _text				- Image stored in the drawable
		std::string _text;

		SDL_Color _color;		// Color of the text
		int _maxWidth;			// Max width of the text before it stops/wraps
		bool _wrap;

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
