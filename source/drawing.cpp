#include "drawing.h"

#include "globals.h"
#include "text.h"
#include "enumerations.h"

#include <iostream>

Text* CreateText(std::string name, Font* font, SDL_Point pos, SDL_Color color, TextAlignment align)
{
	Text* text = new Text(name, font);
	text->SetPosition(pos);
	text->SetColor(color);
	text->SetAlign(align);
	text->UpdateImage();

	return text;
}

void DrawRect(SDL_Rect draw_rect, SDL_Color c) {
	SDL_SetRenderDrawColor(globalRenderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(globalRenderer, &draw_rect);
}

//void DrawRect(int x, int y, int w, int h, int r, int g, int b, int a) {
//	SDL_SetRenderDrawColor(globalRenderer, r, g, b, a);
//	SDL_Rect rect = {x, y, w, h};
//	SDL_RenderFillRect(globalRenderer, &rect);
//}

void DrawRect(int x, int y, int w, int h, SDL_Color c) {
	SDL_SetRenderDrawColor(globalRenderer, c.r, c.g, c.b, c.a);
	SDL_Rect rect = {x, y, w, h};
	SDL_RenderFillRect(globalRenderer, &rect);
}

void DrawLine(SDL_Point p1, SDL_Point p2, SDL_Color c)
{
	SDL_SetRenderDrawColor(globalRenderer, c.r, c.g, c.b, c.a);
	SDL_RenderDrawLine(globalRenderer, p1.x, p1.y, p2.x, p2.y);
}

void DrawLine(int x1, int y1, int x2, int y2, SDL_Color c)
{
	SDL_SetRenderDrawColor(globalRenderer, c.r, c.g, c.b, c.a);
	SDL_RenderDrawLine(globalRenderer, x1, y1, x2, y2);
}

void DrawText(std::string str, TextQuality quality, Font* font, int x, int y, TextAlignment align, SDL_Color c, SDL_Color bg)
{
	SDL_Surface* surface;
	switch (quality) {
		case TextQuality::SOLID: surface 	= TTF_RenderText_Solid(font->font(), str.c_str(), c); break;
		case TextQuality::BLENDED: surface 	= TTF_RenderText_Blended(font->font(), str.c_str(), c); break;
		case TextQuality::SHADED: surface 	= TTF_RenderText_Shaded(font->font(), str.c_str(), c, bg); break;
	}

	if (surface == nullptr) {
		std::cout << "Error: Drawing text, can't make surface: ";
		std::cout << TTF_GetError() << std::endl;
		return;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(globalRenderer, surface);
	if (texture == nullptr) {
		std::cout << "Error: Drawing text, can't make texture: ";
		std::cout << TTF_GetError() << std::endl;
		return;
	}
	
	if (c.a != 255)
		SDL_SetTextureAlphaMod(texture, c.a);

	//std::cout << "Surface dimensions: " << surface->w << ", " << surface->h << std::endl;
	//std::cout << "Texture dimensions: " << texture->w << ", " << texture->h << std::endl;

	SDL_Rect dest = {x, y, surface->w, surface->h};
	
	SDL_SetRenderDrawColor(globalRenderer, c.r, c.g, c.b, c.a);
	SDL_RenderCopy(globalRenderer, texture, nullptr, &dest);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
