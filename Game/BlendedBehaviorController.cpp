#include "stdafx.h"
#include "BlendedBehaviorController.h"

#include "Macros.h"
#include "..\CommonUtilities\Matrix33.h"
#include "PollingStation.h"
#include "Actor.h"

#define WALL_AVOID_DISTANCE 0.1f
#define UNIT_AVOID_DISTANCE 0.05f

BlendedBehaviorController::BlendedBehaviorController()
{
	myFramesToWait = 0;
	myLastFrameWander = { 0, 0 };
	mySpeed = 0.5;

	myLastFrameWander.x = RANDOM_FLOAT(1.f, -1.f);
	myLastFrameWander.y = RANDOM_FLOAT(1.f, -1.f);

	CommonUtilities::Vector::Normalize(myLastFrameWander);

	myLastFrameWander *= fmax(fmin((mySpeed / 2.f) + RANDOM_FLOAT(0.1f, -0.1f), mySpeed), 0.1f);
	myLastFrameDirection = { 0, 0 };

	myTargetPosition = { -1.f, -1.f };
}

BlendedBehaviorController::~BlendedBehaviorController()
{
}

CommonUtilities::Vector::Vector2<float> BlendedBehaviorController::GetDirection()
{
	CommonUtilities::Vector::Vector2<float> direction = (Wander() * 0.4f) + (AvoidWalls() * 1.f) + (AvoidUnits() * 1.5f) + (Seek() * 5.f) + myLastFrameDirection * 0.5f;

	if (CommonUtilities::Vector::Length(direction) > mySpeed)
	{
		CommonUtilities::Vector::Normalize(direction);
		direction *= mySpeed;
	}

	myLastFrameDirection = direction;

	return direction;
}

void BlendedBehaviorController::SetTargetPosition(const CommonUtilities::Vector::Vector2<float>& aVector)
{
	myTargetPosition = aVector;
}

CommonUtilities::Vector::Vector2<float> BlendedBehaviorController::Wander()
{
	--myFramesToWait;

	if (myFramesToWait <= 0)
	{
		float currentSpeed = CommonUtilities::Vector::Length(myLastFrameWander);

		CommonUtilities::Vector::Normalize(myLastFrameWander);

		myLastFrameWander = myLastFrameWander * CommonUtilities::Matrix33<float>::CreateRotateAroundZ(RANDOM_FLOAT(1.f, -1.f));

		myLastFrameWander *= fmax(fmin(currentSpeed + RANDOM_FLOAT(0.1f, -0.1f), mySpeed), 0.1f);

		myFramesToWait = rand() % 300;
	}

	return myLastFrameWander;
}

CommonUtilities::Vector::Vector2<float> BlendedBehaviorController::AvoidWalls()
{
	CommonUtilities::Vector::Vector2<float> position = myParent->GetPosition();
	CommonUtilities::Vector::Vector2<float> direction = { 0, 0 };

	if (position.y <= WALL_AVOID_DISTANCE)
	{
		direction.y += ((1.f - position.y) / WALL_AVOID_DISTANCE);
	}
	if (position.y >= 1 - WALL_AVOID_DISTANCE)
	{
		direction.y += ((1.f - (1.f - position.y)) / WALL_AVOID_DISTANCE) * -1.f;
	}

	if (position.x <= WALL_AVOID_DISTANCE)
	{
		direction.x += ((1.f - position.x) / WALL_AVOID_DISTANCE);
	}
	if (position.x >= 1 - WALL_AVOID_DISTANCE)
	{
		direction.x += ((1.f - (1.f - position.x)) / WALL_AVOID_DISTANCE) * -1.f;
	}

	if (direction.x != 0 || direction.y != 0)
	{
		CommonUtilities::Vector::Normalize(direction);
	}

	return direction * mySpeed;
}

CommonUtilities::Vector::Vector2<float> BlendedBehaviorController::AvoidUnits()
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

CommonUtilities::Vector::Vector2<float> BlendedBehaviorController::Seek()
{
	if (myTargetPosition.x != -1.f && myTargetPosition.y != -1.f)
	{
		CommonUtilities::Vector::Vector2<float> position = myParent->GetPosition();
		CommonUtilities::Vector::Vector2<float> direction = myTargetPosition - position;

		if (CommonUtilities::Vector::Length(direction) < 0.07f)
		{
			myTargetPosition = { -1.f, -1.f };
		}

		return direction;
	}

	return { 0, 0 };
}