#pragma once

#include "globals.h"
#include "text.h"

Text* CreateText(std::string name, Font* font, SDL_Point pos, SDL_Color color, TextAlignment align = TextAlignment::ALIGN_LEFT);

void DrawRect(SDL_Rect draw_rect, SDL_Color c);
//void DrawRect(int x, int y, int w, int h, int r, int g, int b, int a);
void DrawRect(int x, int y, int w, int h, SDL_Color c);

void DrawLine(SDL_Point p1, SDL_Point p2, SDL_Color c);
void DrawLine(int x1, int y1, int x2, int y2, SDL_Color c);
