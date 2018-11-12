#include "pch.h"
#include "ThreadData.h"

void ThreadData::init(BYTE *startingPtr, int numberOfElem)
{
	bitmapInformation = *(new BITMAPINFOHEADER());
	bitmapPtr = startingPtr;
	numberOfElements = numberOfElem;
	isrunning = CreateEvent(0, 1, 0, 0);
	partialNewBitmapPtr = new BYTE[numberOfElem];
}

void ThreadData::init(BYTE *ptr, BITMAPINFOHEADER header, int numberOfThreads)
{
	isrunning = CreateEvent(0, 1, 0, 0);
	bitmapPtr = ptr;
	bitmapInformation = header;
	numberOfElements = header.biSizeImage;
	pointerOnPartialNewBitmapPointersTable = new BYTE*[numberOfThreads];
}