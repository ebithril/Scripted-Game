#pragma once

#include "Vector4decl.h"
#include <cmath>

namespace CommonUtilities
{
	namespace Vector
	{
		template <typename TYPE>
		Vector4<TYPE>::Vector4()
		{
		}

		template <typename TYPE>
		Vector4<TYPE>::Vector4(const TYPE aX, const TYPE aY, const TYPE aZ, const TYPE aW)
		{
			x = aX;
			y = aY;
			z = aZ;
			w = aW;
		}

		template <typename TYPE>
		const Vector4<TYPE> operator+(const Vector4<TYPE> &aVector4, const Vector4<TYPE> &aAnotherVector4)
		{
			Vector4<TYPE> tempVector;
			tempVector.x = aVector4.x + aAnotherVector4.x;
			tempVector.y = aVector4.y + aAnotherVector4.y;
			tempVector.z = aVector4.z + aAnotherVector4.z;
			tempVector.w = aVector4.w + aAnotherVector4.w;

			return tempVector;
		}

		template <typename TYPE>
		const Vector4<TYPE> operator-(const Vector4<TYPE> &aVector4, const Vector4<TYPE> &aAnotherVector4)
		{
			Vector4<TYPE> tempVector;
			tempVector.x = aVector4.x - aAnotherVector4.x;
			tempVector.y = aVector4.y - aAnotherVector4.y;
			tempVector.z = aVector4.z - aAnotherVector4.z;
			tempVector.w = aVector4.w - aAnotherVector4.w;

			return tempVector;
		}

		template <typename TYPE>
		const Vector4<TYPE> operator*(const Vector4<TYPE> &aVector4, const Vector4<TYPE> &aAnotherVector4)
		{
			Vector4<TYPE> tempVector;
			tempVector.x = aVector4.x * aAnotherVector4.x;
			tempVector.y = aVector4.y * aAnotherVector4.y;
			tempVector.z = aVector4.z * aAnotherVector4.z;
			tempVector.w = aVector4.w * aAnotherVector4.w;

			return tempVector;
		}

		template <typename TYPE>
		const Vector4<TYPE> operator/(const Vector4<TYPE> &aVector4, const Vector4<TYPE> &aAnotherVector4)
		{
			Vector4<TYPE> tempVector;
			tempVector.x = aVector4.x / aAnotherVector4.x;
			tempVector.y = aVector4.y / aAnotherVector4.y;
			tempVector.z = aVector4.z / aAnotherVector4.z;
			tempVector.w = aVector4.w / aAnotherVector4.w;

			return tempVector;
		}

		template <typename TYPE>
		void operator*=(Vector4<TYPE> &aVector4, const Vector4<TYPE> &aAnotherVector4)
		{
			aVector4.x *= aAnotherVector4.x;
			aVector4.y *= aAnotherVector4.y;
			aVector4.z *= aAnotherVector4.z;
			aVector4.w *= aAnotherVector4.w;
		}

		template <typename TYPE>
		void operator/=(Vector4<TYPE> &aVector4, const Vector4<TYPE> &aAnotherVector4)
		{
			aVector4.x /= aAnotherVector4.x;
			aVector4.y /= aAnotherVector4.y;
			aVector4.z /= aAnotherVector4.z;
			aVector4.w /= aAnotherVector4.w;
		}

		template <typename TYPE>
		void operator+=(Vector4<TYPE> &aVector4, const Vector4<TYPE> &aAnotherVector4)
		{
			aVector4.x += aAnotherVector4.x;
			aVector4.y += aAnotherVector4.y;
			aVector4.z += aAnotherVector4.z;
			aVector4.w += aAnotherVector4.w;
		}

		template <typename TYPE>
		void operator-=(Vector4<TYPE> &aVector4, const Vector4<TYPE> &aAnotherVector4)
		{
			aVector4.x -= aAnotherVector4.x;
			aVector4.y -= aAnotherVector4.y;
			aVector4.z -= aAnotherVector4.z;
			aVector4.w -= aAnotherVector4.w;
		}

		template <typename TYPE>
		const Vector4<TYPE> operator+(const Vector4<TYPE> &aVector4, const TYPE aScalar)
		{
			Vector4<TYPE> tempVector;
			tempVector.x = aVector4.x + aScalar;
			tempVector.y = aVector4.y + aScalar;
			tempVector.z = aVector4.z + aScalar;
			tempVector.w = aVector4.w + aScalar;

			return tempVector;
		}

		template <typename TYPE>
		const Vector4<TYPE> operator-(const Vector4<TYPE> &aVector4, const TYPE aScalar)
		{
			Vector4<TYPE> tempVector;
			tempVector.x = aVector4.x - aScalar;
			tempVector.y = aVector4.y - aScalar;
			tempVector.z = aVector4.z - aScalar;
			tempVector.w = aVector4.w - aScalar;

			return tempVector;
		}

		template <typename TYPE>
		const Vector4<TYPE> operator*(const Vector4<TYPE> &aVector4, const TYPE aScalar)
		{
			Vector4<TYPE> tempVector;
			tempVector.x = aVector4.x * aScalar;
			tempVector.y = aVector4.y * aScalar;
			tempVector.z = aVector4.z * aScalar;
			tempVector.w = aVector4.w * aScalar;

			return tempVector;
		}

		template <typename TYPE>
		const Vector4<TYPE> operator/(const Vector4<TYPE> &aVector4, const TYPE aScalar)
		{
			Vector4<TYPE> tempVector;
			tempVector.x = aVector4.x / aScalar;
			tempVector.y = aVector4.y / aScalar;
			tempVector.z = aVector4.z / aScalar;
			tempVector.w = aVector4.w / aScalar;

			return tempVector;
		}

		template <typename TYPE>
		void operator*=(Vector4<TYPE> &aVector4, const TYPE aScalar)
		{
			aVector4.x *= aScalar;
			aVector4.y *= aScalar;
			aVector4.z *= aScalar;
			aVector4.w *= aScalar;
		}

		template <typename TYPE>
		void operator/=(Vector4<TYPE> &aVector4, const TYPE aScalar)
		{
			aVector4.x /= aScalar;
			aVector4.y /= aScalar;
			aVector4.z /= aScalar;
			aVector4.w /= aScalar;
		}

		template <typename TYPE>
		void operator+=(Vector4<TYPE> &aVector4, const TYPE aScalar)
		{
			aVector4.x += aScalar;
			aVector4.y += aScalar;
			aVector4.z += aScalar;
			aVector4.w += aScalar;
		}

		template <typename TYPE>
		void operator-=(Vector4<TYPE> &aVector4, const TYPE aScalar)
		{
			aVector4.x -= aScalar;
			aVector4.y -= aScalar;
			aVector4.z -= aScalar;
			aVector4.w -= aScalar;
		}

		template <typename TYPE>
		TYPE Length(const Vector4<TYPE> &aVector4)
		{
			TYPE temp = aVector4.x * aVector4.x;
			temp += aVector4.y * aVector4.y;
			temp += aVector4.z * aVector4.z;
			temp += aVector4.w * aVector4.w;
			temp = sqrt(temp);

			return temp;
		}

		template <typename TYPE>
		TYPE Length2(const Vector4<TYPE> &aVector4)
		{
			return ((aVector4.x * aVector4.x) + (aVector4.y * aVector4.y) + (aVector4.z * aVector4.z) + (aVector4.w * aVector4));
		}

		template <typename TYPE>
		void Normalize(Vector4<TYPE> &aVector4)
		{
			aVector4 /= Length(aVector4);
		}

		template <typename TYPE>
		const Vector4<TYPE> GetNormalized(const Vector4<TYPE> &aVector4)
		{
			return aVector4 / Length(aVector4);
		}

		template <typename TYPE>
		const TYPE Dot(const Vector4<TYPE> &aVector4, const Vector4<TYPE> &aAnotherVector4)
		{
			return ((aVector4.x * aAnotherVector4.x) + (aVector4.y * aAnotherVector4.y) + (aVector4.z * aAnotherVector4.z) + (aVector4.w * aAnotherVector4.w));
		}
	}
}