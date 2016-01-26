#pragma once

#include <Windows.h>
#include "Timer.h"
#include "GrowingArray.h"

namespace CommonUtilities
{
	namespace Timers
	{
		class TimerManager
		{
		public:
			TimerManager();
			~TimerManager();
			const Timer& GetTimer(const unsigned int aID) const;
			unsigned int CreateTimer();
			void Update();
			const Timer& GetMasterTimer() const;
			void ResetTimer(const unsigned int aID);
			void StopTimer(const unsigned int aID);
			void StartTimer(const unsigned int aID);
		private:
			Timer myMasterTimer;
			Containers::GrowingArray<Timer, unsigned int> myTimers;
			LARGE_INTEGER myLastFrame;
			LARGE_INTEGER myClockFrequency;
		};
	}
}