#include "vec2.h"

vec2::vec2(double x, double y) {
	this->x = x;
	this->y = y;
}

vec2::vec2() {
	x = 0; y = 0;
}

vec2 vec2::MakeUnitVector() const {
	double magnitude = sqrt(x * x + y * y);
	return vec2(x / magnitude, y / magnitude);
}

vec2 vec2::operator*(double multiplier) {
	return vec2(this->x * multiplier, this->y * multiplier);
}

double ClockwiseAngle(const vec2& v1, const vec2& v2) {
	vec2 a = v1.MakeUnitVector();
	vec2 b = v2.MakeUnitVector();

	double dotProduct = dot2D(a, b);
	double crossProduct = cross2D(a, b);

	double angleRadian = std::atan2(crossProduct, dotProduct);
	double angleDegrees = angleRadian * (180.0 / 3.14);

	if (angleDegrees < 0.0) {
		angleDegrees += 360.0;
	}

	return angleDegrees;
}