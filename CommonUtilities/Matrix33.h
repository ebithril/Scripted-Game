#pragma once

#include "Matrix33decl.h"
#include "Matrix44decl.h"
#include "Vector3.h"
#include "Vector2.h"
#include <cmath>

namespace CommonUtilities
{
	template<class TYPE>
	Matrix33<TYPE> CreateReflectionMatrixAboutAxis(Vector::Vector3<TYPE> reflectionVector)
	{
		Matrix33<TYPE> reflectionMatrix;
		reflectionMatrix.myMatrix[0] = 1 - 2 * (reflectionVector.x*reflectionVector.x);
		reflectionMatrix.myMatrix[1] = -2 * (reflectionVector.x*reflectionVector.y);
		reflectionMatrix.myMatrix[2] = -2 * (reflectionVector.x*reflectionVector.z);

		reflectionMatrix.myMatrix[3] = -2 * (reflectionVector.y*reflectionVector.x);
		reflectionMatrix.myMatrix[4] = 1 - 2 * (reflectionVector.y*reflectionVector.y);
		reflectionMatrix.myMatrix[5] = -2 * (reflectionVector.y*reflectionVector.z);

		reflectionMatrix.myMatrix[6] = -2 * (reflectionVector.z*reflectionVector.x);
		reflectionMatrix.myMatrix[7] = -2 * (reflectionVector.z*reflectionVector.y);
		reflectionMatrix.myMatrix[8] = 1 - 2 * (reflectionVector.z*reflectionVector.z);
		return reflectionMatrix;
	};

	template <typename T>
	const Matrix33<T> operator+(const Matrix33<T> &aMatrix, const Matrix33<T> &aSecondMatrix)
	{
		Matrix33<T> tempMatrix(aMatrix);

		tempMatrix += aSecondMatrix;

		return tempMatrix;
	}

	template <typename T>
	const Matrix33<T> operator+=(Matrix33<T> &aMatrix, const Matrix33<T> &aSecondMatrix)
	{
		aMatrix.myMatrix[0] += aSecondMatrix.myMatrix[0];
		aMatrix.myMatrix[1] += aSecondMatrix.myMatrix[1];
		aMatrix.myMatrix[2] += aSecondMatrix.myMatrix[2];
		aMatrix.myMatrix[3] += aSecondMatrix.myMatrix[3];
		aMatrix.myMatrix[4] += aSecondMatrix.myMatrix[4];
		aMatrix.myMatrix[5] += aSecondMatrix.myMatrix[5];
		aMatrix.myMatrix[6] += aSecondMatrix.myMatrix[6];
		aMatrix.myMatrix[7] += aSecondMatrix.myMatrix[7];
		aMatrix.myMatrix[8] += aSecondMatrix.myMatrix[8];

		return aMatrix;
	}

	template <typename T>
	const Matrix33<T> operator-(const Matrix33<T> &aMatrix, const Matrix33<T> &aSecondMatrix)
	{
		Matrix33<T> tempMatrix(aMatrix);

		tempMatrix -= aSecondMatrix;

		return tempMatrix;
	}

	template <typename T>
	const Matrix33<T> operator-=(Matrix33<T> &aMatrix, const Matrix33<T> &aSecondMatrix)
	{
		aMatrix.myMatrix[0] -= aSecondMatrix.myMatrix[0];
		aMatrix.myMatrix[1] -= aSecondMatrix.myMatrix[1];
		aMatrix.myMatrix[2] -= aSecondMatrix.myMatrix[2];
		aMatrix.myMatrix[3] -= aSecondMatrix.myMatrix[3];
		aMatrix.myMatrix[4] -= aSecondMatrix.myMatrix[4];
		aMatrix.myMatrix[5] -= aSecondMatrix.myMatrix[5];
		aMatrix.myMatrix[6] -= aSecondMatrix.myMatrix[6];
		aMatrix.myMatrix[7] -= aSecondMatrix.myMatrix[7];
		aMatrix.myMatrix[8] -= aSecondMatrix.myMatrix[8];

		return aMatrix;
	}

	template <typename T>
	const Matrix33<T> operator*(const Matrix33<T> &aMatrix, const Matrix33<T> &aSecondMatrix)
	{
		Matrix33<T> tempMatrix(aMatrix);

		tempMatrix *= aSecondMatrix;

		return tempMatrix;
	}

	template <typename T>
	const Matrix33<T> operator*=(Matrix33<T> &aMatrix, const Matrix33<T> &aSecondMatrix)
	{
		CommonUtilities::Vector::Vector3<T> row1(aMatrix.myMatrix[0], aMatrix.myMatrix[1], aMatrix.myMatrix[2]);
		CommonUtilities::Vector::Vector3<T> row2(aMatrix.myMatrix[3], aMatrix.myMatrix[4], aMatrix.myMatrix[5]);
		CommonUtilities::Vector::Vector3<T> row3(aMatrix.myMatrix[6], aMatrix.myMatrix[7], aMatrix.myMatrix[8]);

		CommonUtilities::Vector::Vector3<T> column1(aSecondMatrix.myMatrix[0], aSecondMatrix.myMatrix[3], aSecondMatrix.myMatrix[6]);
		CommonUtilities::Vector::Vector3<T> column2(aSecondMatrix.myMatrix[1], aSecondMatrix.myMatrix[4], aSecondMatrix.myMatrix[7]);
		CommonUtilities::Vector::Vector3<T> column3(aSecondMatrix.myMatrix[2], aSecondMatrix.myMatrix[5], aSecondMatrix.myMatrix[8]);

		aMatrix.myMatrix[0] = CommonUtilities::Vector::Dot(row1, column1);
		aMatrix.myMatrix[1] = CommonUtilities::Vector::Dot(row1, column2);
		aMatrix.myMatrix[2] = CommonUtilities::Vector::Dot(row1, column3);
		aMatrix.myMatrix[3] = CommonUtilities::Vector::Dot(row2, column1);
		aMatrix.myMatrix[4] = CommonUtilities::Vector::Dot(row2, column2);
		aMatrix.myMatrix[5] = CommonUtilities::Vector::Dot(row2, column3);
		aMatrix.myMatrix[6] = CommonUtilities::Vector::Dot(row3, column1);
		aMatrix.myMatrix[7] = CommonUtilities::Vector::Dot(row3, column2);
		aMatrix.myMatrix[8] = CommonUtilities::Vector::Dot(row3, column3);

		return aMatrix;
	}

	template <typename T>
	const CommonUtilities::Vector::Vector3<T> operator*(const CommonUtilities::Vector::Vector3<T> &aVector, const Matrix33<T> &aMatrix)
	{
		CommonUtilities::Vector::Vector3<T> vector(aVector);

		vector *= aMatrix;
		return vector;
	}

	template <typename T>
	const CommonUtilities::Vector::Vector3<T> operator*=(CommonUtilities::Vector::Vector3<T> &aVector, const Matrix33<T> &aMatrix)
	{
		CommonUtilities::Vector::Vector3<T> column1(aMatrix.myMatrix[0], aMatrix.myMatrix[3], aMatrix.myMatrix[6]);
		CommonUtilities::Vector::Vector3<T> column2(aMatrix.myMatrix[1], aMatrix.myMatrix[4], aMatrix.myMatrix[7]);
		CommonUtilities::Vector::Vector3<T> column3(aMatrix.myMatrix[2], aMatrix.myMatrix[5], aMatrix.myMatrix[8]);

		CommonUtilities::Vector::Vector3<T> returnValue;
		returnValue.x = CommonUtilities::Vector::Dot(aVector, column1);
		returnValue.y = CommonUtilities::Vector::Dot(aVector, column2);
		returnValue.z = CommonUtilities::Vector::Dot(aVector, column3);


		aVector = returnValue;
		return aVector;
	}

	template <typename T>
	const CommonUtilities::Vector::Vector2<T> operator*(const CommonUtilities::Vector::Vector2<T> &aVector, const Matrix33<T> &aMatrix)
	{
		CommonUtilities::Vector::Vector3<T> vector3(aVector.x, aVector.y, 1);

		vector3 *= aMatrix;

		CommonUtilities::Vector::Vector2<T> vector2(vector3.x, vector3.y);

		return vector2;
	}

	template <typename T>
	const bool operator==(const Matrix33<T> &aMatrix, const Matrix33<T> &aSecondMatrix)
	{
		if (aMatrix.myMatrix[0] == aSecondMatrix.myMatrix[0])
		{
			if (aMatrix.myMatrix[1] == aSecondMatrix.myMatrix[1])
			{
				if (aMatrix.myMatrix[2] == aSecondMatrix.myMatrix[2])
				{
					if (aMatrix.myMatrix[3] == aSecondMatrix.myMatrix[3])
					{
						if (aMatrix.myMatrix[4] == aSecondMatrix.myMatrix[4])
						{
							if (aMatrix.myMatrix[5] == aSecondMatrix.myMatrix[5])
							{
								if (aMatrix.myMatrix[6] == aSecondMatrix.myMatrix[6])
								{
									if (aMatrix.myMatrix[7] == aSecondMatrix.myMatrix[7])
									{
										if (aMatrix.myMatrix[8] == aSecondMatrix.myMatrix[8])
										{
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	template <typename T>
	const Matrix33<T>& Matrix33<T>::operator=(const Matrix33<T> &aSecondMatrix)
	{
		myMatrix[0] = aSecondMatrix.myMatrix[0];
		myMatrix[1] = aSecondMatrix.myMatrix[1];
		myMatrix[2] = aSecondMatrix.myMatrix[2];
		myMatrix[3] = aSecondMatrix.myMatrix[3];
		myMatrix[4] = aSecondMatrix.myMatrix[4];
		myMatrix[5] = aSecondMatrix.myMatrix[5];
		myMatrix[6] = aSecondMatrix.myMatrix[6];
		myMatrix[7] = aSecondMatrix.myMatrix[7];
		myMatrix[8] = aSecondMatrix.myMatrix[8];

		return *this;
	}

	template <typename T>
	Matrix33<T>::Matrix33()
	{
		myMatrix[0] = 1;
		myMatrix[1] = 0;
		myMatrix[2] = 0;
		myMatrix[3] = 0;
		myMatrix[4] = 1;
		myMatrix[5] = 0;
		myMatrix[6] = 0;
		myMatrix[7] = 0;
		myMatrix[8] = 1;
	}

	template <typename T>
	Matrix33<T>::Matrix33(const Matrix33 &aMatrix)
	{
		*this = aMatrix;
	}

	template <typename T>
	Matrix33<T>::Matrix33(const Matrix44<T> &aMatrix)
	{
		myMatrix[0] = aMatrix.myMatrix[0];
		myMatrix[1] = aMatrix.myMatrix[1];
		myMatrix[2] = aMatrix.myMatrix[2];
		myMatrix[3] = aMatrix.myMatrix[4];
		myMatrix[4] = aMatrix.myMatrix[5];
		myMatrix[5] = aMatrix.myMatrix[6];
		myMatrix[6] = aMatrix.myMatrix[8];
		myMatrix[7] = aMatrix.myMatrix[9];
		myMatrix[8] = aMatrix.myMatrix[10];
	}

	template <typename T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundX(T aAngleInRadians)
	{
		Matrix33<T> tempMatrix;

		tempMatrix.myMatrix[0] = 1;
		tempMatrix.myMatrix[1] = 0;
		tempMatrix.myMatrix[2] = 0;

		tempMatrix.myMatrix[3] = 0;
		tempMatrix.myMatrix[4] = cos(aAngleInRadians);
		tempMatrix.myMatrix[5] = sin(aAngleInRadians);

		tempMatrix.myMatrix[6] = 0;
		tempMatrix.myMatrix[7] = -sin(aAngleInRadians);
		tempMatrix.myMatrix[8] = cos(aAngleInRadians);

		return tempMatrix;
	}

	template <typename T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundY(T aAngleInRadians)
	{
		Matrix33<T> tempMatrix;

		tempMatrix.myMatrix[0] = cos(aAngleInRadians);
		tempMatrix.myMatrix[1] = 0;
		tempMatrix.myMatrix[2] = -sin(aAngleInRadians);
		tempMatrix.myMatrix[3] = 0;
		tempMatrix.myMatrix[4] = 1;
		tempMatrix.myMatrix[5] = 0;
		tempMatrix.myMatrix[6] = sin(aAngleInRadians);
		tempMatrix.myMatrix[7] = 0;
		tempMatrix.myMatrix[8] = cos(aAngleInRadians);

		return tempMatrix;
	}

	template <typename T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundZ(T aAngleInRadians)
	{
		Matrix33<T> tempMatrix;

		tempMatrix.myMatrix[0] = cos(aAngleInRadians);
		tempMatrix.myMatrix[1] = sin(aAngleInRadians);
		tempMatrix.myMatrix[2] = 0;
		tempMatrix.myMatrix[3] = -sin(aAngleInRadians);
		tempMatrix.myMatrix[4] = cos(aAngleInRadians);
		tempMatrix.myMatrix[5] = 0;
		tempMatrix.myMatrix[6] = 0;
		tempMatrix.myMatrix[7] = 0;
		tempMatrix.myMatrix[8] = 1;

		return tempMatrix;
	}

	template <typename T>
	Matrix33<T> MatrixTranspose(const Matrix33<T> &aMatrixToTranspose)
	{
		CommonUtilities::Vector::Vector3<T> column1(aMatrixToTranspose.myMatrix[0], aMatrixToTranspose.myMatrix[3], aMatrixToTranspose.myMatrix[6]);
		CommonUtilities::Vector::Vector3<T> column2(aMatrixToTranspose.myMatrix[1], aMatrixToTranspose.myMatrix[4], aMatrixToTranspose.myMatrix[7]);
		CommonUtilities::Vector::Vector3<T> column3(aMatrixToTranspose.myMatrix[2], aMatrixToTranspose.myMatrix[5], aMatrixToTranspose.myMatrix[8]);

		Matrix33<T> tempMatrix;

		tempMatrix.myMatrix[0] = column1.x;
		tempMatrix.myMatrix[1] = column1.y;
		tempMatrix.myMatrix[2] = column1.z;
		tempMatrix.myMatrix[3] = column2.x;
		tempMatrix.myMatrix[4] = column2.y;
		tempMatrix.myMatrix[5] = column2.z;
		tempMatrix.myMatrix[6] = column3.x;
		tempMatrix.myMatrix[7] = column3.y;
		tempMatrix.myMatrix[8] = column3.z;

		return tempMatrix;
	}

	template <typename T>
	void Matrix33<T>::Rotate2D(T aRadian)
	{
		Matrix33<T> tempMatrix(*this);

		tempMatrix *= CreateRotateAroundZ(aRadian);

		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[3] = tempMatrix.myMatrix[3];
		myMatrix[4] = tempMatrix.myMatrix[4];
	}

	template <typename T>
	void Matrix33<T>::SetRotation2D(T aRadian)
	{
		Matrix33<T> tempMatrix(CreateRotateAroundZ(aRadian));

		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[3] = tempMatrix.myMatrix[3];
		myMatrix[4] = tempMatrix.myMatrix[4];
	}

	template <typename T>
	const CommonUtilities::Vector::Vector2<T> Matrix33<T>::GetPosition() const
	{
		return CommonUtilities::Vector::Vector2<T>(myMatrix[6], myMatrix[7]);
	}

	template <typename T>
	void Matrix33<T>::SetPosition(T aX, T aY)
	{
		myMatrix[6] = aX;
		myMatrix[7] = aY;
	}

	template <typename T>
	void Matrix33<T>::SetPosition(const CommonUtilities::Vector::Vector2<T> &aVector)
	{
		myMatrix[6] = aVector.x;
		myMatrix[7] = aVector.y;
	}

	template <typename T>
	const CommonUtilities::Vector::Vector3<T> Matrix33<T>::GetTranslation() const
	{
		return CommonUtilities::Vector::Vector3<T>(myMatrix[6], myMatrix[7], myMatrix[8]);
	}

	template <typename T>
	void Matrix33<T>::SetTranslation(T aX, T aY, T aZ)
	{
		myMatrix[6] = aX;
		myMatrix[7] = aY;
		myMatrix[8] = aZ;
	}

	template <typename T>
	void Matrix33<T>::SetTranslation(const CommonUtilities::Vector::Vector3<T> &aVector)
	{
		myMatrix[6] = aVector.x;
		myMatrix[7] = aVector.y;
		myMatrix[8] = aVector.z;
	}
}