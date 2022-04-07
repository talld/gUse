#ifndef GMATH_VECTOR3F_H
#define GMATH_VECTOR3F_H

#include "Vector2f.h"

#include <cmath>
#include <cstring>

namespace GM
{
	struct Vector3f
	{
		Vector3f();

		Vector3f(float x, float y, float z);

		Vector3f(const Vector3f& copyFrom);

		Vector3f(const Vector2f& toUpgrade);

		~Vector3f();

		Vector3f add(const Vector3f& b) const;

		Vector3f add(float bX, float bY, float bZ) const;

		Vector3f sub(const Vector3f& b) const;

		Vector3f sub(float bX, float bY, float bZ) const;

		Vector3f mul(float s) const;

		Vector3f div(float s) const;

		float dot(const Vector3f& b) const;

		float dot(float bX, float bY, float bZ) const;

		Vector3f cross(const Vector3f& b) const;

		Vector3f cross(float bX, float bY, float bZ);

		float magnitude() const;

		Vector3f normalise() const;

		Vector3f& operator=(const Vector3f& copyFrom);

		const float x;

		const float y;

		const float z;
	};
} // namespace GM

#endif  // GMATH_VECTOR3F_H