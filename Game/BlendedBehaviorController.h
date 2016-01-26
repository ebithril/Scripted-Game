#pragma once

#include "Controller.h"

class BlendedBehaviorController : public Controller
{
public:
	BlendedBehaviorController();
	~BlendedBehaviorController();

	CommonUtilities::Vector::Vector2<float> GetDirection() override;
	void SetTargetPosition(const CommonUtilities::Vector::Vector2<float>& aVector) override;
private:
	CommonUtilities::Vector::Vector2<float> Wander();
	CommonUtilities::Vector::Vector2<float> AvoidWalls();
	CommonUtilities::Vector::Vector2<float> AvoidUnits();
	CommonUtilities::Vector::Vector2<float> Seek();

	CommonUtilities::Vector::Vector2<float> myLastFrameWander;
	CommonUtilities::Vector::Vector2<float> myLastFrameDirection;

	CommonUtilities::Vector::Vector2<float> myTargetPosition;
	int myFramesToWait;
	float mySpeed;
};