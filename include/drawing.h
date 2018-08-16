#include "globals.h"

void DrawRect(SDL_Rect draw_rect, SDL_Color c) {
	SDL_SetRenderDrawColor(globalRenderer, c.r, c.g, c.b, c.a);
	SDL_RenderFillRect(globalRenderer, &draw_rect);
}

void DrawRect(int x, int y, int w, int h, int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(globalRenderer, r, g, b, a);
	SDL_Rect rect = {x, y, w, h};
	SDL_RenderFillRect(globalRenderer, &rect);
}
