#pragma once

#include <string>

#include "entity.h"
#include "font.h"
#include "enumerations.h"

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
		//void Update() = 0;

		// UpdateImage()	- Update the text image based on text/font/wrap
		void UpdateImage();

		/*
		 * Set Methods
		 */
        void SetFont(Font* font);       	// Sets the font being used
		void SetText(std::string text);		// Sets the text being displayed

		/*
		 * Get Methods
		 */
        Font* font() const;         // Returns the font used
		std::string text() const;       // Returns the text displayed

		/*
		 * Serialization
		 */
		std::string Serialize();
		void Unserialize(std::string str);

		/*
		 * Public Attributes
		 */
		SDL_Color color;		// Color of the text
		int maxWidth;			// Max width of the text before it stops/wraps
		bool wrap;				// If the text wraps
		TextAlignment align;	// Alignment of the text

	private:

		/*
		 * Private Attributes
		 */
        Font* _font; 			// Font associated with the text
		std::string _text;		// Image stored in the drawable

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
