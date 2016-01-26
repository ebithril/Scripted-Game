#pragma once

#include "..\CommonUtilities\Vector2.h"
#include <tga2d\sprite\sprite.h>

class Obstacle
{
public:
	Obstacle();
	~Obstacle();

	const CommonUtilities::Vector::Vector2<float>& GetPosition() const;
	void SetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition);

	void Render();

private:
	CommonUtilities::Vector::Vector2<float> myPosition;
	DX2D::CSprite* mySprite;
};