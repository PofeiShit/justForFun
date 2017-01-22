#pragma once

#include <Windows.h>
#include <time.h>

class ScreenShot
{
public:
	BOOL CaptureScreenToFile(LPCTSTR szFileName, int BitCount); //截屏保存为BitCount位的位图到文件名szFileName
	ScreenShot(void){};
	~ScreenShot(void){};
private:

	static BOOL DibSaveImage (LPCTSTR pstrFileName, BITMAPFILEHEADER * pbmfh);
	static BITMAPFILEHEADER * DDBToDIB (HDC hdc, HBITMAP hBitmap,int BitCount);
	static HBITMAP CaptureScreen(LPRECT lpRect);
};