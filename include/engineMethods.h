#pragma once

#include "types.h"
#include "entity.h"

#include <string>

sVector* ParseSerializedString(std::string str);
Entity* CreateSerializedObject(std::string str);

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
