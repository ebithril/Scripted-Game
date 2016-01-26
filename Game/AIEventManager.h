#pragma once

#include "Event.h"
#include "..\CommonUtilities\GrowingArray.h"

class Controller;

class AIEventManager
{
public:
	static AIEventManager* GetInstance();
private:
	AIEventManager();
	~AIEventManager();

	static AIEventManager* ourInstance;

	CommonUtilities::Containers::GrowingArray<Controller*> myListeners;
};