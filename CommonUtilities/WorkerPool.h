#pragma once

#include "Worker.h"
#include "Work.h"
#include "Queue.h"
#include "GrowingArray.h"
#include <atomic>
#include <condition_variable>

namespace std
{
	class thread;
}

class WorkerPool
{
public:
	WorkerPool();
	~WorkerPool();

	inline void AddWork(const Work& aWork);

	inline void Stop();
private:
	void Run();

	std::thread* myThread;
	CommonUtilities::Containers::Queue<Work> myWork;
	CommonUtilities::Containers::GrowingArray<Worker> myWorkers;
	std::atomic<bool> myIsRunning;
	std::condition_variable myWaitingVariable;
	std::mutex myMutex;
};

void WorkerPool::AddWork(const Work& aWork)
{
	myWork.Add(aWork);
	myWaitingVariable.notify_all();
}

void WorkerPool::Stop()
{
	myIsRunning = false;

	for (int i = 0; i < myWorkers.Size(); i++)
	{
		myWorkers[i].Stop();
	}

	myWaitingVariable.notify_all();
}