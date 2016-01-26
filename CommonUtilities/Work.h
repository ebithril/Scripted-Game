#pragma once

#include <functional>
#include <string>

class Work
{
public:
	Work();
	Work(const std::function<void()>& aFunction, const std::string& aString);
	~Work();

	inline void DoWork();
private:
	std::function<void()> myFunction;
	std::string myString;
};

void Work::DoWork()
{
	if (myString != "")
	{
		myFunction();
	}
}