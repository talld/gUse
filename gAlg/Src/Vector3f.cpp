#include "../Inc/Vector3f.h"

namespace GM
{
	Vector3f::Vector3f()
		: x(0), y(0), z(0)
	{}

	Vector3f::Vector3f(float x, float y, float z)
		: x(x), y(y), z(z)
	{}

	Vector3f::Vector3f(const Vector3f &copyFrom)
		: x(copyFrom.x), y(copyFrom.y), z(copyFrom.z)
	{}

	Vector3f::Vector3f(const Vector2f &toUpgrade)
		: x(toUpgrade.x), y(toUpgrade.y), z(0)
	{}

	Vector3f::~Vector3f()
	{}

	Vector3f Vector3f::add(const Vector3f &b) const
	{
		Vector3f ret = add(b.x, b.y, b.z);
		return ret;
	}

	Vector3f Vector3f::add(float bX, float bY, float bZ) const
	{
		Vector3f ret = {x + bX, y + bY, z + bZ};
		return ret;
	}

	Vector3f Vector3f::sub(const Vector3f &b) const
	{
		Vector3f ret = sub(b.x, b.y, b.z);
		return ret;
	}

	Vector3f Vector3f::sub(float bX, float bY, float bZ) const
	{
		Vector3f ret = {x - bX, y - bY, z - bZ};
		return ret;
	}

	Vector3f Vector3f::mul(float s) const
	{
		Vector3f ret = {x * s, y * s, z * s};
		return ret;
	}

	Vector3f Vector3f::div(float s) const
	{
		Vector3f ret = {x / s, y / s, z / s};
		return ret;
	}

	float Vector3f::dot(const Vector3f &b) const
	{
		float dot = this->dot(b.x, b.y, b.z);
		return dot;
	}

	float Vector3f::dot(float bX, float bY, float bZ) const
	{
		float dot = (x * bX) + (y * bY) + z * bZ;
		return dot;
	}

	Vector3f Vector3f::cross(const Vector3f &b) const
	{
		return Vector3f();
	}

	Vector3f Vector3f::cross(float bX, float bY, float bZ)
	{
		return Vector3f();
	}

	float Vector3f::magnitude() const
	{
		float mag = std::sqrt((x * x) + (y * y) + (z * z));
		return mag;
	}

	Vector3f Vector3f::normalise() const
	{
		float mag = magnitude();
		Vector3f ret = {x / mag, y / mag, z / mag};
		return ret;
	}

	Vector3f& Vector3f::operator=(const Vector3f &copyFrom)
	{
		// this is UB but as this is a struct with no virtual functions it should be ok
		memcpy(this, &copyFrom, sizeof(Vector3f));
		return *this;
	}

}