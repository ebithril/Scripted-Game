#pragma once

#include "..\CommonUtilities\Vector2.h"
#include <tga2d\sprite\sprite.h>

#include <memory>

namespace Script
{
	class VisualScript;
}
class Box;
class Controller;

class Actor
{
public:
	Actor();
	~Actor();

	void Update(float aDeltaTime);

	void SetController(Controller* aController);

	void SetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition);
	void GoToBox(Box* aBox);

	const CommonUtilities::Vector::Vector2<float>& GetPosition() const;

	void Render();
	Controller* GetController();

	int GetID();

	int GetHealth();
	void GoToPosition(const CommonUtilities::Vector::Vector2<float>& aPosition);

	bool GetIsFramme();
private:
	void ClampMovement(CommonUtilities::Vector::Vector2<float>& aMovement, const CommonUtilities::Vector::Vector2<float>& aSuggestedMovement);
	void UpdateRotation(const CommonUtilities::Vector::Vector2<float>& aSuggestedMovement);
	static int ourIdCounter;

	std::shared_ptr<Script::VisualScript> myScript;

	int myID;
	int myHealth;
	CommonUtilities::Vector::Vector2<float> myPosition;
	float mySpeed;
	Controller* myController;
	Box* myTargetBox;
	DX2D::CSprite* mySprite;
	CommonUtilities::Vector::Vector2<float> myGoToPosition;

	bool myIsFramme;
};