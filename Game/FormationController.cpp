#include "stdafx.h"
#include "FormationController.h"

#include "Formation.h"
#include "Actor.h"
#include "..\CommonUtilities\GrowingArray.h"
#include "PollingStation.h"
#include "Obstacle.h"

#define SLOWDOWN_RADIUS 0.1f
#define UNIT_AVOID_DISTANCE 0.04f
#define OBSTACLE_AVOID_DISTANCE 0.06f

FormationController::FormationController()
{
	mySpeed = 0.5f;
}

FormationController::FormationController(Formation* aFormation) : FormationController()
{
	myFormation = aFormation;
}

FormationController::~FormationController()
{
}

CommonUtilities::Vector::Vector2<float> FormationController::GetDirection()
{
	CommonUtilities::Vector::Vector2<float> direction = Arrive() * 1.01f + AvoidUnits() + AvoidObstacles();
	CommonUtilities::Vector::Vector2<float> normalizedDirection = CommonUtilities::Vector::GetNormalized(direction) * mySpeed;

	if (abs(normalizedDirection.x) < abs(direction.x))
	{
		direction.x = normalizedDirection.x;
	}

	if (abs(normalizedDirection.y) < abs(direction.y))
	{
		direction.y = normalizedDirection.y;
	}

	return direction;
}

CommonUtilities::Vector::Vector2<float> FormationController::Arrive()
{
	CommonUtilities::Vector::Vector2<float> targetPosition = myFormation->GetTargetPostion(this);
	CommonUtilities::Vector::Vector2<float> currentPosition = myParent->GetPosition();

	CommonUtilities::Vector::Vector2<float> direction = targetPosition - currentPosition;

	if (direction.x == 0 && direction.y == 0)
	{
		return direction;
	}

	if (CommonUtilities::Vector::Length2(direction) <= SLOWDOWN_RADIUS * SLOWDOWN_RADIUS)
	{
		direction = GetNormalized(direction) * mySpeed * (CommonUtilities::Vector::Length(direction) / SLOWDOWN_RADIUS);
	}
	else
	{
		direction = GetNormalized(direction) * mySpeed;
	}

	return direction;
}

CommonUtilities::Vector::Vector2<float> FormationController::AvoidUnits()
{
	CommonUtilities::Containers::GrowingArray<Actor*>& actors = PollingStation::GetInstance()->GetActors();

	CommonUtilities::Vector::Vector2<float> result = { 0, 0 };

	for (Actor* actor : actors)
	{
		if (actor != myParent)
		{
			CommonUtilities::Vector::Vector2<float> direction = myParent->GetPosition() - actor->GetPosition();

			if (CommonUtilities::Vector::Length2(direction) <= UNIT_AVOID_DISTANCE * UNIT_AVOID_DISTANCE)
			{
				result += CommonUtilities::Vector::GetNormalized(direction) * (1 - (CommonUtilities::Vector::Length(direction) / UNIT_AVOID_DISTANCE));
			}
		}
	}

	if (result.x != 0 || result.y != 0)
	{
		CommonUtilities::Vector::Normalize(result);
	}

	result *= mySpeed;

	return result;
}

CommonUtilities::Vector::Vector2<float> FormationController::AvoidObstacles()
{
	CommonUtilities::Containers::GrowingArray<Obstacle*>& obstacles = PollingStation::GetInstance()->GetObstacles();

	CommonUtilities::Vector::Vector2<float> result = { 0, 0 };

	for (Obstacle* obstacle : obstacles)
	{
		CommonUtilities::Vector::Vector2<float> direction = myParent->GetPosition() - obstacle->GetPosition();

		if (CommonUtilities::Vector::Length2(direction) <= OBSTACLE_AVOID_DISTANCE * OBSTACLE_AVOID_DISTANCE)
		{
			result += CommonUtilities::Vector::GetNormalized(direction) * (1 - (CommonUtilities::Vector::Length(direction) / OBSTACLE_AVOID_DISTANCE));
		}
	}

	if (result.x != 0 || result.y != 0)
	{
		CommonUtilities::Vector::Normalize(result);
	}

	result *= mySpeed;

	return result;
}