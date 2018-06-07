#pragma once

#include <string>

#include "SDL"
#include "SDL_ttf.h"

class Font
{
    public:
        /*
         *  Constructors/Destructors
         */
        Font();
        Font(std::string);
        ~Font();

        /*
         *  Get Methods
         */
        int size() const;
        std::string name() const;

        /*
         *  Set Methods
         */
        void SetSize();
        void SetName();

    private:
        std::string _name;
        TTF_Font* _sdl_font;
}
