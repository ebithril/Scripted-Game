#include "stdafx.h"
#include "Formation.h"

#include "..\CommonUtilities\Matrix33.h"
#include "Obstacle.h"
#include "PollingStation.h"

#include <cmath>

#define SLOWDOWN_RADIUS 0.1f
#define PI 3.14159265358f
#define OBSTACLE_AVOID_DISTANCE 0.3f

Formation::Formation()
{
	myPosition = { 0.5f, 0.5f };
	myTargetPosition = { 0.5f, 0.5f };
	mySpeed = 0.2f;
	myRotation = 0;
}

Formation::~Formation()
{
}

CommonUtilities::Vector::Vector2<float> Formation::GetTargetPostion(FormationController* aUnitController)
{
	int index = 0;

	for (int i = 0; i < 15; i++)
	{
		if (aUnitController == myUnitControllers[i])
		{
			index = i;
			break;
		}
	}

	int xPos = (index % 3) - 1;
	int yPos = ((index - xPos) / 3) - 2;

	CommonUtilities::Vector::Vector2<float> offset = { float(xPos) * 0.05f, float(yPos) * 0.05f };

	offset = offset * CommonUtilities::Matrix33<float>::CreateRotateAroundZ(myRotation);

	CommonUtilities::Vector::Vector2<float> position = myPosition + offset;

	return position;
}

void Formation::SetUnitController(int aIndex, FormationController* aUnitController)
{
	myUnitControllers[aIndex] = aUnitController;
}

void Formation::SetTargetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition)
{
	myTargetPosition = aPosition;
	CommonUtilities::Vector::Vector2<float> direction = myTargetPosition - myPosition;
	CalcRotation(GetNormalized(direction));
}

void Formation::Update(float aDeltaTime)
{
	CommonUtilities::Vector::Vector2<float> direction = Arrive() * 2.f + AvoidObstacles();
	CommonUtilities::Vector::Vector2<float> normalizedDirection = CommonUtilities::Vector::GetNormalized(direction) * mySpeed;

	if (abs(normalizedDirection.x) < abs(direction.x))
	{
		direction.x = normalizedDirection.x;
	}

	if (abs(normalizedDirection.y) < abs(direction.y))
	{
		direction.y = normalizedDirection.y;
	}

	direction *= aDeltaTime;

	myPosition += direction;
}

void Formation::CalcRotation(CommonUtilities::Vector::Vector2<float> aDirection)
{
	float rotation = atan2f(aDirection.y, aDirection.x);

	if (rotation < -PI)
	{
		rotation += PI * 2;
	}
	else if (rotation > PI)
	{
		rotation -= PI * 2;
	}

	myRotation = rotation;
}

CommonUtilities::Vector::Vector2<float> Formation::Arrive()
{
	CommonUtilities::Vector::Vector2<float> direction = myTargetPosition - myPosition;

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

CommonUtilities::Vector::Vector2<float> Formation::AvoidObstacles()
{
	CommonUtilities::Containers::GrowingArray<Obstacle*>& obstacles = PollingStation::GetInstance()->GetObstacles();

	CommonUtilities::Vector::Vector2<float> result = { 0, 0 };

	for (Obstacle* obstacle : obstacles)
	{
		CommonUtilities::Vector::Vector2<float> direction = myPosition - obstacle->GetPosition();

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