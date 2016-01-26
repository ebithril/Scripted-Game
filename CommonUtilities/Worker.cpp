#include "stdafx.h"
#include "Worker.h"

#include <thread>

Worker::Worker()
{
	myIsDone = true;
	myIsRunning = true;
	myThread = nullptr;
}

Worker::~Worker()
{
	if (myThread != nullptr)
	{
		myThread->join();
	}

	delete myThread;
}

const Worker& Worker::operator=(const Worker& aWorker)
{
	myIsDone = true;
	myIsRunning = true;
	myThread = nullptr;

	return *this;
}

void Worker::Init()
{
	myThread = new std::thread([&] { Run(); });
}

void Worker::AssignWork(const Work& aWork)
{
	myWork = aWork;
	myWaitingVariable.notify_all();
}

void Worker::Run()
{
	std::unique_lock<std::mutex> lock(myMutex);
	while (myIsRunning == true)
	{
		if (myIsDone == true && myIsRunning == true)
		{
			myWaitingVariable.wait(lock);
		}

		if (myIsDone == false && myIsRunning == true)
		{
			myWork.DoWork();
		}
	}
}