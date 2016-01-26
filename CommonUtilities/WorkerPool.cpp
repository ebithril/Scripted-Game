#include "stdafx.h"
#include "WorkerPool.h"
#include <thread>

WorkerPool::WorkerPool()
{
	myIsRunning = true;

	myWorkers.Init(std::thread::hardware_concurrency());

	for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++)
	{
		myWorkers.Add(Worker());
		myWorkers[i].Init();
	}

	myThread = new std::thread([&] { Run(); });
}

WorkerPool::~WorkerPool()
{
	if (myIsRunning == true)
	{
		Stop();
	}

	myThread->join();

	delete myThread;
}

void WorkerPool::Run()
{
	std::unique_lock<std::mutex> lock(myMutex);

	while (myIsRunning == true)
	{
		if (myWork.GetSize() == 0)
		{
			myWaitingVariable.wait(lock);
		}

		while (myWork.GetSize() > 0 && myIsRunning == true)
		{
			for (int i = 0; i < myWorkers.Size(); i++)
			{
				if (myWorkers[i].GetIsDone() == true)
				{
					myWorkers[i].AssignWork(myWork.GetFirst());
					myWork.Pop();
					break;
				}
			}
		}
	}
}