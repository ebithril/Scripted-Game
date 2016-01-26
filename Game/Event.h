#pragma once

#include "..\CommonUtilities\Vector2.h"

enum class eEventType
{
	eAI_MOVE_W,
	eAI_MOVE_S,
	eAI_MOVE_A,
	eAI_MOVE_D,
	eAI_STOP_W,
	eAI_STOP_S,
	eAI_STOP_A,
	eAI_STOP_D,
};

struct Event
{
	eEventType myType;
	float myRadius;
	CommonUtilities::Vector::Vector2<float> myPosition;
};