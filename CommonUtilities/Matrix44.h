#pragma once

#include "Matrix44decl.h"
#include "Matrix33decl.h"
#include "Vector3.h"
#include "Vector4.h"

namespace CommonUtilities
{
	template <typename T>
	const Matrix44<T> operator+(const Matrix44<T> &aMatrix, const Matrix44<T> &aSecondMatrix)
	{
		Matrix44<T> tempMatrix(aMatrix);

		tempMatrix += aSecondMatrix;

		return tempMatrix;
	}

	template <typename T>
	Matrix44<T>::Matrix44(const Matrix33<T>& aMatrix)
	{
		*this = aMatrix;
	}

	template <typename T>
	const Matrix44<T>& Matrix44<T>::operator=(const Matrix33<T> &aSecondMatrix)
	{
		myMatrix[0] = aSecondMatrix.myMatrix[0];
		myMatrix[1] = aSecondMatrix.myMatrix[1];
		myMatrix[2] = aSecondMatrix.myMatrix[2];
	
		myMatrix[4] = aSecondMatrix.myMatrix[3];
		myMatrix[5] = aSecondMatrix.myMatrix[4];
		myMatrix[6] = aSecondMatrix.myMatrix[5];
	
		myMatrix[8] = aSecondMatrix.myMatrix[6];
		myMatrix[9] = aSecondMatrix.myMatrix[7];
		myMatrix[10] = aSecondMatrix.myMatrix[8];

		return *this;
	}


	template <typename T>
	const Matrix44<T> operator+=(Matrix44<T> &aMatrix, const Matrix44<T> &aSecondMatrix)
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
		aMatrix.myMatrix[9] += aSecondMatrix.myMatrix[9];
		aMatrix.myMatrix[10] += aSecondMatrix.myMatrix[10];
		aMatrix.myMatrix[11] += aSecondMatrix.myMatrix[11];
		aMatrix.myMatrix[12] += aSecondMatrix.myMatrix[12];
		aMatrix.myMatrix[13] += aSecondMatrix.myMatrix[13];
		aMatrix.myMatrix[14] += aSecondMatrix.myMatrix[14];
		aMatrix.myMatrix[15] += aSecondMatrix.myMatrix[15];

		return aMatrix;
	}

	template <typename T>
	const Matrix44<T> operator-(const Matrix44<T> &aMatrix, const Matrix44<T> &aSecondMatrix)
	{
		Matrix44<T> tempMatrix(aMatrix);

		tempMatrix -= aSecondMatrix;

		return tempMatrix;
	}

	template <typename T>
	const Matrix44<T> operator-=(Matrix44<T> &aMatrix, const Matrix44<T> &aSecondMatrix)
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
		aMatrix.myMatrix[9] -= aSecondMatrix.myMatrix[9];
		aMatrix.myMatrix[10] -= aSecondMatrix.myMatrix[10];
		aMatrix.myMatrix[11] -= aSecondMatrix.myMatrix[11];
		aMatrix.myMatrix[12] -= aSecondMatrix.myMatrix[12];
		aMatrix.myMatrix[13] -= aSecondMatrix.myMatrix[13];
		aMatrix.myMatrix[14] -= aSecondMatrix.myMatrix[14];
		aMatrix.myMatrix[15] -= aSecondMatrix.myMatrix[15];

		return aMatrix;
	}

	template <typename T>
	const Matrix44<T> operator*(const Matrix44<T> &aMatrix, const Matrix44<T> &aSecondMatrix)
	{
		Matrix44<T> tempMatrix(aMatrix);

		tempMatrix *= aSecondMatrix;

		return tempMatrix;
	}

	template <typename T>
	const Matrix44<T> operator*=(Matrix44<T> &aMatrix, const Matrix44<T> &aSecondMatrix)
	{
		CommonUtilities::Vector::Vector4<T> row1(aMatrix.myMatrix[0], aMatrix.myMatrix[1], aMatrix.myMatrix[2], aMatrix.myMatrix[3]);
		CommonUtilities::Vector::Vector4<T> row2(aMatrix.myMatrix[4], aMatrix.myMatrix[5], aMatrix.myMatrix[6], aMatrix.myMatrix[7]);
		CommonUtilities::Vector::Vector4<T> row3(aMatrix.myMatrix[8], aMatrix.myMatrix[9], aMatrix.myMatrix[10], aMatrix.myMatrix[11]);
		CommonUtilities::Vector::Vector4<T> row4(aMatrix.myMatrix[12], aMatrix.myMatrix[13], aMatrix.myMatrix[14], aMatrix.myMatrix[15]);

		CommonUtilities::Vector::Vector4<T> column1(aSecondMatrix.myMatrix[0], aSecondMatrix.myMatrix[4], aSecondMatrix.myMatrix[8], aSecondMatrix.myMatrix[12]);
		CommonUtilities::Vector::Vector4<T> column2(aSecondMatrix.myMatrix[1], aSecondMatrix.myMatrix[5], aSecondMatrix.myMatrix[9], aSecondMatrix.myMatrix[13]);
		CommonUtilities::Vector::Vector4<T> column3(aSecondMatrix.myMatrix[2], aSecondMatrix.myMatrix[6], aSecondMatrix.myMatrix[10], aSecondMatrix.myMatrix[14]);
		CommonUtilities::Vector::Vector4<T> column4(aSecondMatrix.myMatrix[3], aSecondMatrix.myMatrix[7], aSecondMatrix.myMatrix[11], aSecondMatrix.myMatrix[15]);

		aMatrix.myMatrix[0] = CommonUtilities::Vector::Dot(row1, column1);
		aMatrix.myMatrix[1] = CommonUtilities::Vector::Dot(row1, column2);
		aMatrix.myMatrix[2] = CommonUtilities::Vector::Dot(row1, column3);
		aMatrix.myMatrix[3] = CommonUtilities::Vector::Dot(row1, column4);
		aMatrix.myMatrix[4] = CommonUtilities::Vector::Dot(row2, column1);
		aMatrix.myMatrix[5] = CommonUtilities::Vector::Dot(row2, column2);
		aMatrix.myMatrix[6] = CommonUtilities::Vector::Dot(row2, column3);
		aMatrix.myMatrix[7] = CommonUtilities::Vector::Dot(row2, column4);
		aMatrix.myMatrix[8] = CommonUtilities::Vector::Dot(row3, column1);
		aMatrix.myMatrix[9] = CommonUtilities::Vector::Dot(row3, column2);
		aMatrix.myMatrix[10] = CommonUtilities::Vector::Dot(row3, column3);
		aMatrix.myMatrix[11] = CommonUtilities::Vector::Dot(row3, column4);
		aMatrix.myMatrix[12] = CommonUtilities::Vector::Dot(row4, column1);
		aMatrix.myMatrix[13] = CommonUtilities::Vector::Dot(row4, column2);
		aMatrix.myMatrix[14] = CommonUtilities::Vector::Dot(row4, column3);
		aMatrix.myMatrix[15] = CommonUtilities::Vector::Dot(row4, column4);

		return aMatrix;
	}

	template <typename T>
	const Vector::Vector4<T> operator*(const Vector::Vector4<T> &aVector, const Matrix44<T> &aMatrix)
	{
		Vector::Vector4<T> column1(aMatrix.myMatrix[0], aMatrix.myMatrix[4], aMatrix.myMatrix[8], aMatrix.myMatrix[12]);
		Vector::Vector4<T> column2(aMatrix.myMatrix[1], aMatrix.myMatrix[5], aMatrix.myMatrix[9], aMatrix.myMatrix[13]);
		Vector::Vector4<T> column3(aMatrix.myMatrix[2], aMatrix.myMatrix[6], aMatrix.myMatrix[10], aMatrix.myMatrix[14]);
		Vector::Vector4<T> column4(aMatrix.myMatrix[3], aMatrix.myMatrix[7], aMatrix.myMatrix[11], aMatrix.myMatrix[15]);

		return Vector::Vector4<T>(Vector::Dot(aVector, column1), Vector::Dot(aVector, column2), Vector::Dot(aVector, column3), Vector::Dot(aVector, column4));
	}

	template <typename T>
	const bool operator==(const Matrix44<T> &aMatrix, const Matrix44<T> &aSecondMatrix)
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
											if (aMatrix.myMatrix[9] == aSecondMatrix.myMatrix[9])
											{
												if (aMatrix.myMatrix[10] == aSecondMatrix.myMatrix[10])
												{
													if (aMatrix.myMatrix[11] == aSecondMatrix.myMatrix[11])
													{
														if (aMatrix.myMatrix[12] == aSecondMatrix.myMatrix[12])
														{
															if (aMatrix.myMatrix[13] == aSecondMatrix.myMatrix[13])
															{
																if (aMatrix.myMatrix[14] == aSecondMatrix.myMatrix[14])
																{
																	if (aMatrix.myMatrix[15] == aSecondMatrix.myMatrix[15])
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
	const Matrix44<T>& Matrix44<T>::operator=(const Matrix44<T> &aSecondMatrix)
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
		myMatrix[9] = aSecondMatrix.myMatrix[9];
		myMatrix[10] = aSecondMatrix.myMatrix[10];
		myMatrix[11] = aSecondMatrix.myMatrix[11];
		myMatrix[12] = aSecondMatrix.myMatrix[12];
		myMatrix[13] = aSecondMatrix.myMatrix[13];
		myMatrix[14] = aSecondMatrix.myMatrix[14];
		myMatrix[15] = aSecondMatrix.myMatrix[15];

		return *this;
	}

	template <typename T>
	const Vector::Vector4<T> Matrix44<T>::GetForward() const
	{
		return Vector::Vector4<T>(myMatrix[8], myMatrix[9], myMatrix[10], myMatrix[11]);
	}

	template <typename T>
	const Vector::Vector4<T> Matrix44<T>::GetUp() const
	{
		return Vector::Vector4<T>(myMatrix[4], myMatrix[5], myMatrix[6], myMatrix[7]);
	}

	template <typename T>
	const Vector::Vector4<T> Matrix44<T>::GetRight() const
	{
		return Vector::Vector4<T>(myMatrix[0], myMatrix[1], myMatrix[2], myMatrix[3]);
	}

	template <typename T>
	void Matrix44<T>::SetForward(const Vector::Vector4<T> &aVector)
	{
		myMatrix[8] = aVector.x;
		myMatrix[9] = aVector.y;
		myMatrix[10] = aVector.z;
		myMatrix[11] = aVector.w;
	}

	template <typename T>
	void Matrix44<T>::SetUp(const Vector::Vector4<T> &aVector)
	{
		myMatrix[4] = aVector.x;
		myMatrix[5] = aVector.y;
		myMatrix[6] = aVector.z;
		myMatrix[7] = aVector.w;
	}

	template <typename T>
	void Matrix44<T>::SetRight(const Vector::Vector4<T> &aVector)
	{
		myMatrix[0] = aVector.x;
		myMatrix[1] = aVector.y;
		myMatrix[2] = aVector.z;
		myMatrix[3] = aVector.w;
	}

	template <typename T>
	void Matrix44<T>::SetForward(T aX, T aY, T aZ, T aW)
	{
		SetForward({ aX, aY, aZ, aW });
	}

	template <typename T>
	void Matrix44<T>::SetUp(T aX, T aY, T aZ, T aW)
	{
		SetUp({ aX, aY, aZ, aW });
	}

	template <typename T>
	void Matrix44<T>::SetRight(T aX, T aY, T aZ, T aW)
	{
		SetRight({ aX, aY, aZ, aW });
	}

	template <typename T>
	Matrix44<T>::Matrix44()
	{
		myMatrix[0] = 1;
		myMatrix[1] = 0;
		myMatrix[2] = 0;
		myMatrix[3] = 0;
		myMatrix[4] = 0;
		myMatrix[5] = 1;
		myMatrix[6] = 0;
		myMatrix[7] = 0;
		myMatrix[8] = 0;
		myMatrix[9] = 0;
		myMatrix[10] = 1;
		myMatrix[11] = 0;
		myMatrix[12] = 0;
		myMatrix[13] = 0;
		myMatrix[14] = 0;
		myMatrix[15] = 1;
	}

	template <typename T>
	Matrix44<T>::Matrix44(const Matrix44 &aMatrix)
	{
		*this = aMatrix;
	}

	template <typename T>
	Matrix44<T> Matrix44<T>::CreateRotateAroundX(T aAngleInRadians)
	{
		Matrix44<T> tempMatrix;

		tempMatrix.myMatrix[0] = 1;
		tempMatrix.myMatrix[1] = 0;
		tempMatrix.myMatrix[2] = 0;
		tempMatrix.myMatrix[4] = 0;
		tempMatrix.myMatrix[5] = cos(aAngleInRadians);
		tempMatrix.myMatrix[6] = sin(aAngleInRadians);
		tempMatrix.myMatrix[8] = 0;
		tempMatrix.myMatrix[9] = -sin(aAngleInRadians);
		tempMatrix.myMatrix[10] = cos(aAngleInRadians);

		return tempMatrix;
	}

	template <typename T>
	Matrix44<T> Matrix44<T>::CreateRotateAroundY(T aAngleInRadians)
	{
		Matrix44<T> tempMatrix;

		tempMatrix.myMatrix[0] = cos(aAngleInRadians);
		tempMatrix.myMatrix[1] = 0;
		tempMatrix.myMatrix[2] = -sin(aAngleInRadians);
		tempMatrix.myMatrix[4] = 0;
		tempMatrix.myMatrix[5] = 1;
		tempMatrix.myMatrix[6] = 0;
		tempMatrix.myMatrix[8] = sin(aAngleInRadians);
		tempMatrix.myMatrix[9] = 0;
		tempMatrix.myMatrix[10] = cos(aAngleInRadians);

		return tempMatrix;
	}

	template <typename T>
	Matrix44<T> Matrix44<T>::CreateRotateAroundZ(T aAngleInRadians)
	{
		Matrix44<T> tempMatrix;

		tempMatrix.myMatrix[0] = cos(aAngleInRadians);
		tempMatrix.myMatrix[1] = sin(aAngleInRadians);
		tempMatrix.myMatrix[2] = 0;
		tempMatrix.myMatrix[4] = -sin(aAngleInRadians);
		tempMatrix.myMatrix[5] = cos(aAngleInRadians);
		tempMatrix.myMatrix[6] = 0;
		tempMatrix.myMatrix[8] = 0;
		tempMatrix.myMatrix[9] = 0;
		tempMatrix.myMatrix[10] = 1;

		return tempMatrix;
	}

	template <typename T>
	Matrix44<T> MatrixTranspose(const Matrix44<T> &aMatrixToTranspose)
	{
		Matrix44<T> tempMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				tempMatrix.myMatrix[j + (i * 4)] = aMatrixToTranspose.myMatrix[i + (j * 4)];
			}
		}

		return tempMatrix;
	}

	template <typename T>
	void Matrix44<T>::Rotate3DX(T aRadian)
	{
		Matrix44<T> tempMatrix(*this);

		tempMatrix *= Matrix44<T>::CreateRotateAroundX();

		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[2] = tempMatrix.myMatrix[2];
		myMatrix[4] = tempMatrix.myMatrix[4];
		myMatrix[5] = tempMatrix.myMatrix[5];
		myMatrix[6] = tempMatrix.myMatrix[6];
		myMatrix[8] = tempMatrix.myMatrix[8];
		myMatrix[9] = tempMatrix.myMatrix[9];
		myMatrix[10] = tempMatrix.myMatrix[10];
	}

	template <typename T>
	void Matrix44<T>::Rotate3DY(T aRadian)
	{
		Matrix44<T> tempMatrix(*this);

		tempMatrix *= Matrix44<T>::CreateRotateAroundY();

		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[2] = tempMatrix.myMatrix[2];
		myMatrix[4] = tempMatrix.myMatrix[4];
		myMatrix[5] = tempMatrix.myMatrix[5];
		myMatrix[6] = tempMatrix.myMatrix[6];
		myMatrix[8] = tempMatrix.myMatrix[8];
		myMatrix[9] = tempMatrix.myMatrix[9];
		myMatrix[10] = tempMatrix.myMatrix[10];
	}

	template <typename T>
	void Matrix44<T>::Rotate3DZ(T aRadian)
	{
		Matrix44<T> tempMatrix(*this);

		tempMatrix *= Matrix44<T>::CreateRotateAroundZ();

		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[2] = tempMatrix.myMatrix[2];
		myMatrix[4] = tempMatrix.myMatrix[4];
		myMatrix[5] = tempMatrix.myMatrix[5];
		myMatrix[6] = tempMatrix.myMatrix[6];
		myMatrix[8] = tempMatrix.myMatrix[8];
		myMatrix[9] = tempMatrix.myMatrix[9];
		myMatrix[10] = tempMatrix.myMatrix[10];
	}

	template <typename T>
	void Matrix44<T>::SetRotation3DX(T aRadian)
	{
		Matrix44<T> tempMatrix(Matrix44<T>::CreateRotateAroundX());

		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[2] = tempMatrix.myMatrix[2];
		myMatrix[4] = tempMatrix.myMatrix[4];
		myMatrix[5] = tempMatrix.myMatrix[5];
		myMatrix[6] = tempMatrix.myMatrix[6];
		myMatrix[8] = tempMatrix.myMatrix[8];
		myMatrix[9] = tempMatrix.myMatrix[9];
		myMatrix[10] = tempMatrix.myMatrix[10];
	}

	template <typename T>
	void Matrix44<T>::SetRotation3DY(T aRadian)
	{
		Matrix44<T> tempMatrix(Matrix44<T>::CreateRotateAroundY());

		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[2] = tempMatrix.myMatrix[2];
		myMatrix[4] = tempMatrix.myMatrix[4];
		myMatrix[5] = tempMatrix.myMatrix[5];
		myMatrix[6] = tempMatrix.myMatrix[6];
		myMatrix[8] = tempMatrix.myMatrix[8];
		myMatrix[9] = tempMatrix.myMatrix[9];
		myMatrix[10] = tempMatrix.myMatrix[10];
	}

	template <typename T>
	void Matrix44<T>::SetRotation3DZ(T aRadian)
	{
		Matrix44<T> tempMatrix(Matrix44<T>::CreateRotateAroundZ());

		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[2] = tempMatrix.myMatrix[2];
		myMatrix[4] = tempMatrix.myMatrix[4];
		myMatrix[5] = tempMatrix.myMatrix[5];
		myMatrix[6] = tempMatrix.myMatrix[6];
		myMatrix[8] = tempMatrix.myMatrix[8];
		myMatrix[9] = tempMatrix.myMatrix[9];
		myMatrix[10] = tempMatrix.myMatrix[10];
	}

	template <typename T>
	const Vector::Vector3<T> Matrix44<T>::GetPosition() const
	{
		return CommonUtilities::Vector::Vector3<T>(myMatrix[12], myMatrix[13], myMatrix[14]);
	}

	template <typename T>
	void Matrix44<T>::SetPosition(T aX, T aY, T aZ)
	{
		myMatrix[12] = aX;
		myMatrix[13] = aY;
		myMatrix[14] = aZ;
	}

	template <typename T>
	void Matrix44<T>::SetPosition(const Vector::Vector3<T> &aVector)
	{
		myMatrix[12] = aVector.x;
		myMatrix[13] = aVector.y;
		myMatrix[14] = aVector.z;
	}

	template <typename T>
	const CommonUtilities::Vector::Vector4<T> Matrix44<T>::GetTranslation() const
	{
		return CommonUtilities::Vector::Vector4<T>(myMatrix[12], myMatrix[13], myMatrix[14], myMatrix[15]);
	}

	template <typename T>
	void Matrix44<T>::SetTranslation(T aX, T aY, T aZ, T aW)
	{
		myMatrix[12] = aX;
		myMatrix[13] = aY;
		myMatrix[14] = aZ;
		myMatrix[15] = aW;
	}

	template <typename T>
	void Matrix44<T>::SetTranslation(const Vector::Vector4<T> &aVector)
	{
		myMatrix[12] = aVector.x;
		myMatrix[13] = aVector.y;
		myMatrix[14] = aVector.z;
		myMatrix[15] = aVector.w;
	}

	template <typename T>
	Matrix44<T> Matrix44<T>::GetInverse() const
	{
		Matrix44<T> inversedMatrix = *this;

		Vector::Vector4<T> translation;
		translation = inversedMatrix.GetTranslation();
		translation.x *= -1;
		translation.y *= -1;
		translation.z *= -1;
		translation.w = 1;

		inversedMatrix.SetTranslation(0.f, 0.f, 0.f, 1.f);
		inversedMatrix = MatrixTranspose(inversedMatrix);

		translation = translation * inversedMatrix;

		inversedMatrix.SetTranslation(translation.x, translation.y, translation.z, translation.w);

		return inversedMatrix;
	}

	template <typename T>
	Matrix44<T> Matrix44<T>::CreateProjectionMatrixLH(T aNearZ, T aFarZ, T anAspectRatio, T aFovAngle)
	{
		Matrix44 temp;
		T SinFov;
		T CosFov;
		T Height;
		T Width;

		SinFov = sin(0.5f * aFovAngle);
		CosFov = cos(0.5f * aFovAngle);

		Width = CosFov / SinFov;
		Height = Width / anAspectRatio;

		T scaling = aFarZ / (aFarZ - aNearZ);

		temp.myMatrix[0] = Width;
		temp.myMatrix[5] = Height;
		temp.myMatrix[10] = scaling;
		temp.myMatrix[11] = 1.0f;

		temp.myMatrix[14] = -scaling * aNearZ;
		temp.myMatrix[15] = 0.0f;
		return temp;
	}
}