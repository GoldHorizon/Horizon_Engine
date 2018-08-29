#pragma once

#include <string>
#include <list>
#include <vector>
#include <map>

#include "entity.h"

typedef std::list<Entity*> eList;
typedef std::vector<std::string> sVector;
typedef std::vector<Entity*> eVector;

typedef std::map<SDL_Point, Entity*> peMap;
typedef std::pair<SDL_Point, Entity*> pePair;

