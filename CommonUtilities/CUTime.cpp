#include "stdafx.h"
#include "CUTime.h"

namespace CommonUtilities
{
	namespace Timers
	{
		Time::Time()
		{
			myTime = 0;
		}

		Time::~Time()
		{
		}

		void Time::AddTime(long double timePassed)
		{
			myTime += timePassed;
		}

		void Time::Reset()
		{
			myTime = 0;
		}
	}
}