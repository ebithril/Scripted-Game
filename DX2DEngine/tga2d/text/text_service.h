/*
This class handles all texts that will be rendered, don't use this to show text, only use the CText class
*/

#pragma once


#include "math/vector2.h"
#include "math/vector4.h"
#include "text/fontfile.h"
#include "math/color.h"
#include "arrays/simple_pointer_array.h"
#include <string>
#include <map>
#include <vector>


namespace DX2D
{
	struct TextVertexNew
	{
		TextVertexNew(){ myPosition.Set(0, 0); myTexCoord.Set(0, 0); }
		TextVertexNew(Vector2f aPos, Vector2f aTexCoord, Vector4f color = Vector4f(1, 1, 1, 1))
		{
			myPosition = aPos;
			myTexCoord = aTexCoord;
			myColor = color;
		}
		Vector2f myPosition;
		Vector2f myTexCoord;
		Vector4f myColor;
	};

	class CSpriteBatch;
	class CTexture;
	class CSprite;
	class CTextService
	{
		struct SText
		{
			std::string myText;
			std::string myName;
			Vector2f myPosition;
			float mySize;
			CColor myColor;
		};
	public:
		CTextService();
		~CTextService();

		void Init();
		
		//void Render();

		void Update();

		void InitAndLoad(std::string aFontPathAndName);
		void AddTextToRender(const std::string& aText, const Vector2f& aPosition, CColor aColor, float aSize, const std::string& aName);
		float GetSentenceWidth(const std::string& aText, float aSize, const std::string& aName);
	private:
		void UpdateTextAndDraw(const std::string& aText, const Vector2f& aPosition, CColor aColor, float aSize, const std::string& aName);
		struct STextToRender
		{
			Vector2f mySize;
			Vector2f myUV;
			Vector2f uvScale;
			Vector2f myPosition;
			CColor myColor;
		};

		void BuildText(const std::string& aText, const Vector2f& aPosition, CColor aColor, float aSize, const std::string& aName, std::vector<STextToRender>& aTextBuffer);
		void InitTexture();
		
		float minS;
		float minT;
		float maxS;
		float maxT;
		int currentFontChar;

		SSimplePointerArray<SText*> myTextsToRender;
		int myCurrentSprite;
		std::vector<CSprite*> mySprites;
		bool myIsLoaded;
		struct SFontData
		{
			std::vector<fontChar> myFontChars;
			CSpriteBatch* myBatch;
			CTexture* myTexture;
			std::vector<STextToRender> myTextBuffer;
		};

		std::map<std::string, SFontData*> myFontDatas;
		unsigned int myTextsToDraw;
	};
}