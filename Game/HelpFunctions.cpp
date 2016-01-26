#include "stdafx.h"
#include "HelpFunctions.h"

DX2D::Vector2f ConvertToDXD2DVector(const CommonUtilities::Vector::Vector2<float>& aVector)
{
	return{ aVector.x, aVector.y };
}

CommonUtilities::Vector::Vector2<float> ConvertToCUVector(const DX2D::Vector2f& aVector)
{
	return{ aVector.x, aVector.y };
}