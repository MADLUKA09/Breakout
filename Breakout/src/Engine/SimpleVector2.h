#pragma once

#include <math.h>

template <typename T>
class SimpleVector2 {
public:
	SimpleVector2(T _x, T _y) : x(_x), y(_y) {}
	SimpleVector2() : x(T(0)), y(T(0)) {}

	T x;
	T y;

	T length() const { return sqrt(x * x  + y * y); }
	
	SimpleVector2 operator+(const SimpleVector2& other) const{
		return SimpleVector2(this->x + other.x, this->y + other.y);
	}

	SimpleVector2 operator-(const SimpleVector2& other) const {
		return SimpleVector2(this->x- other.x, this->y - other.y);
	}

	SimpleVector2 operator-() const {
		return SimpleVector2(-this->x, -this->y);
	}

	SimpleVector2 operator*(const T& factor) const {
		return SimpleVector2(this->x * factor, this->y * factor);
	}

	SimpleVector2 operator/(const T& factor) const {
		return SimpleVector2(this->x / factor, this->y / factor);
	}

	T dotProduct(const SimpleVector2& other) const {
		return this->x * other.x + this->y * other.y;
	}

	SimpleVector2 normalized() const {
		return *this / this->length();
	}

	SimpleVector2 projectTo(const SimpleVector2& other) {
		return other.normalized() * this->dotProduct(other.normalized());
	}
};