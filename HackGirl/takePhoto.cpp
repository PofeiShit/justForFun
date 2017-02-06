#include "takePhoto.h"

#ifndef CAPTUREBLT 
#define CAPTUREBLT 0x40000000
#endif

HBITMAP ScreenShot::CaptureScreen(LPRECT lpRect)
{
	HDC hdc, hdcMem;
	HBITMAP hemfCopy;
	HWND hwndScr;
	int dstcx, dstcy;
	if(lpRect){
		dstcx = lpRect->right - lpRect->left;
		dstcy = lpRect->bottom - lpRect->top;
	} else { //lpRect ΪNULLʱ��ʾȫ����ͼ
		dstcx = GetSystemMetrics(SM_CXSCREEN);
		dstcy = GetSystemMetrics(SM_CYSCREEN);
	}
	//�������洰�ڵľ����ָ�룩
	if(LockWindowUpdate(hwndScr = GetDesktopWindow())){
		//����ָ�����ڵĿͻ��������������Ļ����ʾ�豸�����Ļ����ľ����ָ����⣩
		hdc = GetDCEx(hwndScr, NULL, DCX_CACHE | DCX_LOCKWINDOWUPDATE);
		hdcMem = CreateCompatibleDC(hdc);//����һ������ʾ���豸���ݼ��ݵ��ڴ��豸���ݣ�������ʾ������Ҫ�Ļ������ڴ��С
		if(NULL == hdcMem){
			ReleaseDC(hwndScr, hdc);
			LockWindowUpdate(NULL);
			return NULL;
		}
		hemfCopy = CreateCompatibleBitmap(hdc, abs(dstcx), abs(dstcy));//����Ҫ��ʾ��λͼ���ڴ�
		if(NULL == hemfCopy){
			DeleteDC(hdcMem);
			ReleaseDC(hwndScr, hdc);
			LockWindowUpdate(NULL);
			return NULL;
		}
		SelectObject(hdcMem, hemfCopy);//��λͼ�������ʾ�Ļ�����
		if(lpRect)
			StretchBlt(hdcMem, 0, 0, abs(dstcx), abs(dstcy), hdc, lpRect->left, lpRect->top, dstcx, dstcy, SRCCOPY|CAPTUREBLT);
		else 
			BitBlt(hdcMem, 0, 0, dstcx, dstcy, hdc, 0, 0, SRCCOPY|CAPTUREBLT);
		DeleteDC(hdcMem);
		ReleaseDC(hwndScr, hdc);
		LockWindowUpdate(NULL);
		return hemfCopy;
	}
	return NULL;
}
BITMAPFILEHEADER* ScreenShot::DDBToDIB(HDC hdc, HBITMAP hBitmap,int BitCount)
{
    BITMAP bm;
    int    iOffset, iSizeImage ;
    BYTE   *pBits;
    BITMAPFILEHEADER *pbfh;
    BITMAPINFO *pbi;
    if(NULL==hBitmap)
        return NULL;
    GetObject(hBitmap,sizeof(BITMAP),&bm);
    switch(BitCount)
    {
		case 1:
		case 4:
		case 8:
			iOffset=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*(1<<BitCount);
			break;
		case 16:
		case 24:
		case 32:
			iOffset=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
			break;
		default:
			return NULL;
    }
    iSizeImage=(((bm.bmWidth*BitCount+31)/32)*4)*bm.bmHeight;
    pbfh=(BITMAPFILEHEADER *)malloc(iOffset+iSizeImage);
    if(NULL==pbfh)
        return NULL;
    pBits=(BYTE *)pbfh+iOffset;
    pbi=(BITMAPINFO *)(pbfh+1);
    pbfh->bfType=0x4D42;
    pbfh->bfSize=iOffset+iSizeImage;
    pbfh->bfReserved1=0;
    pbfh->bfReserved2=0;
    pbfh->bfOffBits=iOffset;
 
    pbi->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
    pbi->bmiHeader.biWidth=bm.bmWidth;
    pbi->bmiHeader.biHeight=bm.bmHeight;
    pbi->bmiHeader.biPlanes=1;
    pbi->bmiHeader.biBitCount=BitCount;
    pbi->bmiHeader.biCompression=BI_RGB;
    pbi->bmiHeader.biSizeImage=iSizeImage;
    pbi->bmiHeader.biXPelsPerMeter=0;
    pbi->bmiHeader.biYPelsPerMeter=0;
    if(BitCount<16)
    {
        pbi->bmiHeader.biClrUsed=pbi->bmiHeader.biClrImportant=(1<<BitCount);
    }
    else
    {
        pbi->bmiHeader.biClrUsed=pbi->bmiHeader.biClrImportant=0;
    }
    GetDIBits(hdc,hBitmap,0,bm.bmHeight,pBits,pbi,DIB_RGB_COLORS);
    return pbfh;
}
BOOL ScreenShot::DibSaveImage(LPCTSTR pstrFileName, BITMAPFILEHEADER * pbmfh)
{
    BOOL   bSuccess ;
    DWORD  dwBytesWritten ;
    HANDLE hFile ;
     
    hFile = CreateFile (pstrFileName, GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL) ;
     
    if (hFile == INVALID_HANDLE_VALUE)
        return FALSE ;
     
    bSuccess = WriteFile (hFile, pbmfh, pbmfh->bfSize, &dwBytesWritten, NULL) ;
    CloseHandle (hFile) ;
     
    if (!bSuccess || (dwBytesWritten != pbmfh->bfSize))
    {
        DeleteFile (pstrFileName) ;
        return FALSE ;
    }
    return TRUE ;
}
BOOL ScreenShot::CaptureScreenToFile(LPCTSTR szFileName, int BitCount) //��������ΪBitCountλ��λͼ���ļ���szFileName
{
    BOOL bret = FALSE;
    HBITMAP hbmp = CaptureScreen(NULL);
    if(hbmp)
    {
        HDC hdc = CreateDC("Display", NULL, NULL, NULL);
        BITMAPFILEHEADER * pbmfh = DDBToDIB (hdc, hbmp, BitCount);
        ReleaseDC(NULL,hdc);
        if(pbmfh)
        {
            bret = DibSaveImage(szFileName,pbmfh);
            free(pbmfh);
        }
        DeleteObject(hbmp);
    }
    return bret;
}
