#pragma once

class ThreadData
{
private:
	HANDLE isrunning;
	BYTE *bitmapPtr;
	BITMAPINFOHEADER bitmapInformation;
	int numberOfElements;
	BYTE **pointerOnPartialNewBitmapPointersTable;
	BYTE *partialNewBitmapPtr;

public:
	void init(BYTE *startingPtr, int numberOfElem);
	void init(BYTE *ptr, BITMAPINFOHEADER header, int numberOfThreads);
	HANDLE getIsRunningHandle() { return this->isrunning; }
	int getNumberOfElements() { return this->numberOfElements; }
	BITMAPINFOHEADER getBitmapInformation() { return this->bitmapInformation; }
	BYTE *getBitmapPtr() { return this->bitmapPtr; }
	BYTE *getPartialNewBitmapPtr() { return this->partialNewBitmapPtr; }
	BYTE **getPointerOnPartialNewBitmapPointersTable() { return this->pointerOnPartialNewBitmapPointersTable; }

};
