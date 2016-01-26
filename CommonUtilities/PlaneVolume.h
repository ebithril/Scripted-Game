#pragma once

#include "Plane.h"
#include "GrowingArray.h"
#include "Macros.h"

namespace CommonUtilities
{
	template <typename T>
	class PlaneVolume
	{
	public:
		PlaneVolume(Containers::GrowingArray<Plane<T>> aPlaneList);
		void AddPlane(Plane<T > aPlane);
		void RemovePlane(Plane<T> aPlane);
		bool Inside(Vector::Vector3<T> aPosition);
	private:
		Containers::GrowingArray<Plane<T>> myPlaneList;
	};
}

namespace CommonUtilities
{
	template <typename T>
	PlaneVolume<T>::PlaneVolume(Containers::GrowingArray<Plane<T>> aPlaneList)
	{
		myPlaneList = aPlaneList;
	}

	template <typename T>
	void PlaneVolume<T>::AddPlane(Plane<T > aPlane)
	{
		myPlaneList.Add(aPlane);
	}

	template <typename T>
	void PlaneVolume<T>::RemovePlane(Plane<T> aPlane)
	{
		myPlaneList.RemoveCyclic(aPlane);
	}

	template <typename T>
	bool PlaneVolume<T>::Inside(Vector::Vector3<T> aPosition)
	{
		FOR_EACH_GA(myPlaneList)
		{
			if (myPlaneList[i].Inside(aPosition) == false)
			{
				return false;
			}
		}

		return false;
	}
}