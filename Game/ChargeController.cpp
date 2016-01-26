#include "stdafx.h"
#include "ChargeController.h"

#include "Actor.h"

ChargeController::ChargeController()
{
	mySlowRadius = 0.1;
	myMaxSpeed = 0.5;
	myTargetPosition = { 0.9f, 0.4f };
}

ChargeController::~ChargeController()
{
}

void ChargeController::SetTargetPosition(const CommonUtilities::Vector::Vector2<float>& aTargetPosition)
{
	myTargetPosition = aTargetPosition;
}

CommonUtilities::Vector::Vector2<float> ChargeController::GetDirection()
{
	CommonUtilities::Vector::Vector2<float> position = myParent->GetPosition();

	CommonUtilities::Vector::Vector2<float> direction = myTargetPosition - position;

	if (direction.x == 0 && direction.y == 0)
	{
		return direction;
	}

	if (CommonUtilities::Vector::Length2(direction) <= mySlowRadius * mySlowRadius)
	{
		direction = GetNormalized(direction) * myMaxSpeed * (CommonUtilities::Vector::Length(direction) / mySlowRadius);
	}
	else
	{
		direction = GetNormalized(direction) * myMaxSpeed;
	}

	return direction;
}