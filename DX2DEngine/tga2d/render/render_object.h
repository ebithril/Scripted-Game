#pragma once
#include <vector>
#include "tga2d/math/Vector4.h"
#include "tga2d/math/Vector2.h"
#include "tga2d/math/Color.h"

namespace DX2D
{
	class CDirectEngine;
	class CRenderObject
	{
		friend class CDirectEngine;
	public:
		CRenderObject();
		virtual ~CRenderObject(){}
		bool myIsScreenSpace;
	protected:
		virtual void Draw(CDirectEngine* aRenderer) = 0;
	};

	class CRenderObjectSprite : public CRenderObject
	{
	public:
		CRenderObjectSprite();
		~CRenderObjectSprite(){}
		void Draw(CDirectEngine* aRenderer) override;
		Vector2f myPosition;
		CColor myColor;
		Vector2f myPivot;
		float myRotation;
		Vector2f mySize;
		Vector2f mySizeMultiplier;
		Vector2<unsigned int> myImageSize;
		Vector2f myUV;
		Vector2f myUVScale;
	};

	class CRenderObjectLine : public CRenderObject
	{
	public:
		CRenderObjectLine();
		virtual ~CRenderObjectLine(){}
		void Draw(CDirectEngine* aRenderer) override;

		Vector4f myColor;
		Vector2f myFromPosition;
		Vector2f myToPosition;
	};


	struct SCustomPoint
	{
		SCustomPoint()
		{
			myPosition.Set(0, 0);
			myColor.Set(1, 1, 1, 1);
			myUV.Set(0.5f, 0.5f);
		}
		Vector2f myPosition;
		CColor myColor;
		Vector2f myUV;
		int myIndex;
	};
	class CRenderObjectCustom : public CRenderObject
	{
	public:
		CRenderObjectCustom();
		~CRenderObjectCustom(){}
		void Draw(CDirectEngine* aRenderer) override;


		Vector2f myPosition;
		std::vector<SCustomPoint> myPoints;
	};
}