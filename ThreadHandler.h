#pragma once
#include "ThreadData.h"

using namespace std;

class ThreadHandler
{
public:

	vector<ThreadData> *divideDataForThreads(int numberOfThreads, ThreadData *mainTable);
	vector<HANDLE> *createThreads(int numberOfThreads, LPTHREAD_START_ROUTINE nameOfTheFunction, ThreadData *data);
};

