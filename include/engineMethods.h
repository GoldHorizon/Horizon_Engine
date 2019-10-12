#pragma once

#include "types.h"
//#include "entity.h"

#include <string>

std::unique_ptr<std::vector<std::string>> ParseSerializedString(std::string str);
std::unique_ptr<Entity> CreateSerializedObject(std::string str);

void AddOutput(std::string str);
void AddError(std::string str);

vec2<int> WorldToScreen(const vec2<int> &coords);
vec2<int> WorldToScreen(int x, int y);
vec2<int> ScreenToWorld(const vec2<int> &coords);
vec2<int> ScreenToWorld(int x, int y);

bool ContainsPoint(const vec4<int> &rect, const vec2<int> &point);
bool ContainsPoint(const vec2<int> &rect_pos, const vec2<int> &rect_dim, const vec2<int> &point);

template <class T>
void Lerp(T& from, T to, T rate)
{
	if (from < to)
	{
		from += rate;
		if (from > to) from = to;
	}
	else if (from > to)
	{
		from -= rate;
		if (from < to) from = to;
	}
}

bool operator<(const SDL_Point &lhs, const SDL_Point &rhs);
