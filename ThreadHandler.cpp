#include "pch.h"
#include "ThreadHandler.h"

vector<ThreadData> *ThreadHandler::divideDataForThreads(int numberOfThreads, ThreadData *mainTable)
{
	int lengthOfTable = mainTable->getNumberOfElements();
	BYTE **ptrOnPointers = mainTable->getPointerOnPartialNewBitmapPointersTable();

	vector<ThreadData> *dividedTable = new vector<ThreadData>();
	for (int i = 0; i < numberOfThreads; i++)
	{
		dividedTable->push_back(*(new ThreadData()));		
		int numberOfElementsPerThread = mainTable->getNumberOfElements() / numberOfThreads;		 
		dividedTable->at(i).init((mainTable->getBitmapPtr() + (i * (numberOfElementsPerThread))), numberOfElementsPerThread);
		*(ptrOnPointers + i) = dividedTable->at(i).getPartialNewBitmapPtr();
	}

	return dividedTable;
}

vector<HANDLE> *ThreadHandler::createThreads(int numberOfThreads, LPTHREAD_START_ROUTINE nameOfTheFunction, ThreadData *data)
{
	vector <HANDLE> *threads = new vector<HANDLE>();
	vector<ThreadData> *tableOfDataPtr = divideDataForThreads(numberOfThreads, data);

	DWORD id = 0;
	for (int i = 0; i < numberOfThreads; i++)
	{
		threads->push_back((HANDLE)CreateThread(0, 0, nameOfTheFunction, reinterpret_cast<void *>(&(tableOfDataPtr->at(i))), 0, &id));
	}

	return threads;
}
