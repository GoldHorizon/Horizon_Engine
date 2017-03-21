#include "../drawable.h"

Drawable::Drawable():
	_image(nullptr),
	_renderer(globalRenderer),
	_x(0),
	_y(0),
	_width(0),
	_height(0)
{
	if (globalRenderer == nullptr)
	{
		std::cerr << "Error: Cannot instantiate object - globalRenderer not set!" << std::endl;
	}
}

Drawable::Drawable(SDL_Renderer* renderer):
	_image(nullptr),
	_renderer(renderer),
	_x(0),
	_y(0),
	_width(0),
	_height(0)
{
	if (renderer == nullptr)
	{
		std::cerr << "Error: Cannot instantiate object - globalRenderer not set!" << std::endl;
	}
}

Drawable::~Drawable()
{
	FreeMemory();
}

void Drawable::LoadFromFile(const std::string file)
{
	// Create a temporary surface to load our image onto
	SDL_Surface* tempSurface;
	tempSurface = IMG_Load(file.c_str());

	if (tempSurface != nullptr)
	{
		// Set our attributes to match image properties
		_image = SDL_CreateTextureFromSurface(_renderer, tempSurface);
		_width = tempSurface->w;
		_height = tempSurface->h;

		// Free up our surface when we're done
		SDL_FreeSurface(tempSurface);
	}
	else
	{
		std::cout << "Error loading file: " + file << std::endl;
	}//	else
	//	{
	//		//std::cout << "Error: _image not found..." << std::endl;
	//	}
}

void Drawable::FreeMemory()
{
	if (_image != nullptr)
	{
		SDL_DestroyTexture(_image);
		_width = 0;
		_height = 0;
	}
}

void Drawable::Render(float x, float y, SDL_Rect* clipping)
{
	// Set our member variables to the new drawing position
	_x = x;
	_y = y;

	// Create a set of ints to use for drawing position
	int xx = static_cast<int>(x);
	int yy = static_cast<int>(y);

	if (_image != nullptr)
	{
		// Create a rectangle to put on display
		SDL_Rect displayImage = {xx, yy, _width, _height};

		// If we are clipping the sprite, adjust it
		if (clipping != nullptr)
		{
			displayImage.w = clipping->w;
			displayImage.h = clipping->h;
		}

		SDL_RenderCopy(_renderer, _image, clipping, &displayImage);
//		SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
//		SDL_RenderDrawRect(_renderer, &displayImage);
	}
//	else
//	{
//		//std::cout << "Error: _image not found..." << std::endl;
//	}
}

void Drawable::Render(float x, float y, double angle, SDL_Point* origin, SDL_RendererFlip flip, SDL_Rect* clipping)
{
	// Set our member variables to the new drawing position
	_x = x;
	_y = y;

	// Create a set of ints to use for drawing position
	int xx = static_cast<int>(x);
	int yy = static_cast<int>(y);

	if (_image != nullptr)
	{
		// Create a rectangle to put on display
		SDL_Rect displayImage = {xx, yy, _width, _height};
		//std::cout << clipping->x << " " << clipping->y << " " << clipping->w << " " << clipping->h << " " << std::endl;

		// If we are clipping the sprite, adjust it
		if (clipping != nullptr)
		{
			displayImage.w = clipping->w;
			displayImage.h = clipping->h;
		}

		SDL_RenderCopyEx(_renderer, _image, clipping, &displayImage, angle, origin, flip);
	}
//	else
//	{
//		//std::cout << "Error: _image not found..." << std::endl;
//	}
}

/*
 * Get Methods
 */
int Drawable::x() const
{
	return _x;
}

int Drawable::y() const
{
	return _y;
}

int Drawable::width() const
{
	return _width;
}

int Drawable::height() const
{
	return _height;
}

/*
 * Set Methods
 */

void Drawable::SetX(int x)
{
	_x = x;
}

void Drawable::SetY(int y)
{
	_y = y;
}

void Drawable::SetPos(SDL_Point pos)
{
	_x = pos.x;
	_y = pos.y;
}
