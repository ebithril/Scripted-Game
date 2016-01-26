#include "stdafx.h"
#include "Intersection.h"

#include "Line.h"

bool LineVsLine(LineSegment aLine1, LineSegment aLine2, CommonUtilities::Vector::Vector2<float>& aIntersectionPoint)
{
	CommonUtilities::Line<float> line1(aLine1.myStartPos, aLine1.myEndPos);
	CommonUtilities::Line<float> line2(aLine2.myStartPos, aLine2.myEndPos);

	float numX = line2.myData.y * line1.myData.z - line1.myData.y * line2.myData.z;
	float denX = line1.myData.x * line2.myData.y - line2.myData.x * line1.myData.y;

	float numY = line1.myData.x * line2.myData.z - line2.myData.x * line1.myData.z;
	float denY = line1.myData.x * line2.myData.y - line2.myData.x * line1.myData.y;

	if (denX == 0 && denY == 0)
	{
		if (line1.myData.z != line2.myData.z)
		{
			return false;
		}

		CommonUtilities::Vector::Vector2<float> dir1 = aLine1.myEndPos - aLine1.myStartPos;
		CommonUtilities::Vector::Vector2<float> dir2 = aLine2.myEndPos - aLine2.myStartPos;

		float lengthDir1 = CommonUtilities::Vector::Length(dir1);
		dir1 /= lengthDir1;

		float lengthDir2 = CommonUtilities::Vector::Length(dir2);
		dir2 /= lengthDir2;

		if (CommonUtilities::Vector::Dot(dir1, aLine2.myEndPos - aLine1.myStartPos) < lengthDir1 &&
			CommonUtilities::Vector::Dot(dir1, aLine2.myEndPos - aLine1.myStartPos) > 0)
		{
			aIntersectionPoint = aLine2.myEndPos;
			return true;
		}

		if (CommonUtilities::Vector::Dot(dir1, aLine2.myStartPos - aLine1.myStartPos) < lengthDir1 &&
			CommonUtilities::Vector::Dot(dir1, aLine2.myStartPos - aLine1.myStartPos) > 0)
		{
			aIntersectionPoint = aLine2.myStartPos;
			return true;
		}

		if (CommonUtilities::Vector::Dot(dir2, aLine1.myEndPos - aLine2.myStartPos) < lengthDir2 &&
			CommonUtilities::Vector::Dot(dir2, aLine1.myEndPos - aLine2.myStartPos) > 0)
		{
			aIntersectionPoint = aLine1.myEndPos;
			return true;
		}

		if (CommonUtilities::Vector::Dot(dir2, aLine1.myStartPos - aLine2.myStartPos) < lengthDir2 &&
			CommonUtilities::Vector::Dot(dir2, aLine1.myStartPos - aLine2.myStartPos) > 0)
		{
			aIntersectionPoint = aLine1.myStartPos;
			return true;
		}

		return false;
	}

	aIntersectionPoint = CommonUtilities::Vector::Vector2<float>(numX / denX, numY / denY);


	CommonUtilities::Vector::Vector2<float> v1(aLine1.myEndPos - aLine1.myStartPos);

	CommonUtilities::Vector::Vector2<float> v1intersect(aIntersectionPoint - aLine1.myStartPos);

	if (CommonUtilities::Vector::Dot(v1, v1intersect) < 0 || CommonUtilities::Vector::Length2(v1intersect) > CommonUtilities::Vector::Length2(v1))
	{
		return false;
	}

	CommonUtilities::Vector::Vector2<float> v2(aLine2.myEndPos - aLine2.myStartPos);

	CommonUtilities::Vector::Vector2<float> v2intersect(aIntersectionPoint - aLine2.myStartPos);

	if (CommonUtilities::Vector::Dot(v2, v2intersect) < 0 || CommonUtilities::Vector::Length2(v2intersect) > CommonUtilities::Vector::Length2(v2))
	{
		return false;
	}

	return true;
}