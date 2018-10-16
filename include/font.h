#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

#include <string>
#include <sstream>

class Font
{
    public:
        /*
         *  Constructors/Destructors
         */
        Font(std::string name);
		Font(std::string name, int size);
		Font(std::string name, std::string file, int size);
        ~Font();

		/*
		 *	Class Methods
		 */
		void LoadFont(std::string file);
		void LoadFont(std::string file, int size);
		bool FreeFont();

        /*
         *  Get Methods
         */
        int size() const;
		TTF_Font* font() const;

        /*
         *  Set Methods
         */
        void SetSize(int size);

		std::string Serialize();
		void Unserialize(std::string str);

        std::string name;

    private:
		std::string _file;
		int _size;
        TTF_Font* _sdl_font;
};
