#include "stdafx.h"
#include "Timer.h"

namespace CommonUtilities
{
	namespace Timers
	{
		Timer::Timer()
		{
			myIsPaused = false;
		}

		Timer::~Timer()
		{
		}

		void Timer::Stop()
		{
			myIsPaused = true;
		}

		void Timer::Start()
		{
			myIsPaused = false;
		}

		void Timer::AddTime(long double someTime)
		{
			myDelta.Reset();
			myDelta.AddTime(someTime);

			myTime.AddTime(someTime);
		}

		void Timer::Reset()
		{
			myTime.Reset();
		}
	}
}