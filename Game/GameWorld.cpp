#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/sprite/sprite.h>
#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite_batch.h>
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/text/text.h>
#include <tga2d/primitives/custom_shape.h>
#include <tga2d/math/color.h>

#include "Macros.h"
#include "ChargeController.h"
#include "FleeController.h"
#include "BlendedBehaviorController.h"
#include "FormationController.h"
#include "PollingStation.h"

#include "../Script/LuaStateHelper.h"

#include "ExposedFunctions.h"

#include "../Script/LuaArguments.h"

#include "../Script/LuaBaseScript.h"

#include "../Script/LuaState.h"

#include "SpriteContainer.h"

#include <time.h>

int GetObjectPosition(lua_State* aState)
{
	Script::LuaStateHelper stateHelper(aState, "GetObjectPosition");

	stateHelper.CheckAmountOfArguments(1);

	int gameObjectID;
	stateHelper.GetDataAt(gameObjectID, 1);

	CommonUtilities::Containers::GrowingArray<Actor*>& actors = PollingStation::GetInstance()->GetActors();

	for (Actor* actor : actors)
	{
		if (actor->GetID() == gameObjectID)
		{
			CommonUtilities::Vector::Vector2<float> position = actor->GetPosition();

			stateHelper.PushData(position.x);
			stateHelper.PushData(position.y);

			return 2;
		}
	}

	stateHelper.PushData(-1.f);
	stateHelper.PushData(-1.f);

	return 2;
}

int GetObjectHealth(lua_State* aState)
{
	Script::LuaStateHelper stateHelper(aState, "GetObjectPosition");

	stateHelper.CheckAmountOfArguments(1);

	int gameObjectID;
	stateHelper.GetDataAt(gameObjectID, 1);

	CommonUtilities::Containers::GrowingArray<Actor*>& actors = PollingStation::GetInstance()->GetActors();

	for (Actor* actor : actors)
	{
		if (actor->GetID() == gameObjectID)
		{
			stateHelper.PushData(actor->GetHealth());

			return 1;
		}
	}

	return 0;
}

int GetGameObjects(lua_State* aState)
{
	Script::LuaStateHelper stateHelper(aState, "GetObjectPosition");

	stateHelper.CheckAmountOfArguments(0);

	CommonUtilities::Containers::GrowingArray<Actor*>& actors = PollingStation::GetInstance()->GetActors();

	for (int i = 0; i < actors.Size(); i++)
	{
		stateHelper.PushData(i);
	}

	return actors.Size();
}

using namespace DX2D;
CGameWorld::CGameWorld()
{
	srand(time(0));
	myCallBacks.Init(2);
}

CGameWorld::~CGameWorld()
{
	myInputWrapper->Release();
}

void CGameWorld::Init()
{
	myMouseBoxPointer = nullptr;

	myInstance = Script::CreateLuaInterface();

	myBoxes.Init(10);

	myInstance->RegisterFunction("GoToPosition", GoToPosition, "Description");
	myInstance->RegisterFunction("MoveToRandomFreeBox", MoveToRandomFreeBox, "Monkey");

	myInstance->RegisterFunction("CreateSprite", CreateSprite, "Monkey");
	myInstance->RegisterFunction("SetSpriteRotation", SetSpriteRotation, "Monkey");
	myInstance->RegisterFunction("SetSpritePosition", SetSpritePosition, "Monkey");
	myInstance->RegisterFunction("SetSpriteShouldRender", SetSpriteShouldRender, "Monkey");
	myInstance->RegisterFunction("DeleteSprite", DeleteSprite, "Monkey");
	myInstance->RegisterFunction("GetDeltaTime", GetDeltaTime, "Monkey");
	myInstance->RegisterFunction("GetShootCommand", GetShootCommand, "Monkey");
	myInstance->RegisterFunction("GetThrustCommand", GetThrustCommand, "Monkey");
	myInstance->RegisterFunction("GetTurnLeftCommand", GetTurnLeftCommand, "Monkey");
	myInstance->RegisterFunction("GetTurnRightCommand", GetTurnRightCommand, "Monkey");
	myInstance->RegisterFunction("SetCameraPosition", SetCameraPosition, "Monkey");


	myInstance->RegisterAddCallBackFunction("ReachedPosition", [this](std::string aFunctionName, std::shared_ptr<Script::LuaBaseScript> aScript, long long aID) {AddCallback(aFunctionName, aScript, aID); });

	myCursor = new DX2D::CSprite("Sprites/cursor.dds");

	myState = myInstance->CreateLuaState();

	myState->UseFile("Script/Scripts/main.lua");

	myState->CallFunction("Init", 0, 0, LuaArguments());

	myInputWrapper = CU::InputWrapper::GetInstance();
	myInputWrapper->Init(*DX2D::CEngine::GetInstance()->GetHWND(), DX2D::CEngine::GetInstance()->GetHInstance());


	for (int i = 0; i < NUMBER_OF_OBSTACLES; i++)
	{
		myObstacles[i] = new Obstacle;
		myObstacles[i]->SetPosition({ RANDOM_FLOAT(0.9f, 0.1f), RANDOM_FLOAT(0.9f, 0.1f) });

		PollingStation::GetInstance()->AddObstacle(myObstacles[i]);
	}

	for (int i = 0; i < 8; ++i)
	{
		Box box;
		if (i < 4)
		{
			box.SetPosition({ 0.1f + (0.2f * i), 0.3f });
		}
		else
		{
			box.SetPosition({ 0.1f + (0.2f * i) - 0.8f, 0.7f });
		}

		myBoxes.Add(box);
		PollingStation::GetInstance()->AddBox(&myBoxes.GetLast());
	} 

	myActors[0] = new Actor();
	myActors[1] = new Actor();

	myTimerManager.Update();
}

void CGameWorld::Update(float /*aTimeDelta*/)
{
	//myInstance->Update();

	myTimerManager.Update();
	float deltaTime = myTimerManager.GetMasterTimer().GetDeltaTime().GetSeconds();

	PollingStation::GetInstance()->SetDeltaTime(deltaTime);

	myInputWrapper->PollInput();

	//if (deltaTime > 1.f / 30.f)
	//{
	//	deltaTime = 1.f / 30.f;
	//}


	//myInputWrapper.PollInput();
	//
	//float mousePosX = (myInputWrapper.GetCurrentMouseX() / 1920.f) + 0.5f;
	//float mousePosY = (myInputWrapper.GetCurrentMouseY() / 1080.f) + 0.5f;

	//myFormation.Update(deltaTime);

	///*for (int i = 0; i < NUMBER_OF_OBSTACLES; i++)
	//{
	//myObstacles[i]->Render();
	//}*/

	//if (myMouseBoxPointer != nullptr)
	//{
	//	myMouseBoxPointer->SetWinterIsComing(false);
	//}

	//myMouseBoxPointer = nullptr;

	//for (Box& box : myBoxes)
	//{
	//	if (box.TestCollision({ mousePosX, mousePosY }) == true)
	//	{
	//		box.SetWinterIsComing(true);
	//		myMouseBoxPointer = &box;
	//	}
	//}

	//for (int i = 0; i < myBoxes.Size(); ++i)
	//{
	//	myBoxes[i].Render();
	//}

	//for (int i = 0; i < NUMBER_OF_ACTORS; i++)
	//{
	//	myActors[i]->Update(deltaTime);
	//	myActors[i]->Render();

	//	if (myActors[i]->GetIsFramme() == true)
	//	{
	//		SendCallbacks(myActors[i]->GetID());
	//	}
	//}


	//myCursor->SetPosition(DX2D::Vector2f(mousePosX, mousePosY));

	//if (myInputWrapper.MouseButtonDown(eMouseKeys::LEFT))
	//{
	//	myFormation.SetTargetPosition(CommonUtilities::Vector::Vector2<float>(mousePosX, mousePosY));
	//}

	//myCursor->Render();

	
	SpriteContainer::GetInstance()->SetShouldRender(false);
		
	myInstance->Update();

	myState->CallFunction("Update", 0, 0, LuaArguments());

	SpriteContainer::GetInstance()->RenderAll();

	CEngine::GetInstance()->GetLightManager().SetAmbience(1.0f);
}

void CGameWorld::AddCallback(std::string aFunctionName, std::shared_ptr<Script::LuaBaseScript> aScript, long long aID)
{
	CallbackInfo info;
	info.myFunctionName = aFunctionName;
	info.myID = aID;
	info.myScript = aScript;

	myCallBacks.Add(info);
}

void CGameWorld::SendCallbacks(int aID)
{
	for (CallbackInfo& info : myCallBacks)
	{
		info.myScript->CallFunction(info.myFunctionName.c_str(), 2, 0, LuaArguments(std::to_string(info.myID).c_str(), aID));
	}
}