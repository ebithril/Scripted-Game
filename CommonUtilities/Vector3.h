#pragma once

#include "Vector3decl.h"
#include <cmath>

namespace CommonUtilities
{
	namespace Vector
	{
		template <typename TYPE>
		Vector3<TYPE>::Vector3()
		{
		}

		template <typename TYPE>
		Vector3<TYPE>::Vector3(const TYPE aX, const TYPE aY, const TYPE aZ)
		{
			x = aX;
			y = aY;
			z = aZ;
		}

		template <typename TYPE>
		const Vector3<TYPE> operator+(const Vector3<TYPE> &aVector3, const Vector3<TYPE> &aAnotherVector3)
		{
			Vector3<TYPE> tempVector;
			tempVector.x = aVector3.x + aAnotherVector3.x;
			tempVector.y = aVector3.y + aAnotherVector3.y;
			tempVector.z = aVector3.z + aAnotherVector3.z;

			return tempVector;
		}

		template <typename TYPE>
		const Vector3<TYPE> operator-(const Vector3<TYPE> &aVector3, const Vector3<TYPE> &aAnotherVector3)
		{
			Vector3<TYPE> tempVector;
			tempVector.x = aVector3.x - aAnotherVector3.x;
			tempVector.y = aVector3.y - aAnotherVector3.y;
			tempVector.z = aVector3.z - aAnotherVector3.z;

			return tempVector;
		}

		template <typename TYPE>
		const Vector3<TYPE> operator*(const Vector3<TYPE> &aVector3, const Vector3<TYPE> &aAnotherVector3)
		{
			Vector3<TYPE> tempVector;
			tempVector.x = aVector3.x * aAnotherVector3.x;
			tempVector.y = aVector3.y * aAnotherVector3.y;
			tempVector.z = aVector3.z * aAnotherVector3.z;

			return tempVector;
		}

		template <typename TYPE>
		const Vector3<TYPE> operator/(const Vector3<TYPE> &aVector3, const Vector3<TYPE> &aAnotherVector3)
		{
			Vector3<TYPE> tempVector;
			tempVector.x = aVector3.x / aAnotherVector3.x;
			tempVector.y = aVector3.y / aAnotherVector3.y;
			tempVector.z = aVector3.z / aAnotherVector3.z;

			return tempVector;
		}

		template <typename TYPE>
		void operator*=(Vector3<TYPE> &aVector3, const Vector3<TYPE> &aAnotherVector3)
		{
			aVector3.x *= aAnotherVector3.x;
			aVector3.y *= aAnotherVector3.y;
			aVector3.z *= aAnotherVector3.z;
		}

		template <typename TYPE>
		void operator/=(Vector3<TYPE> &aVector3, const Vector3<TYPE> &aAnotherVector3)
		{
			aVector3.x /= aAnotherVector3.x;
			aVector3.y /= aAnotherVector3.y;
			aVector3.z /= aAnotherVector3.z;
		}

		template <typename TYPE>
		void operator+=(Vector3<TYPE> &aVector3, const Vector3<TYPE> &aAnotherVector3)
		{
			aVector3.x += aAnotherVector3.x;
			aVector3.y += aAnotherVector3.y;
			aVector3.z += aAnotherVector3.z;
		}

		template <typename TYPE>
		void operator-=(Vector3<TYPE> &aVector3, const Vector3<TYPE> &aAnotherVector3)
		{
			aVector3.x -= aAnotherVector3.x;
			aVector3.y -= aAnotherVector3.y;
			aVector3.z -= aAnotherVector3.z;
		}

		template <typename TYPE>
		const Vector3<TYPE> operator+(const Vector3<TYPE> &aVector3, const TYPE aScalar)
		{
			Vector3<TYPE> tempVector;
			tempVector.x = aVector3.x + aScalar;
			tempVector.y = aVector3.y + aScalar;
			tempVector.z = aVector3.z + aScalar;

			return tempVector;
		}

		template <typename TYPE>
		const Vector3<TYPE> operator-(const Vector3<TYPE> &aVector3, const TYPE aScalar)
		{
			Vector3<TYPE> tempVector;
			tempVector.x = aVector3.x - aScalar;
			tempVector.y = aVector3.y - aScalar;
			tempVector.z = aVector3.z - aScalar;

			return tempVector;
		}

		template <typename TYPE>
		const Vector3<TYPE> operator*(const Vector3<TYPE> &aVector3, const TYPE aScalar)
		{
			Vector3<TYPE> tempVector;
			tempVector.x = aVector3.x * aScalar;
			tempVector.y = aVector3.y * aScalar;
			tempVector.z = aVector3.z * aScalar;

			return tempVector;
		}

		template <typename TYPE>
		const Vector3<TYPE> operator/(const Vector3<TYPE> &aVector3, const TYPE aScalar)
		{
			Vector3<TYPE> tempVector;
			tempVector.x = aVector3.x / aScalar;
			tempVector.y = aVector3.y / aScalar;
			tempVector.z = aVector3.z / aScalar;

			return tempVector;
		}

		template <typename TYPE>
		void operator*=(Vector3<TYPE> &aVector3, const TYPE aScalar)
		{
			aVector3.x *= aScalar;
			aVector3.y *= aScalar;
			aVector3.z *= aScalar;
		}

		template <typename TYPE>
		void operator/=(Vector3<TYPE> &aVector3, const TYPE aScalar)
		{
			aVector3.x /= aScalar;
			aVector3.y /= aScalar;
			aVector3.z /= aScalar;
		}

		template <typename TYPE>
		void operator+=(Vector3<TYPE> &aVector3, const TYPE aScalar)
		{
			aVector3.x += aScalar;
			aVector3.y += aScalar;
			aVector3.z += aScalar;
		}

		template <typename TYPE>
		void operator-=(Vector3<TYPE> &aVector3, const TYPE aScalar)
		{
			aVector3.x -= aScalar;
			aVector3.y -= aScalar;
			aVector3.z -= aScalar;
		}

		template <typename TYPE>
		TYPE Length(const Vector3<TYPE> &aVector3)
		{
			return sqrt((aVector3.x * aVector3.x) + (aVector3.y * aVector3.y) + (aVector3.z * aVector3.z));
		}

		template <typename TYPE>
		TYPE Length2(const Vector3<TYPE> &aVector3)
		{
			return ((aVector3.x * aVector3.x) + (aVector3.y * aVector3.y) + (aVector3.z * aVector3.z));
		}

		template <typename TYPE>
		void Normalize(Vector3<TYPE> &aVector3)
		{
			TYPE length = Length(aVector3);

			aVector3 /= length;
		}

		template <typename TYPE>
		const Vector3<TYPE> GetNormalized(const Vector3<TYPE> &aVector3)
		{
			Vector3<TYPE> tempVector(aVector3);

			return tempVector / Length(aVector3);
		}

		template <typename TYPE>
		const TYPE Dot(const Vector3<TYPE> &aVector3, const Vector3<TYPE> &aAnotherVector3)
		{
			TYPE returnValue;
			returnValue = aVector3.x * aAnotherVector3.x;
			returnValue += aVector3.y * aAnotherVector3.y;
			returnValue += aVector3.z * aAnotherVector3.z;

			return returnValue;
		}

		template <typename TYPE>
		const Vector3<TYPE> Cross(const Vector3<TYPE> &aVector3, const Vector3<TYPE> &aAnotherVector3)
		{
			Vector3<TYPE> tempVector;

			tempVector.x = aVector3.z * aAnotherVector3.y - aVector3.y * aAnotherVector3.z;
			tempVector.y = aVector3.z * aAnotherVector3.x - aVector3.x * aAnotherVector3.z;
			tempVector.z = aVector3.x * aAnotherVector3.y - aVector3.y * aAnotherVector3.x;

			return tempVector;
		}
	}
}