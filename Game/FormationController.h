#pragma once
#include "Controller.h"

class Formation;

class FormationController : public Controller
{
public:
	FormationController();
	FormationController(Formation* aFormation);
	~FormationController();

	CommonUtilities::Vector::Vector2<float> GetDirection() override;

private:
	CommonUtilities::Vector::Vector2<float> AvoidUnits();
	CommonUtilities::Vector::Vector2<float> AvoidObstacles();
	CommonUtilities::Vector::Vector2<float> Arrive();
	float mySpeed;
	Formation* myFormation;
};