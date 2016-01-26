#pragma once

#include "Vector2decl.h"
#include <cmath>

namespace CommonUtilities
{
	namespace Vector
	{
		template <typename TYPE>
		Vector2<TYPE>::Vector2()
		{
		}

		template <typename TYPE>
		Vector2<TYPE>::Vector2(const TYPE aX, const TYPE aY)
		{
			x = aX;
			y = aY;
		}

		template <typename TYPE>
		const Vector2<TYPE> operator+(const Vector2<TYPE> &aVector2, const Vector2<TYPE> &aAnotherVector2)
		{
			Vector2<TYPE> tempVector;
			tempVector.x = aVector2.x + aAnotherVector2.x;
			tempVector.y = aVector2.y + aAnotherVector2.y;

			return tempVector;
		}

		template <typename TYPE>
		const Vector2<TYPE> operator-(const Vector2<TYPE> &aVector2, const Vector2<TYPE> &aAnotherVector2)
		{
			Vector2<TYPE> tempVector;
			tempVector.x = aVector2.x - aAnotherVector2.x;
			tempVector.y = aVector2.y - aAnotherVector2.y;

			return tempVector;
		}

		template <typename TYPE>
		const Vector2<TYPE> operator*(const Vector2<TYPE> &aVector2, const Vector2<TYPE> &aAnotherVector2)
		{
			Vector2<TYPE> tempVector;
			tempVector.x = aVector2.x * aAnotherVector2.x;
			tempVector.y = aVector2.y * aAnotherVector2.y;

			return tempVector;
		}

		template <typename TYPE>
		const Vector2<TYPE> operator/(const Vector2<TYPE> &aVector2, const Vector2<TYPE> &aAnotherVector2)
		{
			Vector2<TYPE> tempVector;
			tempVector.x = aVector2.x / aAnotherVector2.x;
			tempVector.y = aVector2.y / aAnotherVector2.y;

			return tempVector;
		}

		template <typename TYPE>
		void operator*=(Vector2<TYPE> &aVector2, const Vector2<TYPE> &aAnotherVector2)
		{
			aVector2.x *= aAnotherVector2.x;
			aVector2.y *= aAnotherVector2.y;
		}

		template <typename TYPE>
		void operator/=(Vector2<TYPE> &aVector2, const Vector2<TYPE> &aAnotherVector2)
		{
			aVector2.x /= aAnotherVector2.x;
			aVector2.y /= aAnotherVector2.y;
		}

		template <typename TYPE>
		void operator+=(Vector2<TYPE> &aVector2, const Vector2<TYPE> &aAnotherVector2)
		{
			aVector2.x += aAnotherVector2.x;
			aVector2.y += aAnotherVector2.y;
		}

		template <typename TYPE>
		void operator-=(Vector2<TYPE> &aVector2, const Vector2<TYPE> &aAnotherVector2)
		{
			aVector2.x -= aAnotherVector2.x;
			aVector2.y -= aAnotherVector2.y;
		}

		template <typename TYPE>
		const Vector2<TYPE> operator+(const Vector2<TYPE> &aVector2, const TYPE aScalar)
		{
			Vector2<TYPE> tempVector;
			tempVector.x = aVector2.x + aScalar;
			tempVector.y = aVector2.y + aScalar;

			return tempVector;
		}

		template <typename TYPE>
		const Vector2<TYPE> operator-(const Vector2<TYPE> &aVector2, const TYPE aScalar)
		{
			Vector2<TYPE> tempVector;
			tempVector.x = aVector2.x - aScalar;
			tempVector.y = aVector2.y - aScalar;

			return tempVector;
		}

		template <typename TYPE>
		const Vector2<TYPE> operator*(const Vector2<TYPE> &aVector2, const TYPE aScalar)
		{
			Vector2<TYPE> tempVector;
			tempVector.x = aVector2.x * aScalar;
			tempVector.y = aVector2.y * aScalar;

			return tempVector;
		}

		template <typename TYPE>
		const Vector2<TYPE> operator/(const Vector2<TYPE> &aVector2, const TYPE aScalar)
		{
			Vector2<TYPE> tempVector;
			tempVector.x = aVector2.x / aScalar;
			tempVector.y = aVector2.y / aScalar;

			return tempVector;
		}

		template <typename TYPE>
		void operator*=(Vector2<TYPE> &aVector2, const TYPE aScalar)
		{
			aVector2.x *= aScalar;
			aVector2.y *= aScalar;
		}

		template <typename TYPE>
		void operator/=(Vector2<TYPE> &aVector2, const TYPE aScalar)
		{
			aVector2.x /= aScalar;
			aVector2.y /= aScalar;
		}

		template <typename TYPE>
		void operator+=(Vector2<TYPE> &aVector2, const TYPE aScalar)
		{
			aVector2.x += aScalar;
			aVector2.y += aScalar;
		}

		template <typename TYPE>
		void operator-=(Vector2<TYPE> &aVector2, const TYPE aScalar)
		{
			aVector2.x -= aScalar;
			aVector2.y -= aScalar;
		}

		template <typename TYPE>
		TYPE Length(const Vector2<TYPE> &aVector2)
		{
			return sqrt(aVector2.x * aVector2.x + aVector2.y * aVector2.y);
		}

		template <typename TYPE>
		TYPE Length2(const Vector2<TYPE> &aVector2)
		{
			return ((aVector2.x * aVector2.x) + (aVector2.y * aVector2.y));
		}

		template <typename TYPE>
		void Normalize(Vector2<TYPE> &aVector2)
		{
			TYPE length = Length(aVector2);

			aVector2 /= length;
		}

		template <typename TYPE>
		const Vector2<TYPE> GetNormalized(const Vector2<TYPE> &aVector2)
		{
			Vector2<TYPE> tempVector(aVector2);

			return tempVector / Length(aVector2);
		}

		template <typename TYPE>
		const TYPE Dot(const Vector2<TYPE> &aVector2, const Vector2<TYPE> &aAnotherVector2)
		{
			return ((aVector2.x * aAnotherVector2.x) + (aVector2.y * aAnotherVector2.y));
		}
	}
}