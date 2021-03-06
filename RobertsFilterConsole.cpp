// RobertsFilterConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "BitmapLoader.h"
#include "ThreadHandler.h"
#include "BitmapWriter.h"

extern "C" BYTE *MyProc1(BYTE *valuesPtr, int imageSize);

using namespace std;


int detectNumberOfCores()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;	
}

DWORD WINAPI threadProc2(void *args)
{
	std::cout << "Beginning a thread...\n";
	ThreadData *data = reinterpret_cast<ThreadData *>(args);
	if (!data)
	{
		return 1;
	}
	SetEvent(data->getIsRunningHandle());
	
	// functionality here
	//=====================================

	/*
		[	0,	1,	0]	 [	0,	0,	1]
		[	0,	0, -1]	 [	0,	-1,	0]
		[	0,	0,	0]	 [	0,	0,	0]
	*/
	const char matrix1[9] = { 0, 0, 1, 0, -1, 0, 0, 0, 0 };
	const char matrix2[9] = { 0, 1, 0, 0, 0, -1, 0, 0, 0 };

	BYTE *valuesPtr = data->getBitmapPtr();
	BYTE *newValuesPtr = data->getPartialNewBitmapPtr();
	int pixelCounter = 0;
	while (pixelCounter < data->getNumberOfElements())
	{
		short weight1 = 0;
		short weight2 = 0;

		for (int i = 0; i < 9; i++)
		{
			weight1 += valuesPtr[(i * 3) + pixelCounter] * matrix1[i];
			weight2 += valuesPtr[(i * 3) + pixelCounter] * matrix2[i];
		}

		//short val = abs(weight1) + abs(weight2);
		short val = round(sqrt(weight1*weight1 + weight2 * weight2));
		byte finalValue = (unsigned char)(val);

		if (finalValue > 150) finalValue = 255;
		*(newValuesPtr + pixelCounter) = finalValue;

		pixelCounter += 1;
	}
}

void printBitmapRGB(BYTE *bitmapValues, BITMAPINFOHEADER bitmapInfo)
{
	for (int i = 0; i < bitmapInfo.biSizeImage / 3; i++, bitmapValues += 3)
	{
		cout << "R: " << int(*(bitmapValues)) << " G: " << int(*(bitmapValues + 1)) << " B: " << int(*(bitmapValues + 2)) << '\n';
	}
}


int main()
{
	const int numberOfCores = detectNumberOfCores();
	cout << "Number of processor cores: " << numberOfCores << '\n';
	const int numberOfThreads = 1;

	std::cout << "Loading .bmp file...\n";

	BitmapLoader *bitmapLoader = new BitmapLoader();
	bitmapLoader->loadBitmapFromFile("bitmapaKrason.bmp");
	BYTE *valuesPtr = bitmapLoader->getBitmapValuesPtr();
	BITMAPINFOHEADER infoHeader = bitmapLoader->getBitmapInfoHeader();
	
	std::cout << ".bmp file loaded.\nStarting image processing.\n";

	ThreadData *data = new ThreadData();	
	data->init(valuesPtr, infoHeader, numberOfThreads);


	// ==================================

	printBitmapRGB(valuesPtr, infoHeader);

	ThreadHandler *threadHandler = new ThreadHandler();
	vector<HANDLE> threads = *(threadHandler->createThreads(numberOfThreads, threadProc2, data));
	WaitForMultipleObjects(threads.size(), &threads[0], TRUE, 10000);
	
	std::cout << "Image processing completed.\nSaving file...\n";

	// MERGING PARTIAL TABLES INTO ONE TABLE

	BYTE *newImageValuesPtr = new BYTE[infoHeader.biSizeImage];
	BYTE **tableOfPointers = data->getPointerOnPartialNewBitmapPointersTable();

	int l = 0;	
	int numberOfElementsInPartialBitmaps = infoHeader.biSizeImage / numberOfThreads;

	for (int j = 0; j < numberOfThreads; j++)
	{
		for (int i = 0; i < numberOfElementsInPartialBitmaps; i++)
		{
			newImageValuesPtr[l] = tableOfPointers[j][i];
			l++;
		}
	}
	
	// ==================================
	
	LONG width = bitmapLoader->getBitmapInfoHeader().biWidth;
	LONG height = bitmapLoader->getBitmapInfoHeader().biHeight;

	BitmapWriter *bitmapWriter = new BitmapWriter();
	bitmapWriter->SaveBitmapToFile(newImageValuesPtr, width, height, 24, 2, L"modifiedBitmap.bmp");

	std::cout << "Finished!\n";

	system("pause");
}