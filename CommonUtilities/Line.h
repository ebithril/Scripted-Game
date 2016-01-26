#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace CommonUtilities
{
	template <typename T>
	class Line
	{
	public:
		Line();
		Line(Vector::Vector2<T> aFirstPoint, Vector::Vector2<T> aSecondPoint);
		void InitWith2Points(Vector::Vector2<T> aFirstPoint, Vector::Vector2<T> aSecondPoint);
		void InitWithPointAndDirection(Vector::Vector2<T> aPoint, Vector::Vector2<T> aDirection);
		bool Inside(Vector::Vector2<T> aPosition);
		bool operator==(Line<T> aLinje);

		Vector::Vector3<T> myData;
	};
}

namespace CommonUtilities
{
	template <typename T>
	Line<T>::Line()
	{
	}

	template <typename T>
	Line<T>::Line(Vector::Vector2<T> aFirstPoint, Vector::Vector2<T> aSecondPoint)
	{
		InitWith2Points(aFirstPoint, aSecondPoint);
	}

	template <typename T>
	void Line<T>::InitWith2Points(Vector::Vector2<T> aFirstPoint, Vector::Vector2<T> aSecondPoint)
	{
		aFirstPoint -= aSecondPoint;
		Vector::Normalize(aFirstPoint);

		T oldX = aFirstPoint.x;

		aFirstPoint.x = -aFirstPoint.y;
		aFirstPoint.y = oldX;

		myData.x = aFirstPoint.x;
		myData.y = aFirstPoint.y;
		myData.z = Vector::Dot(aFirstPoint, aSecondPoint);
	}

	template <typename T>
	void Line<T>::InitWithPointAndDirection(Vector::Vector2<T> aPoint, Vector::Vector2<T> aDirection)
	{
		Vector::Normalize(aDirection);

		T oldX = aDirection.x;

		aDirection.x = -aDirection.y;
		aDirection.y = oldX;

		myData.x = aDirection.x;
		myData.y = aDirection.y;
		myData.z = Vector::Dot(aDirection, aPoint);
	}

	template <typename T>
	bool Line<T>::Inside(Vector::Vector2<T> aPosition)
	{
		return (Vector::Dot(aPosition - (Vector::Vector2<T>(myData.x, myData.y) * myData.z), Vector::Vector2<T>(myData.x, myData.y)) <= 0);
	}

	template <typename T>
	bool Line<T>::operator==(Line<T> aLinje)
	{
		if (myData.x == aLinje.myData.x)
		{
			if (myData.y == aLinje.myData.y)
			{
				if (myData.z == aLinje.myData.z)
				{
					return true;
				}
			}
		}

		return false;
	}
}