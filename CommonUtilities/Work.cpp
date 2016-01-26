#include "stdafx.h"
#include "Work.h"

Work::Work()
{
	myString = "";
}

Work::Work(const std::function<void()>& aFunction, const std::string& aString)
{
	myFunction = aFunction;
	myString = aString;
}

Work::~Work()
{
}