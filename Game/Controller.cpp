#include "stdafx.h"
#include "Controller.h"

#include "Actor.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::SetParent(Actor* aParent)
{
	myParent = aParent;
}

void Controller::SetTargetPosition(const CommonUtilities::Vector::Vector2<float>& aVector)
{
}

void Controller::Init()
{
}

const CommonUtilities::Vector::Vector2<float>& Controller::GetPosition() const
{
	return myParent->GetPosition();
}
