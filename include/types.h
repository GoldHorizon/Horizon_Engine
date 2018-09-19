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

template <class T>
struct Vec2 {
	T x;
	T y;

	Vec2(T a, T b) : x(a), y(b) {};
};

template <class T>
struct Vec3 {
	T x;
	T y;
	T z;

	Vec3(T a, T b, T c) : x(a), y(b), z(c) {};
};
