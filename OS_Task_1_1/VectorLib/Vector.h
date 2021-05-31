#pragma once

#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif

#include "Number.h"
#define M_PI 3.14159265358979323846


VECTOR_API class Vector
{
public:
	VECTOR_API Vector(Number x, Number y) : x_(x), y_(y) { }

	VECTOR_API Number Rho() {
		return Number(x_ * x_ + y_ * y_).Sqrt();
	}

	VECTOR_API Number Theta() {
		if (x_ == zero) {
			if (y_ > zero) {
				return CreateNumber(M_PI / 2);
			}
			else if (y_ < zero) {
				return CreateNumber(-M_PI / 2);
			}
			else {
				return CreateNumber(INT_MAX);
			}
		}
		else {
			Number num = y_ / x_;
			num = CreateNumber(atan(num.GetValue()));
			if (x_ > zero) {
				return num;
			}
			if (x_ < zero && !(y_ < zero)) {
				return num + CreateNumber(M_PI);
			}
			if (x_ < zero && y_ < zero) {
				return num - CreateNumber(M_PI);
			}
		}
		return zero;
	}

	VECTOR_API Vector operator+(Vector& v) {
		return Vector(x_ + v.x_, this->y_ + v.y_);
	}

	VECTOR_API friend std::ostream& operator<<(std::ostream& out, Vector& vector) {
		out << vector.x_ << ' ' << vector.y_;
		return out;
	}

private:
	Number x_;
	Number y_;
};

