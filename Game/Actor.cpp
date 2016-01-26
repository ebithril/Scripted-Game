#include "stdafx.h"
#include "Actor.h"

#include "Controller.h"
#include "PollingStation.h"
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/engine.h>

#include "HelpFunctions.h"

#include "../Script/VisualScript.h"
#include "../Script/LuaInterface.h"
#include "Box.h"

#define PI 3.14159265358f

#define SLOW_DOWN_RADIUS 0.05f
#define SLOW_DOWN_RADIUS_SQUARED (SLOW_DOWN_RADIUS * SLOW_DOWN_RADIUS)

int Actor::ourIdCounter = 0;

Actor::Actor() : myPosition(0, 0), myGoToPosition(0,0)
{
	myController = nullptr;
	mySprite = new DX2D::CSprite("Sprites/unit.dds");
	mySprite->SetPivot({ 0.5f, 0.5f });

	PollingStation::GetInstance()->AddActor(this);

	myID = ourIdCounter++;
	myHealth = 100;

	Script::LuaInterface* instance = Script::CreateLuaInterface();

	myScript = instance->LoadVisualScript("Script/Scripts/ActorScript.xml");

	myScript->SetGameObjectID(myID);

	myTargetBox = nullptr;
	myIsFramme = true;
	myScript->Start();
	instance->Release();
}

Actor::~Actor()
{
}

void Actor::Update(float aDeltaTime)
{ 
	CommonUtilities::Vector::Vector2<float> direction = myGoToPosition - myPosition;

	float lengthSquared = CommonUtilities::Vector::Length2(direction);

	if (lengthSquared < SLOW_DOWN_RADIUS_SQUARED)
	{
		float speedFactor = (lengthSquared / SLOW_DOWN_RADIUS_SQUARED);

		direction = CommonUtilities::Vector::GetNormalized(direction) * speedFactor;

		if (speedFactor <= 0.01)
		{
			myIsFramme = true;

			if (myTargetBox != nullptr)
			{
				myTargetBox->SetWinterIsComing(false);
				myTargetBox = nullptr;
			}
		}
	}
	else
	{
		direction = CommonUtilities::Vector::GetNormalized(direction);
	}

	myPosition += direction * 0.5f * aDeltaTime;

	mySprite->SetPosition(DX2D::Vector2f(myPosition.x, myPosition.y));

}

void Actor::SetController(Controller* aController)
{
	myController = aController;
	myController->SetParent(this);

	myController->Init();
}

void Actor::SetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition)
{
	myPosition = aPosition;

	mySprite->SetPosition(DX2D::Vector2f(myPosition.x, myPosition.y));
}

const CommonUtilities::Vector::Vector2<float>& Actor::GetPosition() const
{
	return myPosition;
}

void Actor::Render()
{
	mySprite->Render();
}

Controller* Actor::GetController()
{
	return myController;
}

int Actor::GetID()
{
	return myID;
}

int Actor::GetHealth()
{
	return myHealth;
}

void Actor::ClampMovement(CommonUtilities::Vector::Vector2<float>& aMovement, const CommonUtilities::Vector::Vector2<float>& aSuggestedMovement)
{
	if (aMovement.x > aSuggestedMovement.x)
	{
		aMovement.x = aSuggestedMovement.x;
	}
	else if (aMovement.y > aSuggestedMovement.y)
	{
		aMovement.y = aSuggestedMovement.y;
	}
}

void Actor::UpdateRotation(const CommonUtilities::Vector::Vector2<float>& aSuggestedMovement)
{
	float rotation = atan2f(aSuggestedMovement.y, aSuggestedMovement.x);

	if (rotation < -PI)
	{
		rotation += PI * 2;
	}
	else if (rotation > PI)
	{
		rotation -= PI * 2;
	}

	mySprite->SetRotation(rotation);
}

void Actor::GoToPosition(const CommonUtilities::Vector::Vector2<float>& aPosition)
{
	myGoToPosition = aPosition;
	myIsFramme = false;
}

bool Actor::GetIsFramme()
{
	return myIsFramme;
}

void Actor::GoToBox(Box* aBox)
{
	if (myTargetBox != nullptr)
	{
		myTargetBox->SetWinterIsComing(false);
	}

	myIsFramme = false;
	myTargetBox = aBox;
	myGoToPosition = myTargetBox->GetPosition();
	myTargetBox->SetWinterIsComing(true);
}