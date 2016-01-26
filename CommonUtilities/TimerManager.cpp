#include "stdafx.h"
#include "TimerManager.h"
#include <assert.h>
#include "Macros.h"

namespace CommonUtilities
{
	namespace Timers
	{
		TimerManager::TimerManager() : myTimers(1)
		{
			QueryPerformanceFrequency(&myClockFrequency);
			QueryPerformanceCounter(&myLastFrame);
		}

		TimerManager::~TimerManager()
		{
		}

		const Timer& TimerManager::GetTimer(const unsigned int aID) const
		{
			assert(aID < myTimers.Size() && "ID bigger than number of timers.");

			return myTimers[aID];
		}

		unsigned int TimerManager::CreateTimer()
		{
			myTimers.Add(Timer());

			return myTimers.Size() - 1;
		}

		void TimerManager::Update()
		{
			QueryPerformanceFrequency(&myClockFrequency);

			LARGE_INTEGER newFrame;
			QueryPerformanceCounter(&newFrame);
			long double deltaTime;
			deltaTime = static_cast<long double>(newFrame.QuadPart - myLastFrame.QuadPart) / myClockFrequency.QuadPart;
			myLastFrame = newFrame;

			myMasterTimer.AddTime(deltaTime);

			FOR_EACH_GA(myTimers)
			{
				if (myTimers[i].GetIsPaused() == false)
				{
					myTimers[i].AddTime(deltaTime);
				}
			}
		}

		const Timer& TimerManager::GetMasterTimer() const
		{
			return myMasterTimer;
		}

		void TimerManager::ResetTimer(const unsigned int aID)
		{
			assert(aID < myTimers.Size() && "ID bigger than number of timers.");

			myTimers[aID].Reset();
		}

		void TimerManager::StopTimer(const unsigned int aID)
		{
			assert(aID < myTimers.Size() && "ID bigger than number of timers.");

			myTimers[aID].Stop();
		}

		void TimerManager::StartTimer(const unsigned int aID)
		{
			assert(aID < myTimers.Size() && "ID bigger than number of timers.");

			myTimers[aID].Start();
		}
	}
}