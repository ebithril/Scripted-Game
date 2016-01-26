#pragma once

#include "Controller.h"

class ChargeController : public Controller
{
public:
	ChargeController();
	~ChargeController();

	void SetTargetPosition(const CommonUtilities::Vector::Vector2<float>& aTargetPosition);

	CommonUtilities::Vector::Vector2<float> GetDirection() override;

private:
	CommonUtilities::Vector::Vector2<float> myTargetPosition;
	float mySlowRadius;
	float myMaxSpeed;
};