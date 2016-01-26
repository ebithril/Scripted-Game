#pragma once

#include "Vector2decl.h"
#include "Vector3decl.h"


namespace CommonUtilities
{
	template <typename T>
	class Matrix44;

	template <typename T>
	class Matrix33
	{
	public:
		Matrix33();
		Matrix33(const Matrix33 &aMatrix);
		Matrix33(const Matrix44<T> &aMatrix);

		const Matrix33& operator=(const Matrix33 &aSecondMatrix);

		void Rotate2D(T aRadian);
		void SetRotation2D(T aRadian);

		const CommonUtilities::Vector::Vector2<T> GetPosition() const;
		void SetPosition(T aX, T aY);
		void SetPosition(const CommonUtilities::Vector::Vector2<T> &aVector);

		const CommonUtilities::Vector::Vector3<T> GetTranslation() const;
		void SetTranslation(T aX, T aY, T aZ);
		void SetTranslation(const CommonUtilities::Vector::Vector3<T> &aVector);

		static Matrix33 CreateRotateAroundX(T aAngleInRadians);
		static Matrix33 CreateRotateAroundY(T aAngleInRadians);
		static Matrix33 CreateRotateAroundZ(T aAngleInRadians);

		T myMatrix[9];
	};
}