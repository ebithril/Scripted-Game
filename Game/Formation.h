#pragma once

#include "..\CommonUtilities\Vector2.h"
#include "..\CommonUtilities\StaticArray.h"

class FormationController;

class Formation
{
public:
	Formation();
	~Formation();

	CommonUtilities::Vector::Vector2<float> GetTargetPostion(FormationController* aUnitController);
	void SetUnitController(int aIndex, FormationController* aUnitController);
	void SetTargetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition);
	void Update(float aDeltaTime);
private:
	void CalcRotation(CommonUtilities::Vector::Vector2<float> aDirection);

	CommonUtilities::Vector::Vector2<float> Arrive();
	CommonUtilities::Vector::Vector2<float> AvoidObstacles();

	CommonUtilities::Containers::StaticArray<FormationController*, 15> myUnitControllers;
	CommonUtilities::Vector::Vector2<float> myPosition;
	CommonUtilities::Vector::Vector2<float> myTargetPosition;
	float myRotation;
	float mySpeed;
};