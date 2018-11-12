#pragma once

#include "pch.h"

using namespace std;

class BitmapLoader
{
private:

	BITMAPFILEHEADER fileInfo;
	BITMAPINFOHEADER bitmapInfo;

	BYTE *bitmapValuesPtr = 0;

public:
	void loadBitmapFromFile(string filePath);
	BYTE *convertBGR2RGB(BYTE *BGRValuesPtr);

	BYTE *getBitmapValuesPtr() { return this->bitmapValuesPtr; }
	BITMAPINFOHEADER getBitmapInfoHeader() { return this->bitmapInfo; }
};