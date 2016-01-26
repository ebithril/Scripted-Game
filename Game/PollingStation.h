#pragma once

#include "..\CommonUtilities\GrowingArray.h"

class Actor;
class Obstacle;
class Box;

class PollingStation
{
public:
	static PollingStation* GetInstance();

	void AddActor(Actor* aActor);
	CommonUtilities::Containers::GrowingArray<Actor*>& GetActors();

	Actor* GetActorByID(int aID);

	void AddObstacle(Obstacle* aObstacle);
	CommonUtilities::Containers::GrowingArray<Obstacle*>& GetObstacles();

	void AddBox(Box* aBox);
	CommonUtilities::Containers::GrowingArray<Box*>& GetBoxes();
	Box* GetRandomFreeBox();

	float GetDeltaTime();
	void SetDeltaTime(float aDeltaTime);
private:
	PollingStation();
	~PollingStation();

	static PollingStation* ourInstance;

	float myDeltaTime;

	CommonUtilities::Containers::GrowingArray<Actor*> myActors;
	CommonUtilities::Containers::GrowingArray<Obstacle*> myObstacles;
	CommonUtilities::Containers::GrowingArray<Box*> myBoxes;
};