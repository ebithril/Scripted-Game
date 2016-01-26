#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle()
{
	mySprite = new DX2D::CSprite("Sprites\\Obstacle.dds");
	mySprite->SetPivot({ 0.5f, 0.5f });
}


Obstacle::~Obstacle()
{
}

const CommonUtilities::Vector::Vector2<float>& Obstacle::GetPosition() const
{
	return myPosition;
}

void Obstacle::SetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition)
{
	myPosition = aPosition;
	mySprite->SetPosition(DX2D::Vector2f(myPosition.x, myPosition.y));
}

void Obstacle::Render()
{
	mySprite->Render();
}