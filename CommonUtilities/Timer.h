#pragma once

#include "CUTime.h"

namespace CommonUtilities
{
	namespace Timers
	{
		class Timer
		{
		public:
			Timer();
			~Timer();
			inline const Time& GetTime() const;
			inline const bool GetIsPaused() const;
			void Stop();
			void Start();
			void AddTime(long double someTime);
			void Reset();
			inline const Time& GetDeltaTime() const;
		private:
			Time myTime;
			Time myDelta;
			bool myIsPaused;
		};
	}
}


namespace CommonUtilities
{
	namespace Timers
	{
		inline const Time& Timer::GetTime() const
		{
			return myTime;
		}

		inline const bool Timer::GetIsPaused() const
		{
			return myIsPaused;
		}

		inline const Time& Timer::GetDeltaTime() const
		{
			return myDelta;
		}
	}
}