#pragma once

#include<iostream>
#include <cmath>

class vec2 {

public:
	vec2(double x, double y);
	vec2();

	double x, y;

	static vec2 up() {
		return vec2(0, -1);
	}
	static vec2 right() {
		return vec2(1, 0);
	}
	static vec2 down() {
		return vec2(0, 1);
	}
	static vec2 left() {
		return vec2(-1, 0);
	}

	vec2 MakeUnitVector() const;

	vec2 operator*(double multiplier);

};

inline vec2 operator+(const vec2& a, const vec2& b) {
	return vec2(a.x + b.x, a.y + b.y);
}

inline vec2 operator-(const vec2& a, const vec2& b) {
	return vec2(a.x - b.x, a.y - b.y);
}

inline vec2 operator*(const vec2& a, const vec2& b) {
	return vec2(a.x * b.x, a.y * b.y);
}

inline bool operator ==(const vec2& a, const vec2& b) {
	if (a.x == b.x && a.y == b.y)
		return true;
	return false;
}

inline bool operator !=(const vec2& a, const vec2& b) {
	return !(a == b);
}

inline std::ostream& operator <<(std::ostream& output, const vec2& a) {
	output << a.x << ", " << a.y;
	return output;
}

inline vec2 direction(const vec2& start, const vec2& end) {
	vec2 result = end - start;
	return result.MakeUnitVector();
}

inline double magnitude(const vec2& a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

inline double dot2D(const vec2& v1, const vec2& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

inline double cross2D(const vec2& v1, const vec2& v2) {
	return v1.x * v2.y - v1.y * v2.x;
}

double ClockwiseAngle(const vec2& v1, const vec2& v2);

using Coordinate = vec2;