#include "stdafx.h"
#include "FleeController.h"

#include "Actor.h"
#include <random>

FleeController::FleeController()
{
	myFleeRadius = 0.1;
	myMaxSpeed = 0.5;
}

FleeController::FleeController(Actor* aFleeTarget) : FleeController()
{
	myFleeTarget = aFleeTarget;
}

FleeController::~FleeController()
{
}

CommonUtilities::Vector::Vector2<float> FleeController::GetDirection()
{
	CommonUtilities::Vector::Vector2<float> position = myParent->GetPosition();
	CommonUtilities::Vector::Vector2<float> fleePosition = myFleeTarget->GetPosition();

	CommonUtilities::Vector::Vector2<float> direction = position - fleePosition;

	if (direction.x == 0 && direction.y == 0)
	{
		direction.x = rand();
		direction.y = rand();
	}

	if (CommonUtilities::Vector::Length2(direction) <= myFleeRadius * myFleeRadius)
	{
		direction = CommonUtilities::Vector::GetNormalized(direction) * myMaxSpeed * (1 - (CommonUtilities::Vector::Length(direction) / myFleeRadius));
	}
	else
	{
		direction.x = 0;
		direction.y = 0;
	}

	return direction;
}