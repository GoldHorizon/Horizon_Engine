#include "globals.h"
#include "text.h"

Text* CreateText(std::string name, Font* font, SDL_Point pos, SDL_Color color, TextAlignment align = TextAlignment::ALIGN_LEFT)
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

void DrawRect(int x, int y, int w, int h, int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(globalRenderer, r, g, b, a);
	SDL_Rect rect = {x, y, w, h};
	SDL_RenderFillRect(globalRenderer, &rect);
}
