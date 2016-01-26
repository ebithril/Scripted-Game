#pragma once

#include "Macros.h"
#include <string>
#include <assert.h>
#include <fstream>
#include <sstream>

#define DL_ASSERT(string) DL_Debug::Debug::GetInstance()->AssertMessage(__FILE__, __LINE__, __FUNCTION__, L#string);

#define DL_ASSERT_CONDITION(condition, string) DL_Debug::Debug::GetInstance()->AssertMessage(condition, __FILE__, __LINE__, __FUNCTION__, L#string);

#define DL_ASSERT_EXPRESSION(condition) DL_Debug::Debug::GetInstance()->AssertMessage((condition), _CRT_WIDE(#condition), __FILE__, __LINE__, __FUNCTION__);

#define DL_PRINT(string)  DL_Debug::Debug::GetInstance()->PrintMessage(string);

#define DL_DEBUG( ... )  DL_Debug::Debug::GetInstance()->DebugMessage(__LINE__,__FUNCTION__,__VA_ARGS__);

namespace DL_Debug
{
	class Debug
	{
	public:
		static bool Create(std::string aFile = "DebugLogger.txt");
		static bool Destroy();
		static Debug* GetInstance();
		void AssertMessage(const char *aFileName, int aLine, const char *aFunctionName, const wchar_t *aString);
		void AssertMessage(bool aCondition, const char *aFileName, int aLine, const char *aFunctionName, const wchar_t *aString);
		void AssertMessage(bool aCondition, const wchar_t *aString, const char *aFileName, int aLine, const char *aFunctionName);
		void PrintMessage(const char *aString);
		void DebugMessage(const int aLine, const char *aFileName, const char *aFormattedString, ...);
	private:
		Debug();
		~Debug();
		static Debug* ourInstance;
		std::wofstream myDebugFile;
	};
}