#pragma once

#include "Line.h"
#include "GrowingArray.h"
#include "Macros.h"

namespace CommonUtilities
{
	template <typename T>
	class LineVolume
	{
	public:
		LineVolume();
		LineVolume(Containers::GrowingArray<Line<T>> &aLineList);
		void AddLine(Line<T> aLine);
		void RemoveLine(Line<T> aLine);
		bool Inside(Vector::Vector2<T> aPosition);
	private:
		Containers::GrowingArray<Line<T>> myLineList;
	};
}

namespace CommonUtilities
{
	template <typename T>
	LineVolume<T>::LineVolume()
	{
		myLineList.Init(4);
	}

	template <typename T>
	LineVolume<T>::LineVolume(Containers::GrowingArray<Line<T>> &aLineList)
	{
		myLineList = aLineList;
	}

	template <typename T>
	void LineVolume<T>::AddLine(Line<T> aLine)
	{
		myLineList.Add(aLine);
	}

	template <typename T>
	void LineVolume<T>::RemoveLine(Line<T> aLine)
	{
		myLineList.RemoveCyclic(aLine);
	}

	template <typename T>
	bool LineVolume<T>::Inside(Vector::Vector2<T> aPosition)
	{
		FOR_EACH_GA(myLineList)
		{
			if (myLineList[i].Inside(aPosition) == false)
			{
				return false;
			}
		}

		return true;
	}
}