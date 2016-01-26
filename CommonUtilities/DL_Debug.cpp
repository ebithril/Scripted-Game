#include "stdafx.h"
#include "DL_Debug.h"
#include "DL_Assert.h"
#include "DL_StackWalker.h"
#include <stdio.h>
#include <stdarg.h>
#include <sstream>
#include <time.h>

DL_Debug::Debug *DL_Debug::Debug::ourInstance = nullptr;

bool DL_Debug::Debug::Create(std::string aFile)
{
	assert(ourInstance == nullptr && "Debugobject already created");

	ourInstance = new Debug();

	time_t now = time(0);
	struct tm tstruct;
	char buff[30];
	localtime_s(&tstruct, &now);

	strftime(buff, sizeof(buff), "%Y-%m-%d_%H_%M_%S", &tstruct);
	CreateDirectory(L"log", NULL);
	std::stringstream ss;
	ss << "log\\" << buff << "_" << aFile;

	if (ourInstance == nullptr)
	{
		return false;
	}

	ourInstance->myDebugFile.open(ss.str().c_str());

	return true;
}

bool DL_Debug::Debug::Destroy()
{
	ourInstance->myDebugFile.close();

	SAFE_DELETE(ourInstance);
	return true;
}

DL_Debug::Debug* DL_Debug::Debug::GetInstance()
{
	return ourInstance;
}

DL_Debug::Debug::Debug()
{
}

DL_Debug::Debug::~Debug()
{
}

void DL_Debug::Debug::AssertMessage(const char *aFileName, int aLine, const char *aFunctionName, const wchar_t *aString)
{
	myDebugFile << "\nFilename: " << aFileName << "\n"
		<< "Line: " << aLine << "\n"
		<< "Function: " << aFunctionName << "\n"
		<< "Message: " << aString << "\n";
	
	StackWalker st;
	st.ShowCallstack();

	std::wstringstream ss;
	ss << aFileName;

	myDebugFile.flush();
	_wassert(aString, ss.str().c_str(), aLine);
}

void DL_Debug::Debug::PrintMessage(const char *aString)
{
	myDebugFile << aString;
}

void DL_Debug::Debug::DebugMessage(const int aLine, const char *aFileName, const char *aFormattedString, ...)
{
	char buffer[1024];

	va_list args;
	va_start(args, aFormattedString);
	vsprintf_s(buffer, aFormattedString, args);
	va_end(args);

	myDebugFile << "\nFilename: " << aFileName << "\n"
		<< "Line: " << aLine << "\n";

	myDebugFile << buffer;
}

void DL_Debug::Debug::AssertMessage(bool aCondition, const char *aFileName, int aLine, const char *aFunctionName, const wchar_t *aString)
{
	if (aCondition == false)
	{
		AssertMessage(aFileName, aLine, aFunctionName, aString);
	}
}

void DL_Debug::Debug::AssertMessage(bool aCondition, const wchar_t *aString, const char *aFileName, int aLine, const char *aFunctionName)
{
	if (aCondition == false)
	{
		myDebugFile << "\nFilename: " << aFileName << "\n"
			<< "Line: " << aLine << "\n"
			<< "Function: " << aFunctionName << "\n"
			<< "Message: " << aString << "\n";

		StackWalker st;
		st.ShowCallstack();

		std::wstringstream ss;
		ss << aFileName;

		myDebugFile.flush();
		_wassert(aString, ss.str().c_str(), aLine);
	}
}