#include "stdafx.h"
#include "SpriteContainer.h"

#include "Camera.h"

#include <tga2d/sprite/sprite.h>
#include <tga2d/sprite/sprite_batch.h>

SpriteContainer* SpriteContainer::ourInstance = nullptr;

SpriteContainer::SpriteContainer()
{
	mySprites.Init(64);
}

SpriteContainer::~SpriteContainer()
{
}

SpriteContainer* SpriteContainer::GetInstance()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new SpriteContainer();
	}
	
	return ourInstance;
}

DX2D::CSprite* SpriteContainer::CreateSprite(const std::string& aSpritePath)
{
	if (CheckIfExists(aSpritePath) == true)
	{
		DX2D::CSprite* sprite = new DX2D::CSprite(nullptr);

		mySpriteBatches[aSpritePath]->AddObject(sprite);

		sprite->SetPivot({ 0.5f, 0.5f });

		mySprites.Add(sprite);

		return sprite;
	}
	else
	{
		mySpriteBatches[aSpritePath] = new DX2D::CSpriteBatch(true);
		mySpriteBatches[aSpritePath]->Init(aSpritePath.c_str());

		DX2D::CSprite* sprite = new DX2D::CSprite(nullptr);

		mySpriteBatches[aSpritePath]->AddObject(sprite);

		sprite->SetPivot({ 0.5f, 0.5f });

		mySprites.Add(sprite);

		return sprite;
	}
}

void SpriteContainer::SetShouldRender(bool aShouldrender)
{
	for (DX2D::CSprite* sprite : mySprites)
	{
		sprite->SetShouldRender(aShouldrender);
	}
}

void SpriteContainer::RenderAll()
{
	for (DX2D::CSprite* sprite : mySprites)
	{
		Camera::GetInstance()->SetRenderPosition(sprite);
	}

	for (auto batch : mySpriteBatches)
	{
		batch.second->Render();
	}
}

void SpriteContainer::DeleteSprite(DX2D::CSprite* aSprite)
{
	for (auto batch : mySpriteBatches)
	{
		batch.second->RemoveObject(aSprite);
	}

	mySprites.DeleteCyclic(aSprite);
}

bool SpriteContainer::CheckIfExists(const std::string& aSpritePath)
{
	return mySpriteBatches.find(aSpritePath) != mySpriteBatches.end();
}