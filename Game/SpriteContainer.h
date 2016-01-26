#pragma once

#include <unordered_map>

#include "../CommonUtilities/GrowingArray.h"

namespace DX2D
{
	class CSpriteBatch;
	class CSprite;
}

class SpriteContainer
{
public:
	static SpriteContainer* GetInstance();

	DX2D::CSprite* CreateSprite(const std::string& aSpritePath);

	void SetShouldRender(bool aShouldrender);

	void RenderAll();

	void DeleteSprite(DX2D::CSprite* aSprite);

private:
	SpriteContainer();
	~SpriteContainer();

	static SpriteContainer* ourInstance;

	bool CheckIfExists(const std::string& aSpritePath);

	std::unordered_map<std::string, DX2D::CSpriteBatch*> mySpriteBatches;
	CommonUtilities::Containers::GrowingArray<DX2D::CSprite*> mySprites;
};