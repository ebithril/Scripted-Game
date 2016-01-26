#pragma once

struct lua_State;

int GoToPosition(lua_State* aState);

int MoveToRandomFreeBox(lua_State* aState);

int CreateSprite(lua_State* aState);

int SetSpriteRotation(lua_State* aState);

int SetSpritePosition(lua_State* aState);

int SetSpriteShouldRender(lua_State* aState);

int DeleteSprite(lua_State* aState);

int GetDeltaTime(lua_State* aState);

int GetShootCommand(lua_State* aState);

int GetThrustCommand(lua_State* aState);

int GetTurnLeftCommand(lua_State* aState);

int GetTurnRightCommand(lua_State* aState);

int SetCameraPosition(lua_State* aState);