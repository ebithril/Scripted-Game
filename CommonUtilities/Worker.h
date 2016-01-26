#pragma once

#include "Work.h"
#include <atomic>
#include <condition_variable>

namespace std
{
	class thread;
}

class Worker
{
public:
	Worker();
	~Worker();

	const Worker& operator=(const Worker& aWorker);

	void Init();
	void AssignWork(const Work& aWork);
	inline void Stop();

	inline bool GetIsDone();

private:
	void Run();

	Work myWork;
	std::thread* myThread;
	std::mutex myMutex;
	std::condition_variable myWaitingVariable;
	std::atomic<bool> myIsDone;
	std::atomic<bool> myIsRunning;
};

void Worker::Stop()
{
	myIsRunning = false;
	myWaitingVariable.notify_all();
}

bool Worker::GetIsDone()
{
	return myIsDone;
}