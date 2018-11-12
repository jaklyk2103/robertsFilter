#include "pch.h"
#include "BitmapLoader.h"

void BitmapLoader::loadBitmapFromFile(string filePath)
{
	ifstream inputBitmap(filePath, ios::binary);
	if (inputBitmap.is_open())
	{
		// read headers
		inputBitmap.read((char *)(&fileInfo), sizeof(BITMAPFILEHEADER));
		inputBitmap.read((char *)(&bitmapInfo), sizeof(BITMAPINFOHEADER));

		// create array
		BYTE *bgrDataPointer = new BYTE[bitmapInfo.biSizeImage];

		inputBitmap.read((char *)(bgrDataPointer), bitmapInfo.biSizeImage);
		inputBitmap.close();

		this->bitmapValuesPtr = this->convertBGR2RGB(bgrDataPointer);
	}
	else
	{
		std::cout << "Couldn't find bitmap file.\n";
	}
}

BYTE *BitmapLoader::convertBGR2RGB(BYTE *bgrValuesPtr)
{
	BYTE *rgbPtr(new BYTE[bitmapInfo.biSizeImage]);
	BYTE *tmp = rgbPtr;

	for (int i = 0; i < bitmapInfo.biSizeImage / 3; i++, bgrValuesPtr += 3, tmp += 3)
	{
		*(tmp) = *(bgrValuesPtr + 2);
		*(tmp + 1) = *(bgrValuesPtr + 1);
		*(tmp + 2) = *(bgrValuesPtr);		
	}
	return rgbPtr;
}
