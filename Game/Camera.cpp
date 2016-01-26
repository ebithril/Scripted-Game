#include "stdafx.h"
#include "Camera.h"

#include "HelpFunctions.h"

#include <tga2d/sprite/sprite.h>

Camera* Camera::ourInstance = nullptr;

Camera* Camera::GetInstance()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new Camera();
	}

	return ourInstance;
}

void Camera::SetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition)
{
	myPosition = aPosition;
}

void Camera::SetRenderPosition(DX2D::CSprite* aSprite)
{
	CommonUtilities::Vector::Vector2<float> spritePos = ConvertToCUVector(aSprite->GetPosition());

	spritePos -= myPosition;

	aSprite->SetPosition(ConvertToDXD2DVector(spritePos));
}

Camera::Camera()
{
	myPosition = { 0, 0 };
}

Camera::~Camera()
{
}
