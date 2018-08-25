#pragma once

#include "types.h"
#include "entity.h"

#include <string>

sVector* ParseSerializedString(std::string str);
Entity* CreateSerializedObject(std::string str);

bool operator<(const SDL_Point &lhs, const SDL_Point &rhs);
