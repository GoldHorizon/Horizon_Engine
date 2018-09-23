#pragma once

#include <string>
#include <list>
#include <vector>
#include <map>
#include <iostream>
#include <math.h>

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

	/*
	 * Methods
	 */
	Vec2() : Vec2(0, 0) {};
	Vec2(T a, T b) : x(a), y(b) {};
	float distanceTo(const Vec2<T> &R) {
		float x1 = x;
		float y1 = y;
		float x2 = R.x;
		float y2 = R.y;

		return std::sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	}

	/*
	 * Operators
	 */
	void operator+= (const Vec2<T> &R) {
		x += R.x;
		y += R.y;
	}
	void operator-= (const Vec2<T> &R) {
		x -= R.x;
		y -= R.y;
	}
	Vec2<T> operator+ (const Vec2<T> &R) const {
		Vec2<T> result;
		result.x = this->x + R.x;
		result.y = this->y + R.y;
		return result;
	}
	Vec2<T> operator- (const Vec2<T> &R) const {
		Vec2<T> result;
		result.x = this->x - R.x;
		result.y = this->y - R.y;
		return result;
	}
	void operator= (const Vec2<T> &R) {
		x = R.x;
		y = R.y;
	}
	bool operator== (const Vec2<T> &R) {
		return ((x == R.x) && (y == R.y));
	}
	friend std::ostream &operator<< (std::ostream &output, const Vec2<T> &R) {
		output << "(" << R.x << ", " << R.y << ")";
		return output;
	}
};

template <class T>
struct Vec3 {
	T x;
	T y;
	T z;

	/*
	 * Methods
	 */
	Vec3() : Vec3(0, 0, 0) {};
	Vec3(T a, T b, T c) : x(a), y(b), z(c) {};

	/*
	 * Operators
	 */
	void operator+= (const Vec3<T> &R) {
		x += R.x;
		y += R.y;
		z += R.z;
	}
	void operator-= (const Vec3<T> &R) {
		x -= R.x;
		y -= R.y;
		z -= R.z;
	}
	Vec3<T> operator+ (const Vec3<T> &R) const {
		Vec3<T> result;
		result.x = this->x + R.x;
		result.y = this->y + R.y;
		result.z = this->z + R.z;
		return result;
	}
	Vec3<T> operator- (const Vec3<T> &R) const {
		Vec3<T> result;
		result.x = this->x - R.x;
		result.y = this->y - R.y;
		result.z = this->z - R.z;
		return result;
	}
	void operator= (const Vec3<T> &R) {
		x = R.x;
		y = R.y;
		z = R.z;
	}
	bool operator== (const Vec3<T> &R) {
		return ((x == R.x) && (y == R.y) && (z == R.z));
	}
	friend std::ostream &operator<< (std::ostream &output, const Vec3<T> &R) {
		output << "(" << R.x << ", " << R.y << ", " << R.z << ")";
		return output;
	}
};
