#pragma once
class BitmapWriter
{
public:
	void SaveBitmapToFile(BYTE* pBitmapBits,
		LONG lWidth,
		LONG lHeight,
		WORD wBitsPerPixel,
		const unsigned long& padding_size,
		LPCTSTR lpszFileName);
};

