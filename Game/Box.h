#pragma once
#include "..\CommonUtilities\Vector2.h"

namespace DX2D
{
	class CSprite;
}

class Box
{
public:
	Box();
	~Box();


	void SetPosition(const CommonUtilities::Vector::Vector2<float>& aPosition);
	const CommonUtilities::Vector::Vector2<float>& GetPosition() const;
	bool TestCollision(const CommonUtilities::Vector::Vector2<float>& aPosition);

	void Render();

	void SetWinterIsComing(bool aWinterIsComing);
	bool GetWinterIsComing() const;
private:
	CommonUtilities::Vector::Vector2<float> myPosition;
	CommonUtilities::Vector::Vector2<float> myDimensions;
	bool myWinterIsComing; 
	DX2D::CSprite* mySprite;
};