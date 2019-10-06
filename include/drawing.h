#pragma once

#include <memory>

#include "globals.h"
#include "text.h"
#include "types.h"

std::unique_ptr<Text> CreateText(std::string name, Font* font, SDL_Point pos, SDL_Color color, TextAlignment align = TextAlignment::ALIGN_LEFT);

void DrawRect(SDL_Rect draw_rect, SDL_Color c, bool fill = true);
//void DrawRect(int x, int y, int w, int h, int r, int g, int b, int a);
void DrawRect(int x, int y, int w, int h, SDL_Color c, bool fill = true);
void DrawRect(int x, int y, int w, int h, vec4<float> c, bool fill = true);

void DrawLine(SDL_Point p1, SDL_Point p2, SDL_Color c);
void DrawLine(int x1, int y1, int x2, int y2, SDL_Color c);

void DrawText(std::string str, TextQuality quality, Font* font, int x, int y, TextAlignment align, SDL_Color c, SDL_Color bg = {0, 0, 0, 255});

void DrawFastText(std::string str, Font* font, int x, int y, TextAlignment align, vec4<float> c, vec4<float> bg = {0, 0, 0, 0});
void DrawSmoothText(std::string str, Font* font, int x, int y, TextAlignment align, vec4<float> c, vec4<float> bg = {0, 0, 0, 0});
void DrawShadedText(std::string str, Font* font, int x, int y, TextAlignment align, vec4<float> c, vec4<float> bg = {0, 0, 0, 255});
