#include "stdafx.h"
#include "ExposedFunctions.h"

#include "Actor.h"
#include "PollingStation.h"

#include "../Script/LuaStateHelper.h"
#include "../CommonUtilities/Vector2.h"

#include "../CommonUtilities/InputWrapper.h"

#include "SpriteContainer.h"

#include <tga2d/sprite/sprite.h>

#include "Camera.h"

int GoToPosition(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "GoToPosition");

	state.CheckAmountOfArguments(3);

	CommonUtilities::Vector::Vector2<float> position;

	state.GetDataAt(position.x, 1);
	state.GetDataAt(position.y, 2);

	int gameObjectID;
	state.GetDataAt(gameObjectID, 3);

	PollingStation::GetInstance()->GetActorByID(gameObjectID)->GoToPosition(position);

	return 0;
}

int MoveToRandomFreeBox(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "MoveToRandomFreeBox");

	state.CheckAmountOfArguments(1);
	int gameObjectId;
	state.GetDataAt(gameObjectId, 1);

	PollingStation::GetInstance()->GetActorByID(gameObjectId)->GoToBox(PollingStation::GetInstance()->GetRandomFreeBox());

	return 0;
}

int CreateSprite(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "CreateSprite");

	std::string spritePath;
	state.GetDataAt(spritePath, 1);

	DX2D::CSprite* sprite = SpriteContainer::GetInstance()->CreateSprite(spritePath);
	
	state.PushData(reinterpret_cast<void*>(sprite));

	return 1;
}

int SetSpriteRotation(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "SetSpriteRotation");

	DX2D::CSprite* spritePtr = nullptr;

	state.GetDataAt(reinterpret_cast<void**>(&spritePtr), 1);

	float rotation;

	state.GetDataAt(rotation, 2);

	spritePtr->SetRotation(rotation);

	return 0;
}

int SetSpritePosition(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "SetSpritePosition");

	DX2D::CSprite* spritePtr = nullptr;

	state.GetDataAt(reinterpret_cast<void**>(&spritePtr), 1);

	float x;
	float y;

	state.GetDataAt(x, 2);
	state.GetDataAt(y, 3);

	spritePtr->SetPosition({ x, y });

	return 0;
}

int SetSpriteShouldRender(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "SetSpriteShouldRender");
	
	DX2D::CSprite* spritePtr = nullptr;

	state.GetDataAt(reinterpret_cast<void**>(&spritePtr), 1);

	bool shouldRender;

	state.GetDataAt(shouldRender, 2);

	spritePtr->SetShouldRender(shouldRender);

	return 0;
}

int DeleteSprite(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "DeleteSprite");

	DX2D::CSprite* spritePtr = nullptr;

	state.GetDataAt(reinterpret_cast<void**>(&spritePtr), 1);

	SpriteContainer::GetInstance()->DeleteSprite(spritePtr);

	return 0;
}

int GetDeltaTime(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "GetDeltaTime");

	state.PushData(PollingStation::GetInstance()->GetDeltaTime());

	return 1;
}

int GetShootCommand(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "GetShootCommand");

	state.PushData(CU::InputWrapper::GetInstance()->KeyDown(eKeyboardKeys::KEY_X));

	return 1;
}

int GetThrustCommand(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "GetThrustCommand");

	state.PushData(CU::InputWrapper::GetInstance()->KeyDown(eKeyboardKeys::KEY_UPARROW));

	return 1;
}

int GetTurnLeftCommand(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "GetTurnLeftCommand");

	state.PushData(CU::InputWrapper::GetInstance()->KeyDown(eKeyboardKeys::KEY_LEFTARROW));

	return 1;
}

int GetTurnRightCommand(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "GetTurnRightCommand");

	state.PushData(CU::InputWrapper::GetInstance()->KeyDown(eKeyboardKeys::KEY_RIGHTARROW));

	return 1;
}

int SetCameraPosition(lua_State* aState)
{
	Script::LuaStateHelper state(aState, "SetCameraPosition");

	float x;
	float y;

	state.GetDataAt(x, 1);
	state.GetDataAt(y, 2);

	Camera::GetInstance()->SetPosition({ x, y });

	return 0;
}