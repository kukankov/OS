#pragma once

#include<cmath>
#include<iostream>


class Number
{
public:
	Number() = default;

	Number(double value) : value_(value) { }

	Number(const Number& c) { value_ = c.value_; }

	Number operator-(const Number& number) {
		return Number(value_ - number.value_);
	}

	Number operator+(const Number& number) {
		return Number(value_ + number.value_);
	}

	Number operator*(const Number& number) {
		return Number(value_ * number.value_);
	}

	Number operator/(const Number& number) {
		return Number(value_ / number.value_);
	}

	bool operator==(Number& number) {
		return value_ == number.value_;
	}

	bool operator!=(Number& number) {
		return !this->operator==(number);
	}

	bool operator>(Number& number) {
		return value_ > number.value_;
	}

	bool operator<(Number& number) {
		return value_ < number.value_;
	}


	Number Sqrt() { 
		return std::sqrt(value_);
	}

	Number Atan() {
		return std::atan(value_);
	}

	friend std::ostream& operator<<(std::ostream& out, Number& number) {
		out << number.value_;
		return out;
	}

	double GetValue() { return value_; }

private:
	double value_;

};

Number one(1);
Number zero(0);

Number CreateNumber(double value) {
	return { value };
}