#include "stdafx.h"
#include "Box.h"
#include <tga2d/sprite/sprite.h>
#include "HelpFunctions.h"
Box::Box()
{
	mySprite = new DX2D::CSprite("Sprites/box.png");
	mySprite->SetPivot({ 0.5f, 0.5f });
	myWinterIsComing = false;
	myDimensions.x = 64.f / 1920.f;
	myDimensions.y = 64.f / 1080.f;
}


Box::~Box()
{
}


bool Box::TestCollision(const CommonUtilities::Vector::Vector2<float>& aPosition)
{
	CommonUtilities::Vector::Vector2<float> min;
	CommonUtilities::Vector::Vector2<float> max;

	min.x = myPosition.x - myDimensions.x;
	min.y = myPosition.y - myDimensions.y;
	max.x = myPosition.x + myDimensions.x;
	max.y = myPosition.y + myDimensions.y;

	if (aPosition.x < min.x)
	{
		return false;
	}
	if (aPosition.x > max.x)
	{
		return false;
	}
	if (aPosition.y < min.y)
	{
		return false;
	}
	if (aPosition.y > max.y)
	{
		return false;
	}
	return true;
}

void Box::SetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition)
{
	myPosition = aPosition;
}

const CommonUtilities::Vector::Vector2<float>& Box::GetPosition() const
{
	return myPosition;
}

void Box::Render()
{
	mySprite->SetPosition(ConvertToDXD2DVector(myPosition));

	mySprite->Render();
}

void Box::SetWinterIsComing(bool aWinterIsComing)
{
	myWinterIsComing = aWinterIsComing;
}

bool Box::GetWinterIsComing() const
{
	return myWinterIsComing;
}