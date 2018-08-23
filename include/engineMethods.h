#pragma once

#include "types.h"
#include "entity.h"

#include <string>

sVector* ParseSerializedString(std::string str);
Entity* CreateSerializedObject(std::string str);
