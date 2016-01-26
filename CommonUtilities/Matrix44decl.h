#pragma once

#include "Vector3decl.h"
#include "Vector4decl.h"

namespace CommonUtilities
{
	template <typename T>
	class Matrix33;

	template <typename T>
	class Matrix44
	{
	public:
		Matrix44();
		Matrix44(const Matrix44 &aMatrix);
		Matrix44(const Matrix33<T> &aMatrix);

		const Matrix44& operator=(const Matrix44 &aSecondMatrix);
		const Matrix44& operator=(const Matrix33<T> &aSecondMatrix);

		static Matrix44 CreateRotateAroundX(T aAngleInRadians);
		static Matrix44 CreateRotateAroundY(T aAngleInRadians);
		static Matrix44 CreateRotateAroundZ(T aAngleInRadians);

		void Rotate3DX(T aRadian);
		void Rotate3DY(T aRadian);
		void Rotate3DZ(T aRadian);

		void SetRotation3DX(T aRadian);
		void SetRotation3DY(T aRadian);
		void SetRotation3DZ(T aRadian);

		const Vector::Vector3<T> GetPosition() const;
		void SetPosition(T aX, T aY, T aZ);
		void SetPosition(const Vector::Vector3<T> &aVector);

		const Vector::Vector4<T> GetTranslation() const;
		void SetTranslation(T aX, T aY, T aZ, T aW);
		void SetTranslation(const Vector::Vector4<T> &aVector);

		const Vector::Vector4<T> GetForward() const;
		void SetForward(T aX, T aY, T aZ, T aW);
		void SetForward(const Vector::Vector4<T> &aVector);

		const Vector::Vector4<T> GetRight() const;
		void SetRight(T aX, T aY, T aZ, T aW);
		void SetRight(const Vector::Vector4<T> &aVector);

		const Vector::Vector4<T> GetUp() const;
		void SetUp(T aX, T aY, T aZ, T aW);
		void SetUp(const Vector::Vector4<T> &aVector);

		Matrix44<T> CreateProjectionMatrixLH(T aNearZ, T aFarZ, T anAspectRatio, T aFovAngle);

		Matrix44<T> GetInverse() const;

		T myMatrix[16];
	};
}