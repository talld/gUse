#include "../Vector2f.h"

namespace GM
{
	Vector2f::Vector2f()
		: x(0), y(0)
	{}

	Vector2f::Vector2f(float x, float y)
		: x(x), y(y)
	{}

	Vector2f::Vector2f(const Vector2f &copyFrom)
		: x(copyFrom.x), y(copyFrom.y)
	{}

	Vector2f::~Vector2f()
	{}

	Vector2f Vector2f::add(const Vector2f &b) const
	{
		Vector2f ret = add(b.x, b.y);
		return ret;
	}

	Vector2f Vector2f::add(float bX, float bY) const
	{
		Vector2f ret = {x + bX, y + bY};
		return ret;
	}

	Vector2f Vector2f::sub(const Vector2f &b) const
	{
		Vector2f ret = sub(b.x, b.y);
		return ret;
	}

	Vector2f Vector2f::sub(float bX, float bY) const
	{
		Vector2f ret = {x - bX, y - bY};
		return ret;
	}

	Vector2f Vector2f::mul(float s) const
	{
		Vector2f ret = {x * s, y * s};
		return ret;
	}

	Vector2f Vector2f::div(float s) const
	{
		Vector2f ret = {x / s, y / s};
		return ret;
	}

	float Vector2f::dot(const Vector2f &b) const
	{
		float dot = this->dot(b.x, b.y);
		return dot;
	}

	float Vector2f::dot(float bX, float bY) const
	{
		float dot = (x * bX) + (y * bY);
		return dot;
	}

	float Vector2f::magnitude() const
	{
		float mag = std::sqrt((x * x) + (y * y));
		return mag;
	}

	Vector2f Vector2f::normalise() const
	{
		float mag = magnitude();
		Vector2f ret = {x / mag, y / mag};
		return ret;
	}

	Vector2f Vector2f::rotate(float angle) const
	{
		float rad = angle * DEG2RAD;
		float sin = std::sin(rad);
		float cos = std::cos(rad);
		Vector2f ret = {(x * cos) - (y * sin), (x * sin) + (y * cos)};
		return ret;
	}

	Vector2f& Vector2f::operator=(const Vector2f &copyFrom)
	{
		// this is UB but as this is a struct with no virtual functions it should be ok
		memcpy(this, &copyFrom, sizeof(Vector2f));
		return *this;
	}
}