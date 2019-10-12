#pragma once

#include <string>
#include <list>
#include <vector>
#include <map>
#include <iostream>
#include <math.h>

//#include "entity.h"
#include "SDL.h"

class Entity;

typedef std::list<Entity*> eList;
typedef std::vector<Entity*> eVector;

typedef std::map<SDL_Point, Entity*> peMap;
typedef std::pair<SDL_Point, Entity*> pePair;

template <class T>
struct vec2 {
	T x;
	T y;

	/*
	 * Methods
	 */
	vec2() : vec2(0, 0) {};
	vec2(T a, T b) : x(a), y(b) {};
	float distanceTo(const vec2<T> &R) {
		float x1 = x;
		float y1 = y;
		float x2 = R.x;
		float y2 = R.y;

		return std::sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	}

	/*
	 * Operators
	 */
	void operator+= (const vec2<T> &R) {
		x += R.x;
		y += R.y;
	}
	void operator-= (const vec2<T> &R) {
		x -= R.x;
		y -= R.y;
	}
	vec2<T> operator+ (const vec2<T> &R) const {
		vec2<T> result;
		result.x = this->x + R.x;
		result.y = this->y + R.y;
		return result;
	}
	vec2<T> operator- (const vec2<T> &R) const {
		vec2<T> result;
		result.x = this->x - R.x;
		result.y = this->y - R.y;
		return result;
	}
	void operator= (const vec2<T> &R) {
		x = R.x;
		y = R.y;
	}
	bool operator== (const vec2<T> &R) {
		return ((x == R.x) && (y == R.y));
	}
	friend std::ostream &operator<< (std::ostream &output, const vec2<T> &R) {
		output << "(" << R.x << ", " << R.y << ")";
		return output;
	}
};

template <typename T>
struct vec3 : public vec2<T> {
	T z;

	/*
	 * Methods
	 */
	vec3() : vec3(0, 0, 0) {};
	vec3(T a, T b, T c) : vec2<T>::vec2(a, b), z(c) {};

	/*
	 * Operators
	 */
	void operator+= (const vec3<T> &R) {
		this->x += R.x;
		this->y += R.y;
		this->z += R.z;
	}
	void operator-= (const vec3<T> &R) {
		this->x -= R.x;
		this->y -= R.y;
		this->z -= R.z;
	}
	vec3<T> operator+ (const vec3<T> &R) const {
		vec3<T> result;
		result.x = this->x + R.x;
		result.y = this->y + R.y;
		result.z = this->z + R.z;
		return result;
	}
	vec3<T> operator- (const vec3<T> &R) const {
		vec3<T> result;
		result.x = this->x - R.x;
		result.y = this->y - R.y;
		result.z = this->z - R.z;
		return result;
	}
	void operator= (const vec3<T> &R) {
		this->x = R.x;
		this->y = R.y;
		this->z = R.z;
	}
	bool operator== (const vec3<T> &R) {
		return ((this->x == R.x) && (this->y == R.y) && (this->z == R.z));
	}
	friend std::ostream &operator<< (std::ostream &output, const vec3<T> &R) {
		output << "(" << R.x << ", " << R.y << ", " << R.z << ")";
		return output;
	}
};

template <typename T>
struct vec4 : public vec3<T> {
	T w;

	/*
	 * Methods
	 */
	vec4() : vec4(0, 0, 0, 0) {};
	vec4(T a, T b, T c, T d) : vec3<T>::vec3(a, b, c), w(d) {};

	/*
	 * Operators
	 */
	void operator+= (const vec4<T> &R) {
		this->x += R.x;
		this->y += R.y;
		this->z += R.z;
		this->w += R.w;
	}
	void operator-= (const vec4<T> &R) {
		this->x -= R.x;
		this->y -= R.y;
		this->z -= R.z;
		this->w -= R.w;
	}
	vec4<T> operator+ (const vec4<T> &R) const {
		vec4<T> result;
		result.x = this->x + R.x;
		result.y = this->y + R.y;
		result.z = this->z + R.z;
		result.w = this->w + R.w;
		return result;
	}
	vec4<T> operator- (const vec4<T> &R) const {
		vec4<T> result;
		result.x = this->x - R.x;
		result.y = this->y - R.y;
		result.z = this->z - R.z;
		result.w = this->w - R.w;
		return result;
	}
	void operator= (const vec4<T> &R) {
		this->x = R.x;
		this->y = R.y;
		this->z = R.z;
		this->w = R.w;
	}
	bool operator== (const vec4<T> &R) {
		return ((this->x == R.x) && (this->y == R.y) && (this->z == R.z) && (this->w == R.w));
	}
	friend std::ostream &operator<< (std::ostream &output, const vec4<T> &R) {
		output << "(" << R.x << ", " << R.y << ", " << R.z << ", " << R.w << ")";
		return output;
	}
};
