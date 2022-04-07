#ifndef GMATH_VECTOR2F_H
#define GMATH_VECTOR2F_H

#include "Defines.h"
#include <cmath>
#include <utility>
#include <algorithm>
#include <cstring>

namespace GM
{
	struct Vector2f
	{
		Vector2f();

		Vector2f(float x, float y);

		Vector2f(const Vector2f& copyFrom);

		~Vector2f();

		Vector2f add(const Vector2f& b) const;

		Vector2f add(float bX, float bY) const;

		Vector2f sub(const Vector2f& b) const;

		Vector2f sub(float bX, float bY) const;

		Vector2f mul(float s) const;

		Vector2f div(float s) const;

		float dot(const Vector2f& b) const;

		float dot(float bX, float bY) const;

		float magnitude() const;

		Vector2f normalise() const;

		Vector2f rotate(float angle) const;

		Vector2f& operator=(const Vector2f& copyFrom);

		const float x;

		const float y;
	};
} // namespace GM
#endif  // GMATH_VECTOR2F_H
