#pragma once

#include "types.h"
#include "entity.h"

#include <string>

sVector* ParseSerializedString(std::string str);
Entity* CreateSerializedObject(std::string str);

void AddOutput(std::string str);
void AddError(std::string str);

Vec2<int> WorldToScreen(const Vec2<int> &coords);
Vec2<int> WorldToScreen(int x, int y);
Vec2<int> ScreenToWorld(const Vec2<int> &coords);
Vec2<int> ScreenToWorld(int x, int y);

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
