#pragma once

#include <Windows.h>
#include <time.h>

class ScreenShot
{
public:
	BOOL CaptureScreenToFile(LPCTSTR szFileName, int BitCount); //��������ΪBitCountλ��λͼ���ļ���szFileName
	ScreenShot(void){};
	~ScreenShot(void){};
private:

	static BOOL DibSaveImage (LPCTSTR pstrFileName, BITMAPFILEHEADER * pbmfh);
	static BITMAPFILEHEADER * DDBToDIB (HDC hdc, HBITMAP hBitmap,int BitCount);
	static HBITMAP CaptureScreen(LPRECT lpRect);
};