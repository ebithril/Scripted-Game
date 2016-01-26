#include "stdafx.h"
#include "AIEventManager.h"

#include "Actor.h"
#include "Controller.h"
#include "PollingStation.h"

AIEventManager* AIEventManager::ourInstance = nullptr;

AIEventManager::AIEventManager()
{
}

AIEventManager::~AIEventManager()
{
}

AIEventManager* AIEventManager::GetInstance()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new AIEventManager();
	}

	return ourInstance;
}