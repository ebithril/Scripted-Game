#pragma once
#include <vector>

#include "..\CommonUtilities\InputWrapper.h"
#include "..\CommonUtilities\Vector2.h"
#include "..\CommonUtilities\StaticArray.h"
#include "..\CommonUtilities\TimerManager.h"
#include "..\CommonUtilities\GrowingArray.h"

#include "Actor.h"
#include "Box.h"
#include "Formation.h"
#include "Obstacle.h"

#include "../Script/LuaInterface.h"

namespace Script
{
	class LuaBaseScript;
}

#define NUMBER_OF_ACTORS 2
#define NUMBER_OF_OBSTACLES 20

namespace DX2D
{
	class CSprite;
	class CSpriteBatch;
	class CText;
	class CCustomShape;
}

struct CallbackInfo
{
	std::string myFunctionName;
	std::shared_ptr<Script::LuaBaseScript> myScript;
	long long myID;
};

class CGameWorld
{
public:
	CGameWorld();
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta);
private:
	void AddCallback(std::string aFunctionName, std::shared_ptr<Script::LuaBaseScript> aScript, long long aID);
	void SendCallbacks(int aID);

	DX2D::CSprite* myCursor;

	CommonUtilities::Containers::StaticArray<Actor*, NUMBER_OF_ACTORS> myActors;
	CommonUtilities::Containers::StaticArray<Obstacle*, NUMBER_OF_OBSTACLES> myObstacles;

	Formation myFormation;

	CommonUtilities::InputWrapper* myInputWrapper;
	CommonUtilities::Timers::TimerManager myTimerManager;

	CommonUtilities::Containers::GrowingArray<CallbackInfo> myCallBacks;
	CommonUtilities::Containers::GrowingArray<Box> myBoxes;

	Box* myMouseBoxPointer;

	Script::LuaInterface* myInstance;

	std::shared_ptr<Script::LuaState> myState;
};