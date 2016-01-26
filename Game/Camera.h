#pragma once

#include "../CommonUtilities/Vector2.h"

namespace DX2D
{
	class CSprite;
}

class Camera
{
public:
	static Camera* GetInstance();

	void SetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition);
	void SetRenderPosition(DX2D::CSprite* aSprite);

private:
	Camera();
	~Camera();

	static Camera* ourInstance;

	CommonUtilities::Vector::Vector2<float> myPosition;
};