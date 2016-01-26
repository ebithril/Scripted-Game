#include "stdafx.h"
#include "PollingStation.h"
#include "Box.h"
#include "Actor.h"

PollingStation* PollingStation::ourInstance = nullptr;

PollingStation::PollingStation()
{
	myActors.Init(4);
	myObstacles.Init(4);
	myBoxes.Init(10);
}

PollingStation::~PollingStation()
{
}

PollingStation* PollingStation::GetInstance()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new PollingStation();
	}

	return ourInstance;
}

void PollingStation::AddActor(Actor* aActor)
{
	myActors.Add(aActor);
}

CommonUtilities::Containers::GrowingArray<Actor*>& PollingStation::GetActors()
{
	return myActors;
}

Actor* PollingStation::GetActorByID(int aID)
{
	for (Actor* actor : myActors)
	{
		if (actor->GetID() == aID)
		{
			return actor;
		}
	}

	return nullptr;
}

void PollingStation::AddObstacle(Obstacle* aObstacle)
{
	myObstacles.Add(aObstacle);
}

CommonUtilities::Containers::GrowingArray<Obstacle*>& PollingStation::GetObstacles()
{
	return myObstacles;
}

void PollingStation::AddBox(Box* aBox)
{
	myBoxes.Add(aBox);
}

CommonUtilities::Containers::GrowingArray<Box*>& PollingStation::GetBoxes()
{
	return myBoxes;
}

Box* PollingStation::GetRandomFreeBox()
{
	int randomBoxIndex = rand() % myBoxes.Size();
	while (true)
	{
		if (myBoxes[randomBoxIndex]->GetWinterIsComing() == false)
		{
			return myBoxes[randomBoxIndex];
		}
		randomBoxIndex = rand() % myBoxes.Size();
	}
}

float PollingStation::GetDeltaTime()
{
	return myDeltaTime;
}

void PollingStation::SetDeltaTime(float aDeltaTime)
{
	myDeltaTime = aDeltaTime;
}
