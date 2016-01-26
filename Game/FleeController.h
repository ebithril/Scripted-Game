#pragma once

#include "Controller.h"

class FleeController : public Controller
{
public:
	FleeController();
	FleeController(Actor* aFleeTarget);
	~FleeController();

	CommonUtilities::Vector::Vector2<float> GetDirection() override;

private:
	Actor* myFleeTarget;
	float myFleeRadius;
	float myMaxSpeed;
};