#pragma once
#include <cmath>

template<typename T>
struct Vector2 {
	T x;
	T y;

	
	static Vector2 down;
	static Vector2 up;
	static Vector2 left;
	static Vector2 right;

	static Vector2 InvalidPos;
	

	Vector2(const T& x = 0, const T& y = 0) : x(x), y(y) {}

	template<typename U>
	Vector2(const Vector2<U>& other) : Vector2((const T&)other.x, (const T&)other.y) {}

	
	// copy constructor
	Vector2(const Vector2& other) : Vector2(other.x, other.y) {}

	void normalize() {
		float sqrt = (float)::sqrt(this->sqrMagnitude());
		this->x /= sqrt;
		this->y /= sqrt;
	}

	float sqrMagnitude() const {
		return this->x * this->x + this->y * this->y;
	}

	float magnitude() const {
		return ::sqrt(this->sqrMagnitude());
	}

	Vector2 operator+(const Vector2& other) const {
		return Vector2{ this->x + other.x, this->y + other.y };
	}

	Vector2 operator-(const Vector2& other) const {
		return Vector2{ this->x - other.x, this->y - other.y };
	}

	Vector2 operator/(float div) const {
		if (div == 0.0f) return *this;
		return Vector2{ static_cast<T>(this->x / div), static_cast<T>(this->y / div) };
	}

	Vector2 operator*(float mul) const {
		return Vector2{ static_cast<T>(this->x * mul), static_cast<T>(this->y * mul) };
	}

	bool operator>(const Vector2& other) const {
		return this->sqrMagnitude() > other.sqrMagnitude();
	}

	bool operator==(const Vector2 other) const {
		auto dist = (*this - other).magnitude();
		return dist < 0.01;
	}

	bool operator!=(const Vector2 other) const {
		return !(*this == other);
	}

};

typedef Vector2<float>	Position;
typedef Vector2<float>	Direction;
typedef Vector2<int>	ScreenPosition;
typedef Vector2<int>	Dimension;


