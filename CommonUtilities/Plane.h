#pragma once

#include "Vector3.h"
#include "Vector4.h"

namespace CommonUtilities
{
	template <typename T>
	class Plane
	{
	public:
		Plane();
		Plane(Vector::Vector3<T> aFirstPoint, Vector::Vector3<T> aSecondPoint, Vector::Vector3<T> aThirdPoint);
		Plane(Vector::Vector3<T> aPoint, Vector::Vector3<T> aNormal);
		bool operator==(Plane<T> aPlane);
		void InitWith3Points(Vector::Vector3<T> aFirstPoint, Vector::Vector3<T> aSecondPoint, Vector::Vector3<T> aThirdPoint);
		void InitWithPointAndNormal(Vector::Vector3<T> aPoint, Vector::Vector3<T> aNormal);
		bool Inside(Vector::Vector3<T> aPosition);
	private:
		Vector::Vector4<T> myData;
	};
}

namespace CommonUtilities
{
	template <typename T>
	Plane<T>::Plane()
	{
	}

	template <typename T>
	Plane<T>::Plane(Vector::Vector3<T> aFirstPoint, Vector::Vector3<T> aSecondPoint, Vector::Vector3<T> aThirdPoint)
	{
		InitWith3Points(aFirstPoint, aSecondPoint, aThirdPoint);
	}
	
	template <typename T>
	Plane<T>::Plane(Vector::Vector3<T> aPoint, Vector::Vector3<T> aNormal)
	{
		InitWithPointAndNormal(aPoint, aNormal);
	}
	
	template <typename T>
	void Plane<T>::InitWith3Points(Vector::Vector3<T> aFirstPoint, Vector::Vector3<T> aSecondPoint, Vector::Vector3<T> aThirdPoint)
	{
		Vector::Vector3<T> tempVector(Vector::Cross(aSecondPoint - aFirstPoint, aThirdPoint - aFirstPoint));

		myData.x = tempVector.x;
		myData.y = tempVector.y;
		myData.z = tempVector.z;
		myData.w = Vector::Dot(tempVector, aFirstPoint);
	}
	
	template <typename T>
	void Plane<T>::InitWithPointAndNormal(Vector::Vector3<T> aPoint, Vector::Vector3<T> aNormal)
	{
		myData.x = aNormal.x;
		myData.y = aNormal.y;
		myData.z = aNormal.z;
		myData.w = Vector::Dot(aNormal, aPoint);
	}
	
	template <typename T>
	bool Plane<T>::Inside(Vector::Vector3<T> aPosition)
	{
		return (Vector::Dot(aPosition - (Vector::Vector3<T>(myData.x, myData.y, myData.z) * myData.w), Vector::Vector3<T>(myData.x, myData.y, myData.z)) <= 0);
	}

	template <typename T>
	bool Plane<T>::operator==(Plane<T> aPlane)
	{
		if (myData.x == aPlane.myData.x)
		{
			if (myData.y == aPlane.myData.y)
			{
				if (myData.z == aPlane.myData.z)
				{
					if (myData.w == aPlane.myData.w)
					{
						return true;
					}
				}
			}
		}

		return false;
	}
}